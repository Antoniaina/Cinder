#include <cinder/cinder.h>
#include <stdio.h>

void hello(cinder_request_t *req) 
{
    printf("Hello route lty e\n");
}

int main(void)
{
    cinder_server_config_t config = {
        .port = 3000
    };

    cinder_server_t *server = cinder_server_create(&config);

    if (!server) 
        return 1;

    cinder_route_t routes[] = {
        ROUTE("GET", "/hello", hello),
        ROUTE_END()
    };

    cinder_set_routes(server, routes);
    cinder_server_start(server);
    cinder_server_destroy(server);

    return 0;
}