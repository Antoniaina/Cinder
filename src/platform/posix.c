#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <cinder/platform.h>

struct cinder_socket {
    int fd;
};

cinder_socket_t* cinder_socket_open(void) 
{
    cinder_socket_t *sock = malloc(sizeof(*sock));
    if (!sock)
        return NULL;

    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd < 0) {
        free(sock);
        return NULL;
    }

    return sock;
}

int cinder_socket_bind(cinder_socket_t *sock, int port)
{
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    return bind(sock->fd, (struct sockaddr*)&addr, sizeof(addr));
}

int cinder_socket_listen(cinder_socket_t* sock)
{
    return listen(sock->fd, 16);
}

cinder_socket_t* cinder_socket_accept(cinder_socket_t *sock)
{
    int fd = accept(sock->fd, NULL, NULL);
    if (fd < 0)
        return NULL;

    cinder_socket_t *client = malloc(sizeof(*client));
    client->fd = fd;
    return client;
}

int cinder_socket_send(cinder_socket_t *sock, const void *data, size_t len)
{
    return send(sock->fd, data, len, 0);
}

void cinder_socket_close(cinder_socket_t *sock)
{
    if (!sock)
        return;

    close(sock->fd);
    free(sock);
}

int cinder_socket_read(cinder_socket_t *sock, void *buffer, size_t size)
{
    if (!sock)
        return -1;

    return read(sock->fd, buffer, size);
}
