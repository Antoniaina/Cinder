#include <stdio.h>
#include<stdlib.h>

#include <cinder/log.h>
#include <cinder/server.h>
#include <cinder/platform.h>
#include <cinder/http.h>

struct cinder_server {
    cinder_server_config_t config;
    cinder_socket_t *socket;
};

cinder_server_t* cinder_server_create( const cinder_server_config_t *config)
{   
    if (!config)
        return NULL;

    cinder_server_t *server = malloc(sizeof(*server));
    if (!server)
        return NULL;

    
    server->config = *config;
    return server;
}

void cinder_server_destroy(cinder_server_t* server)
{
    free(server);
}

int cinder_server_start(cinder_server_t *server)
{   
    CINDER_INFO("server", "starting cinder server");
    const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 17\r\n\r\n"
        "Hello from cinder";

    server->socket = cinder_socket_open();
    cinder_socket_bind(server->socket, server->config.port);
    cinder_socket_listen(server->socket);
    CINDER_INFO("server", "listening on port %u", server->config.port);

    while (1) {
        cinder_socket_t *client = cinder_socket_accept(server->socket);

        if (!client)
            continue;
        
        CINDER_INFO("server", "client connected");

        cinder_request_t req;

        if(!cinder_http_read(client, &req)) {
            if (!cinder_http_parse_request_line(&req)) {
                CINDER_INFO("http", "%s %s", req.method, req.path);
            }
        }

        cinder_socket_send(client, response, sizeof(response) -1);

        cinder_socket_close(client);        
    }

    return 0;
        
}