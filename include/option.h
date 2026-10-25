#ifndef UGLYC_OPTION_H
#define UGLYC_OPTION_H

#include "types.h"
#include "vector.h"
#include <stdbool.h>

#define concat(a, b) a##b

#define declare_option_for(T)                                                  \
    typedef struct {                                                           \
        T val;                                                                 \
        bool is_some;                                                          \
        bool is_none;                                                          \
    } concat(Option_, T)
declare_option_for(i32);
declare_option_for(Vec(i32));

#define Option(T) concat(Option_, T)

// NOTE: Only works in variable initialization
#define Some(v) {.val = v, .is_some = true, .is_none = false}
#define None {.is_some = false, .is_none = true}

#define Some_explicit(T, v)                                                    \
    (concat(Option_, T)) { .val = v, .is_some = true, .is_none = false }
#define None_explicit(type)                                                    \
    (concat(Option_, T)) { .is_some = false, .is_none = true }

// TODO: panic()
#define unwrap_opt(opt) ((opt.is_some) ? (opt.val) : (0))
#define expect_opt(opt, msg) ((opt.is_some) ? (opt.val) : (0))
#define unwrap_or_opt(opt, default) ((opt.is_some) ? (opt.val) : (default))

// TODO: Only declare var_name var when opt.is_some
#define if_let_Some(T, opt, var_name)                                          \
    T var_name = opt.val;                                                      \
    if (opt.is_some)

#endif
