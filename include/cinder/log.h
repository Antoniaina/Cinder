#pragma once

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED   "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_GRAY  "\x1b[90m"

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
} cinder_log_level_t;

void cinder_log(cinder_log_level_t level, 
                const char *module, 
                const char *fmt, 
                ...);


#define CINDER_INFO(module, ...) \
    cinder_log(LOG_INFO, module, __VA_ARGS__)

#define CINDER_ERROR(module, ...) \
    cinder_log(LOG_ERROR, module, __VA_ARGS__)

#ifdef ENABLE_DEBUG

#define CINDER_DEBUG(module, ...) \
    cinder_log(LOG_DEBUG, module, __VA_ARGS__)

#else

#define CINDER_DEBUG(module, ...)

#endif