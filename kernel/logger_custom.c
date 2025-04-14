// kernel/logger_custom.c
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "logger_custom.h"

void log_message(enum log_level level, const char *message) {
    switch (level) {
        case INFO:
            printf("INFO - %s\n", message);
            break;
        case WARN:
            printf("WARNING - %s\n", message);
            break;
        case ERROR:
            printf("ERROR - %s\n", message);
            break;
        default:
            printf("UNKNOWN - %s\n", message);
            break;
    }
}