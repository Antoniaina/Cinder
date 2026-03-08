#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <cinder/log.h>

static const char *level_str[] = {
    "DEBUG",
    "INFO",
    "ERROR"
};

void cinder_log(cinder_log_level_t level, 
                const char *module,
                const char *fmt,
                ...)
{
    time_t now = time(NULL);
    struct tm *t  = localtime(&now);

    char timebuf[32];

    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", t);

    printf("[%s] %s %s: ", level_str[level], timebuf, module);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}