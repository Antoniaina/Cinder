#include <unistd.h>
#include <string.h>

#include <cinder/http.h>
#include <cinder/log.h>

int cinder_http_read(cinder_socket_t* sock, cinder_request_t *req)
{
    if (!req) {
        CINDER_ERROR("http", "read failed: req is NULL");
        return -1;
    }

    if (!sock) {
        CINDER_ERROR("http", "read failed: socket is NULL");
        return -1;
    }

    ssize_t n = cinder_socket_read(sock, req->raw, sizeof(req->raw) - 1);

    if (n < 0) {
        CINDER_ERROR("http", "read failed: socket read error");
        return -1;
    }

    if (n == 0)
        return -1;

    req->raw[n] = '\0';
    req->length = (size_t)n;

    return 0;
}

int cinder_http_parse_request_line(cinder_request_t *req)
{
    if (!req) {
        CINDER_ERROR("http", "parse failed: req is NULL");
        return -1;
    }

    if (req->length == 0)
        return -1;

    char *buffer = req->raw;

    req->method = buffer;
    while (*buffer && *buffer != ' ')
        buffer++;

    if (*buffer == '\0')
        return -1;

    *buffer = '\0';
    buffer++;

    req->path = buffer;
    while (*buffer && *buffer != ' ')
        buffer++;

    if (*buffer == '\0')
        return -1;

    *buffer = '\0';
    buffer++;

    req->version = buffer;

    return 0;
}