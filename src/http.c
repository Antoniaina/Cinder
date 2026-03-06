#include <unistd.h>
#include <string.h>

#include <cinder/http.h>

int cinder_http_read(cinder_socket_t* sock, cinder_request_t *req)
{
    if (!req)
        return -1;

    ssize_t n = cinder_socket_read(sock, req->raw, sizeof(req->raw)-1);    

    req->raw[n] = '\0';
    req->length = (size_t)n;

    return 0;
}

int cinder_http_parse_request_line(cinder_request_t *req)
{
    if (!req)
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