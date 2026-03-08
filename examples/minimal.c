#include <cinder/cinder.h>
#include <cinder/log.h>

int main(void)
{
    cinder_server_config_t config = {
        .port = 3000
    };

    cinder_server_t *server = cinder_server_create(&config);

    if (!server) {
        return 1;
    }

    cinder_server_start(server);
    cinder_server_destroy(server);

    return 0;
}