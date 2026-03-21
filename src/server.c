#include <stdio.h>
#include<stdlib.h>

#include <cinder/log.h>
#include <cinder/server.h>
#include <cinder/platform.h>
#include <cinder/http.h>
#include <cinder/router.h>

struct cinder_server {
    cinder_server_config_t config;
    cinder_socket_t *socket;
    const cinder_route_t *routes;
};

cinder_server_t* cinder_server_create( const cinder_server_config_t *config)
{   
    if (!config) {
        CINDER_ERROR("server", "create failed: config is NULL");
        return NULL;
    }

    cinder_server_t *server = malloc(sizeof(*server));
    if (!server) {
        CINDER_ERROR("server", "create failed: memory allocation failed");
        return NULL;
    }

    server->config = *config;
    return server;
}

void cinder_server_destroy(cinder_server_t* server)
{
    if (server) {
        free(server);
    }
}

int cinder_server_start(cinder_server_t *server)
{   
    CINDER_INFO("server", "starting cinder server");
    const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 17\r\n\r\n"
        "Hello from cinder";

    server->socket = cinder_socket_open();
    if (!server->socket) {
        CINDER_ERROR("server", "failed to open socket");
        return -1;
    }

    if (cinder_socket_bind(server->socket, server->config.port) < 0) {
        CINDER_ERROR("server", "failed to bind to port %u", server->config.port);
        return -1;
    }

    if (cinder_socket_listen(server->socket) < 0) {
        CINDER_ERROR("server", "failed to listen on socket");
        return -1;
    }

    CINDER_INFO("server", "listening on port %u", server->config.port);

    while (1) {
        cinder_socket_t *client = cinder_socket_accept(server->socket);

        if (!client) {
            CINDER_ERROR("server", "accept failed");
            continue;
        }
        cinder_request_t req;

        if (cinder_http_read(client, &req) == 0) {
            if (cinder_http_parse_request_line(&req) == 0) {
                CINDER_INFO("http", "%s %s", req.method, req.path);

                cinder_handler_fn handler = cinder_router_match(server->routes, &req);

                if (handler) {
                    handler(&req);
                } else {
                    CINDER_ERROR("router", "404 Not Found\n");
                }
            }
        }

        int sent = cinder_socket_send(client, response, sizeof(response) - 1);
        if (sent < 0) {
            CINDER_ERROR("server", "failed to send response to client");
        }

        cinder_socket_close(client);
    }

    return 0;
        
}

void cinder_set_routes(
    cinder_server_t *server, 
    const cinder_route_t *routes
) {
    server->routes = routes;
}
