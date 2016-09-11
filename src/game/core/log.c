#include "log.h"
#include <stdio.h>

void print_log(enum log_type log_type, char *text)
{
    char *prefix;

    switch(log_type)
    {
        case LOG_INFO:
            prefix = "INFO";
            break;
        case LOG_ERROR:
            prefix = "ERROR";
            break;
    }

    printf("[%s] %s\n", prefix, text);
}
