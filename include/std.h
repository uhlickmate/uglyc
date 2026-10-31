#ifndef UGLYC_STD_H
#define UGLYC_STD_H

#include <stdlib.h>

#define concat(a, b) a##b

#define class struct
#define class_declared typedef struct
#define declare_class(T) typedef struct T T

#define impl(T, name, R) R concat(T##_, name)
#define method(T, method) concat(T##_, method)

#define var(name, T) T name
#define func(T, name) T name

#define for_range(from, to, item) for (int item = from; item < to + 1; item++)
#define for_range_down(from, to, item)                                         \
    for (int item = from; item > to - 1; item--)

#define foreach_arr(size, item, array)                                         \
    for (int keep = 1, count = 0; keep && count != size;                       \
         keep = !keep, count++)                                                \
        for (item = (array) + count; keep; keep = !keep)

#define foreach_vec(item, vec)                                                 \
    for (int keep = 1, count = 0; keep && count != vec.len;                    \
         keep = !keep, count++)                                                \
        for (item = (vec.ptr) + count; keep; keep = !keep)

typedef enum {
    Heap,
    Stack
} AllocType;

#endif
