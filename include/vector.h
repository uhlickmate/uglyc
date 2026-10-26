#ifndef UGLYC_VECTOR_H
#define UGLYC_VECTOR_H

#include "types.h"
#include <stdlib.h>
#include <string.h>

// NOTE: All vec ops require explicit type passed unlike
// other objects (Option, Result have an optional explicit constructor)

#define declare_vec_for(T)                                                     \
    typedef struct {                                                           \
        T *ptr;                                                                \
        size_t len;                                                            \
        size_t capacity;                                                       \
    } Vec_##T
declare_vec_for(i32);

#define Vec(T) Vec_##T

#define Vec_new(T)                                                             \
    (Vec(T)) { .ptr = NULL, .len = 0, .capacity = 0, }

#define Vec_with_capacity(T, cap)                                              \
    (Vec(T)) { .ptr = malloc(cap), .len = 0, .capacity = cap, }

#define Vec_with_intended_len(T, i_len)                                        \
    (Vec(T)) {                                                                 \
        .ptr = malloc(i_len * sizeof(T)), .len = 0,                            \
        .capacity = i_len * sizeof(T),                                         \
    }

#define Vec_from(T, arr)                                                       \
    ({                                                                         \
        size_t arr_len = sizeof(arr) / sizeof(T);                              \
        Vec(T) v = (Vec(T)){                                                   \
            .ptr = malloc(sizeof(arr)),                                        \
            .len = arr_len,                                                    \
            .capacity = sizeof(arr),                                           \
        };                                                                     \
        memcpy(v.ptr, arr, sizeof(arr));                                       \
        v;                                                                     \
    })

#define Vec_to_arr(T, vec, arr, arr_size)                                      \
    ({                                                                         \
        if (arr_size <= vec.capacity && arr_size > 0) {                        \
            T *_arr = (arr);                                                   \
            memcpy(_arr, vec.ptr, vec.capacity);                               \
        }                                                                      \
    })

#define Vec_to_arr_unsafe(T, vec, arr)                                         \
    ({                                                                         \
        T *_arr = (arr);                                                       \
        memcpy(_arr, vec.ptr, vec.capacity);                                   \
    })

#define Vec_free(vec) free(vec.ptr)

#define Vec_push(T, vec_ptr, el)                                               \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        if (_vec->capacity == _vec->len * sizeof(T)) {                         \
            void *tmp = realloc(_vec->ptr, _vec->capacity + sizeof(T));        \
            if (tmp != NULL) {                                                 \
                _vec->ptr = tmp;                                               \
                _vec->len++;                                                   \
                _vec->capacity += sizeof(T);                                   \
                _vec->ptr[_vec->len] = el;                                     \
            }                                                                  \
        } else {                                                               \
            _vec->ptr[_vec->len] = el;                                         \
        }                                                                      \
    })

// TODO: Panic
#define Vec_set(T, vec_ptr, idx, el)                                           \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        if (_vec->len > idx && idx >= 0) {                                     \
            _vec->ptr[idx] = el;                                               \
        }                                                                      \
    })

#define Vec_pop(T, vec_ptr)                                                    \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        if (_vec->len > 0) {                                                   \
            _vec->len--;                                                       \
        }                                                                      \
    })

#define Vec_shrink_to_fit(T, vec_ptr)                                          \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        if (_vec->len * sizeof(T) != _vec->capacity) {                         \
            void *tmp = realloc(_vec->ptr, _vec->len * sizeof(T));             \
            if (tmp != NULL) {                                                 \
                _vec->ptr = tmp;                                               \
                _vec->capacity = _vec->len * sizeof(T);                        \
            }                                                                  \
        }                                                                      \
    })

#define Vec_insert(T, vec_ptr, idx, el)                                        \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        if (_vec->len >= idx && idx > 0) {                                     \
            void *tmp = realloc(_vec->ptr, _vec->capacity + sizeof(T));        \
            if (tmp != NULL) {                                                 \
                _vec->ptr = tmp;                                               \
                size_t pushed_elements = sizeof(T) * (_vec->len - idx);        \
                memmove(_vec->ptr + idx + 1, _vec->ptr + idx,                  \
                        pushed_elements);                                      \
                _vec->ptr[idx] = el;                                           \
                _vec->len++;                                                   \
                _vec->capacity += sizeof(T);                                   \
            }                                                                  \
        }                                                                      \
    })

// TODO: Panic when out of bounds
#define Vec_get(vec, idx) *(vec.ptr + idx)
#define Vec_is_empty(vec)                                                      \
    ({                                                                         \
        bool res = false;                                                      \
        if (vec.len == 0)                                                      \
            res = true;                                                        \
        res;                                                                   \
    })

#endif
