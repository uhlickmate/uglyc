#ifndef UGLYC_DEBUG_H
#define UGLYC_DEBUG_H

#include "string.h"
#include "types.h"
#include "error.h"
#include <string.h>

static inline bool i32_eq(i32 a, i32 b) { return (a == b); }
static inline bool char_ptr_eq(char* a, char* b) { return (strcmp((a), (b)) == 0); }

#define eq(a, b) _Generic((a), \
    i32: i32_eq, \
    char*: char_ptr_eq, \
    const char*: char_ptr_eq, \
    String: String_eq, \
    default: false \
)((a), (b)) \

#define assert_eq(a, b) \
    if (!eq((a), (b))) { \
        panic(ERR_NOT_EQUAL, "arguments of assert_eq are not equal"); \
    } \



#endif
