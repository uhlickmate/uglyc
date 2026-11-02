#ifndef UGLYC_GC_H
#define UGLYC_GC_H

#include "vector.h"
#include "std.h"

declare_class(PoolAlloc);
class PoolAlloc {
    Vec(char_ptr) data;
    // TODO: Vec for lookup
};

static inline PoolAlloc PoolAlloc_new() {
    return (PoolAlloc){ .data = Vec_new(char_ptr) };
}

#define PoolAlloc_alloc(T, bytes, pool_ptr) \
    ({ \
        PoolAlloc *_pool = (pool_ptr); \
        T* temp_buf = (T*)malloc(bytes); \
        Vec_push(char_ptr, &_pool->data, (char*)temp_buf); \
        temp_buf; \
    })

#define PoolAlloc_realloc(T, org_ptr, bytes, pool_ptr) \
    ({ \
        PoolAlloc *_pool = (pool_ptr); \
        T* _ptr = (org_ptr); \
        T* temp_ptr = realloc(_ptr, bytes); \
        if (temp_ptr != NULL) { \
            org_ptr = temp_ptr; \
        } \
    })

#define PoolAlloc_get(T, idx, pool_ptr) \
    ({ \
        PoolAlloc *_pool = (pool_ptr); \
        T* ptr = (T*)(_pool->data.ptr[idx]); \
        ptr; \
    })

#define PoolAlloc_free(pool_ptr) \
    PoolAlloc *_pool = (pool_ptr); \
    foreach_vec(char_ptr *el, _pool->data) { \
        free(*el); \
    } \
    Vec_free(_pool->data); \

#endif
