#include <stdio.h>
#include<stdlib.h>

#include "cinder/server.h"

struct cinder_server {
    cinder_server_config_t config;
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
    if (!server)
        return -1;

    printf("Server listening on port %u\n", server->config.port);
    return 0;
}