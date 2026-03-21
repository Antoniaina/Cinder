#include <string.h>

#include <cinder/router.h>

cinder_handler_fn cinder_router_match(
    const cinder_route_t *routes,
    cinder_request_t *req
) {
    const cinder_route_t *route = routes;

    while (route->path != NULL) {
        if (strcmp(route->method, req->method) == 0 && 
            strcmp(route->path, req->path) == 0    
        ) return route->handler;

        route++;
    }

    return NULL;
}