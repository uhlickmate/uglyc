#ifndef UGLYC_ARENA_ALLOC_H
#define UGLYC_ARENA_ALLOC_H

#include "option.h"
#include "vector.h"
#include <stdlib.h>

typedef struct {
    char *base;
    char *next;
    size_t len;
    size_t capacity;
} Arena;

static inline Arena Arena_new(size_t bytes) {
    char *mem_ptr = (char *)malloc(bytes);
    return (Arena){
        .base = mem_ptr, .next = mem_ptr, .len = 0, .capacity = bytes};
}

static inline void Arena_move(Arena *a, size_t n) {}

#define Arena_add_primitive(T, primitive, arena_ptr)                           \
    ({                                                                         \
        T *res = NULL;                                                         \
        Arena *_a = (arena_ptr);                                               \
        if (_a->len + sizeof(T) <= _a->capacity) {                             \
            _a->next = (char *)primitive;                                      \
            res = _a->next;                                                    \
            _a->len += sizeof(T);                                              \
            _a->next += sizeof(T);                                             \
        }                                                                      \
        res;                                                                   \
    })

// _vec->ptr now points to the buffer in the arena
#define Arena_add_vec_move(T, vec_ptr, arena_ptr)                              \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        Arena *_a = (arena_ptr);                                               \
        if (_a->len + _vec->len * sizeof(T) <= _a->capacity) {                 \
            T *a_ptr = memcpy(_a->next, _vec->ptr, _vec->len * sizeof(T));     \
            free(_vec->ptr);                                                   \
            _vec->ptr = a_ptr;                                                 \
            _a->len += _vec->len * sizeof(T);                                  \
            _a->next += _vec->len * sizeof(T);                                 \
        }                                                                      \
    })
// original Vec is drained & becomes empty
// returns arena vec as a new struct
#define Arena_add_vec_drain(T, vec_ptr, arena_ptr)                             \
    ({                                                                         \
        Vec(T) *_vec = (vec_ptr);                                              \
        Arena *_a = (arena_ptr);                                               \
        Option(Vec(T)) res = None;                                             \
        if (_a->len + _vec->len * sizeof(T) <= _a->capacity) {                 \
            T *a_ptr = memcpy(_a->next, _vec->ptr, _vec->len * sizeof(T));     \
            Vec(T) v_new = {                                                   \
                .ptr = a_ptr, .len = _vec->len, .capacity = _vec->capacity};   \
            res = Some_explicit(Vec(T), v_new);                                \
            _a->len += _vec->len * sizeof(T);                                  \
            _a->next += _vec->len * sizeof(T);                                 \
            free(_vec->ptr);                                                   \
            _vec->ptr = NULL;                                                  \
            _vec->len = 0;                                                     \
            _vec->capacity = 0;                                                \
        }                                                                      \
        res;                                                                   \
    })

#define Arena_add_string()

static inline void Arena_destroy(Arena *a) { free(a->base); }

#endif
