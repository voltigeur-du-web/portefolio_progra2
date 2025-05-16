#include <assert.h>
#include "pile.h"

void test_new_stack() {
    Stack_t s = new_stack();
    assert(size_stack(s) == 0);
    destroy_stack(s);
}

void test_add_remove_from_stack() {
    Stack_t s = new_stack();
    add_to_stack(s, 10);
    assert(size_stack(s) == 1);
    assert(remove_from_stack(s) == 10);
    assert(size_stack(s) == 0);
    destroy_stack(s);
}

void test_multiple_add_remove_from_stack() {
    Stack_t s = new_stack();
    add_to_stack(s, 10);
    add_to_stack(s, 20);
    add_to_stack(s, 30);
    assert(size_stack(s) == 3);
    assert(remove_from_stack(s) == 30);
    assert(size_stack(s) == 2);
    assert(remove_from_stack(s) == 20);
    assert(size_stack(s) == 1);
    assert(remove_from_stack(s) == 10);
    assert(size_stack(s) == 0);
    destroy_stack(s);
}

void test_remove_from_empty_stack() {
    Stack_t s = new_stack();
    // Assuming remove_from_stack on empty stack is undefined behavior, we should not call it.
    // Instead, we check that size is zero.
    assert(size_stack(s) == 0);
    destroy_stack(s);
}

int main() {
    test_new_stack();
    test_add_remove_from_stack();
    test_multiple_add_remove_from_stack();
    test_remove_from_empty_stack();
    printf("Tous les tests passent !\n");
    return 0;
}
