#include "../include/uglyc.h"
#include <stdio.h>

class {
    i32 x;
    i32 y;
}
Object;

impl(Object, Object, new)(i32 x, i32 y) {
    x += 1;
    y -= 1;
    return (Object){.x = x, .y = y};
}

func(int) main() {

    Object o = Object_new(10, 5);

    return 0;
}
