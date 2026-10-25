#ifndef UGLYC_RESUTL_H
#define UGLYC_RESUTL_H

#include "types.h"
#include "vector.h"
#include <stdbool.h>

#define concat(a, b) a##b

#define declare_result_for(T, E)                                               \
    typedef struct {                                                           \
        union {                                                                \
            T ok;                                                              \
            E err;                                                             \
        } val;                                                                 \
        bool is_ok;                                                            \
        bool is_err;                                                           \
    } concat(Result_, T)
declare_result_for(i32, i32);
declare_result_for(Vec(i32), i32);

// NOTE: Only works in variable initialization
#define ok(v) {.is_ok = true, .is_err = false, .val.ok = v}
#define err(e) {.is_ok = false, .is_err = false, .val.err = e}

#define ok_explicit(T, v)                                                      \
    (T) { .is_ok = true, .is_err = false, .val.ok = v }
#define err_explicit(T, e)                                                     \
    (T) { .is_ok = false, .is_err = false, .val.err = e }

// TODO: panic()
#define unwrap_res(res) ((res.is_ok) ? (res.val.ok) : (0))
#define expect_res(res, msg) ((res.is_ok) ? (res.val.ok) : (0))
#define unwrap_or_res(res, default) ((res.is_ok) ? (res.val.ok) : (default))

#endif
