#ifndef UGLYC_TYPES_H
#define UGLYC_TYPES_H

#include <stdint.h>
#include <stdlib.h>

// Mapping to Rust-style names
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#ifdef __SIZEOF_INT128__
typedef __int128 i128;
typedef unsigned __int128 u128;
#endif

typedef ssize_t isize;
typedef size_t usize;

typedef float f32;
typedef double f64;

#endif
