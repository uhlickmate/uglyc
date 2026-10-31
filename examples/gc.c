#include "../include/uglyc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

func(int, main)(void) {

    Memblock a = Memblock_new();

    Vec(char_ptr) v = Vec_new(char_ptr);
    i32 num = 15;

    i32* ptr = Memblock_alloc(i32, sizeof(i32), &a);

    *ptr = 10;

    i32* ptr_new = Memblock_get(i32, 0, &a);
    printf("%d \n", *ptr_new);

    return 0;
}
