#include "../include/uglyc.h"
#include <stdio.h>

int main() {
    string_t s =
        string_from("My new awesome lovely nice beautiful string thingy");

    char char_buf[128];
    string_to_char_buf(s, char_buf, sizeof(char_buf));

    printf("%s \n", char_buf);
}
