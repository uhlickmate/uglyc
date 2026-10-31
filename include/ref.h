#ifndef UGLYC_REF_H
#define UGLYC_REF_H

#include "types.h"
#include "std.h"

#define declare_ref_for(T)                                                  \
    typedef struct {                                                           \
        T* ptr;                                                                 \
        size_t* ref_count; \
        AllocType alloc_type; \
    } concat(Ref_, T)
declare_ref_for(i32);

#define Ref(T) concat(Ref_, T)

#define Ref_new_heap(T, v) \
    ({ \
        size_t *ref_c = malloc(32); \
        *ref_c = 1; \
        Ref(T) r = (Ref(T)){ .ptr = v, .ref_count = ref_c, .alloc_type = Heap }; \
        r; \
    })

#define Ref_new_stack(T, v) \
    ({ \
        size_t *ref_c = malloc(32); \
        *ref_c = 1; \
        Ref(T) r = (Ref(T)){ .ptr = v, .ref_count = ref_c, .alloc_type = Stack }; \
        r; \
    })

#define Ref_clone(T, ref_ptr) \
    ({ \
        Ref(T) *_ref = (ref_ptr); \
        *(_ref->ref_count)++; \
        Ref(T) ref_out = (Ref(T)){ .ptr = _ref->ptr, .ref_count = _ref->ref_count }; \
        ref_out; \
    })


#define Ref_free(ref_ptr) \
    if ((ref_ptr) != NULL & (ref_ptr)->ref_count != NULL) { \
        (*(ref_ptr)->ref_count)--; \
        if (*(ref_ptr)->ref_count == 0) { \
            free((ref_ptr)->ptr); \
            free((ref_ptr)->ref_count); \
        } \
        (ref_ptr)->ptr = NULL; \
        (ref_ptr)->ref_count = NULL; \
    }

#define Ref_has_ptr(ref) (ref.ptr != NULL)

#define Ref_get_unsafe(ref) *(ref).ptr
#define Ref_try_get(T, ref) \
    ({ \
        Option(T) opt = None_explicit(T); \
        if ((ref).ptr != NULL && (ref).ref_count != NULL) { \
            opt = Some_explicit(T, (ref).ptr); \
        } \
        opt; \
    })

#endif
