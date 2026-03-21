#pragma once

#include <stdint.h>
#include <cinder/router.h>

typedef struct {
    uint16_t port;
} cinder_server_config_t;

typedef struct cinder_server cinder_server_t;

cinder_server_t* cinder_server_create(const cinder_server_config_t *config);

void cinder_server_destroy(cinder_server_t* server);

int cinder_server_start(cinder_server_t *server);

void cinder_set_routes(cinder_server_t*, const cinder_route_t*);