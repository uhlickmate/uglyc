#include "../include/uglyc.h"

declare_class(Person);
class Person {
    String name;
    i32 age;
};

// Or also:
class_declared {
    String name;
    i32 age;
} PersonOther;

impl(Person, new, Person)(String name, i32 age) {
    return (Person){ .name = name, .age = age };
}
impl(Person, get_age, i32)(Person *self) {
    return self->age;
}

func(int, main)(void) {
    Person me = Person_new(String_from("John Foo"), 25);
    char* name = String_to_new_char_buf(me.name, me.name.len);

    assert_eq(me.name, method(String, from)("John Foo"));
    assert_eq(Person_get_age(&me), 25);

    String_free(&me.name);
    free(name);

    return 0;
}
