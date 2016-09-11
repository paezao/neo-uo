#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

enum log_type
{
    LOG_INFO,
    LOG_ERROR
};

void print_log(enum log_type log_type, char *text);

#endif
