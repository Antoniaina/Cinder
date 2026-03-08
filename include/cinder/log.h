#pragma once

#define CINDER_DEBUG(module, ...) \
    cinder_log(LOG_DEBUG, module, __VA_ARGS__)

#define CINDER_INFO(module, ...) \
    cinder_log(LOG_INFO, module, __VA_ARGS__)
    
#define CINDER_ERROR(module, ...) \
    cinder_log(LOG_ERROR, module, __VA_ARGS__)


#include <stdio.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
} cinder_log_level_t;

void cinder_log(cinder_log_level_t level, 
                const char *module, 
                const char *fmt, 
                ...);

