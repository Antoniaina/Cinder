#pragma once

#include <stddef.h>

typedef struct cinder_socket cinder_socket_t;

cinder_socket_t* cinder_socket_open(void);
int cinder_socket_bind(cinder_socket_t*, int port);
int cinder_socket_listen(cinder_socket_t*);
cinder_socket_t* cinder_socket_accept(cinder_socket_t*);
int cinder_socket_send(cinder_socket_t*, const void*, size_t);
void cinder_socket_close(cinder_socket_t *);
