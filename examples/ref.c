#include "../include/uglyc.h"
#include <stdio.h>

func(int, main)(void) {

    i32* org = malloc(32);
    *org = 10;

    Ref(i32) ref = Ref_new_heap(i32, org);
    Ref(i32) ref_cloned = Ref_clone(i32, &ref);


    printf("%d \n", Ref_has_ptr(ref));
    Ref_free(&ref);
    Option(Ref(i32)) opt = Ref_try_get(Ref(i32), ref);
    printf("Is some: %d \n", opt.is_some);
    printf("%d \n", Ref_has_ptr(ref_cloned));
    Ref_free(&ref_cloned);

    printf("%d \n", Ref_has_ptr(ref));

    return 0;
}
