#ifndef UGLYC_GC_H
#define UGLYC_GC_H

#include "vector.h"
#include "std.h"

declare_class(Memblock);
class Memblock {
    Vec(char_ptr) data;
    Vec(usize) sizes;
};

static inline Memblock Memblock_new() {
    return (Memblock){ .data = Vec_new(char_ptr), .sizes = Vec_new(usize) };
}

#define Memblock_alloc(T, bytes, membl_ptr) \
    ({ \
        Memblock *_membl = (membl_ptr); \
        T* temp_buf = (T*)malloc(bytes); \
        Vec_push(char_ptr, &_membl->data, (char*)temp_buf); \
        Vec_push(usize, &_membl->sizes, bytes); \
        temp_buf; \
    })

#define Memblock_get(T, idx, membl_ptr) \
    ({ \
        Memblock *_membl = (membl_ptr); \
        T* ptr = (T*)(_membl->data.ptr[idx]); \
        ptr; \
    })

#define Memblock_free()

#endif
