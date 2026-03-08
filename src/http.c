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

    if (n == 0) {
        CINDER_DEBUG("http", "client closed connection (0 bytes read)");
        return -1;
    }

    req->raw[n] = '\0';
    req->length = (size_t)n;
    CINDER_DEBUG("http", "read %zd bytes from client", n);

    return 0;
}

int cinder_http_parse_request_line(cinder_request_t *req)
{
    if (!req) {
        CINDER_ERROR("http", "parse failed: req is NULL");
        return -1;
    }

    if (req->length == 0) {
        CINDER_DEBUG("http", "parse failed: empty request");
        return -1;
    }

    char *buffer = req->raw;

    req->method = buffer;
    while (*buffer && *buffer != ' ')
        buffer++;

    if (*buffer == '\0') {
        CINDER_DEBUG("http", "parse failed: invalid request format (method)");
        return -1;
    }

    *buffer = '\0';
    buffer++;

    req->path = buffer;
    while (*buffer && *buffer != ' ')
        buffer++;

    if (*buffer == '\0') {
        CINDER_DEBUG("http", "parse failed: invalid request format (path)");
        return -1;
    }

    *buffer = '\0';
    buffer++;

    req->version = buffer;
    CINDER_DEBUG("http", "parsed request: %s %s %s", req->method, req->path, req->version);

    return 0;
}