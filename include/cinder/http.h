#pragma once

#include <cinder/platform.h>
#include <stddef.h>

#define CINDER_HTTP_MAX_REQUEST 4096


typedef struct {
    char raw[CINDER_HTTP_MAX_REQUEST];
    size_t length;

    char *method;
    char *path;
    char *version;
} cinder_request_t;

int cinder_http_read(cinder_socket_t* , cinder_request_t*);
int cinder_http_parse_request_line(cinder_request_t*);