#include "../include/uglyc.h"
#include <stdio.h>

int main() {
    String s =
        String_from("My new awesome lovely nice beautiful string thingy");

    char char_buf[128];
    String_to_char_buf(s, char_buf, sizeof(char_buf));

    printf("%s \n", char_buf);
}
