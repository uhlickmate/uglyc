#ifndef UGLYC_ERROR_H
#define UGLYC_ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define FORE_BLACK "\x1b[30m"
#define FORE_RED "\x1b[31m"
#define FORE_GREEN "\x1b[32m"
#define FORE_YELLOW "\x1b[33m"
#define FORE_BLUE "\x1b[34m"
#define FORE_MAGENTA "\x1b[35m"
#define FORE_CYAN "\x1b[36m"
#define FORE_WHITE "\x1b[37m"
#define FORE_NORMAL "\x1b[m"

// Error codes
#define ERR_BUF_OVERFLOW "err0001"

static inline void _panic(const char *code, const char *file, int line,
                          const char *fmt, ...) {
    fprintf(stderr, "%s%s # (%s:%d): %s", FORE_RED, code, file, line,
            FORE_WHITE);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");
    exit(1);
}

#define panic(code, ...) _panic(code, __FILE__, __LINE__, __VA_ARGS__)

#endif
