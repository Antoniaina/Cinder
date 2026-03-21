#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <cinder/platform.h>
#include <cinder/log.h>

struct cinder_socket {
    int fd;
};

cinder_socket_t* cinder_socket_open(void)
{
    cinder_socket_t *sock = malloc(sizeof(*sock));
    if (!sock) {
        CINDER_ERROR("platform", "socket_open: malloc failed");
        return NULL;
    }

    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd < 0) {
        CINDER_ERROR("platform", "socket_open: socket() failed (errno=%d)", errno);
        free(sock);
        return NULL;
    }

    return sock;
}

int cinder_socket_bind(cinder_socket_t *sock, int port)
{
    if (!sock) {
        CINDER_ERROR("platform", "socket_bind: sock is NULL");
        return -1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    int ret = bind(sock->fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
        CINDER_ERROR("platform", "socket_bind failed on port %d (errno=%d)", port, errno);
        return -1;
    }

    return ret;
}

int cinder_socket_listen(cinder_socket_t* sock)
{
    if (!sock) {
        CINDER_ERROR("platform", "socket_listen: sock is NULL");
        return -1;
    }

    int ret = listen(sock->fd, 16);
    if (ret < 0) {
        CINDER_ERROR("platform", "socket_listen failed (errno=%d)", errno);
        return -1;
    }

    return ret;
}

cinder_socket_t* cinder_socket_accept(cinder_socket_t *sock)
{
    if (!sock) {
        CINDER_ERROR("platform", "socket_accept: sock is NULL");
        return NULL;
    }

    int fd = accept(sock->fd, NULL, NULL);
    if (fd < 0) {
        CINDER_ERROR("platform", "socket_accept failed (errno=%d)", errno);
        return NULL;
    }

    cinder_socket_t *client = malloc(sizeof(*client));
    if (!client) {
        CINDER_ERROR("platform", "socket_accept: malloc for client failed");
        close(fd);
        return NULL;
    }

    client->fd = fd;
    return client;
}

int cinder_socket_send(cinder_socket_t *sock, const void *data, size_t len)
{
    if (!sock) {
        CINDER_ERROR("platform", "socket_send: sock is NULL");
        return -1;
    }

    ssize_t sent = send(sock->fd, data, len, 0);
    if (sent < 0) {
        CINDER_ERROR("platform", "socket_send failed (errno=%d)", errno);
        return -1;
    }

    return (int)sent;
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
    if (!sock) {
        CINDER_ERROR("platform", "socket_read: sock is NULL");
        return -1;
    }

    return read(sock->fd, buffer, size);
}
