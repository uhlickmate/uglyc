#ifndef UGLYC_STRING_H
#define UGLYC_STRING_H

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_DEFAULT_SIZE 16

typedef struct {
    char *ptr;
    size_t len;
    size_t capacity;
} string_t;

static inline string_t string_new() {
    string_t s = {.ptr = (char *)malloc(STRING_DEFAULT_SIZE),
                  .len = 0,
                  .capacity = STRING_DEFAULT_SIZE};
    return s;
}

static inline string_t string_from(char *str) {
    size_t str_len = strlen(str);
    string_t s = {
        .ptr = (char *)malloc(str_len), .len = str_len, .capacity = str_len};
    strcpy(s.ptr, str);
    return s;
}
static inline string_t to_string(char *str) {
    size_t str_len = strlen(str);
    string_t s = {
        .ptr = (char *)malloc(str_len), .len = str_len, .capacity = str_len};
    strcpy(s.ptr, str);
    return s;
}

static inline void string_to_char_buf(string_t src, char *dest,
                                      size_t dest_size) {
    if (src.len > dest_size) {
        panic(ERR_BUF_OVERFLOW,
              "source string_t buffer (%d) is larger than destination buffer "
              "(%d)",
              strlen(src.ptr), strlen(dest));
    }
    strcpy(dest, src.ptr);
}
static inline void string_to_char_buf_unsafe(string_t src, char *dest) {
    strcpy(dest, src.ptr);
}

static inline size_t string_(string_t str) {}

#endif
