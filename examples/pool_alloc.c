#include "../include/uglyc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

func(int, main)(void) {
    PoolAlloc p = PoolAlloc_new();

    i32* ptr = PoolAlloc_alloc(i32, 16, &p);
    PoolAlloc_realloc(i32, ptr, 8, &p);

    PoolAlloc_free(&p);
    return 0;
}
