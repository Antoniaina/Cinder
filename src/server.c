#include <stdio.h>
#include<stdlib.h>

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
    const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 17\r\n\r\n"
        "Hello from cinder";

    server->socket = cinder_socket_open();
    cinder_socket_bind(server->socket, server->config.port);
    cinder_socket_listen(server->socket);

    while (1) {
        cinder_socket_t *client = cinder_socket_accept(server->socket);

        if (!client)
            continue;

        cinder_request_t req;

        if(!cinder_http_read(client, &req)) {
            if (!cinder_http_parse_request_line(&req)) {
                printf("method: %s\n", req.method);
                printf("path: %s\n", req.path);
                printf("version: %s\n", req.version);
            }
        }

        cinder_socket_send(client, response, sizeof(response) -1);

        cinder_socket_close(client);        
    }

    return 0;
        
}