#pragma once

#include<cinder/http.h>

typedef void(*cinder_handler_fn) (
    cinder_request_t *req;
);

typedef struct {
    const char *method;
    const char *path;
    cinder_handler_fn handler;
} cinder_route_t;

#define ROUTE(method, path, handler) \
    {method, path, handler}

#define ROUTE_END() \
    {NULL, NULL, NULL}

cinder_handler_fn cinder_router_match(
    const cinder_route_t *routes;
    cinder_request_t *req;
);