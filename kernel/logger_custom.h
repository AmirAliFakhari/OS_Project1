// kernel/logger_custom.h
#ifndef LOGGER_CUSTOM_H
#define LOGGER_CUSTOM_H

enum log_level {
    INFO = 0,
    WARN = 1,
    ERROR = 2
};

void log_message(enum log_level level, const char *message);

#endif