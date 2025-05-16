#include <assert.h>
#include "Dict.h"

// Test pour create_dict
void test_create_dict() {
    Dico_t dico = create_dict();
    assert(dico != NULL);
    printf("test_create_dict passed\n");
}

// Test pour add_to_dict
void test_add_to_dict() {
    Dico_t dico = create_dict();
    bool result = add_to_dict(dico, "key1", 10);
    assert(result == true);
    result = add_to_dict(dico, "key1", 20);
    assert(result == false);
    printf("test_add_to_dict passed\n");
}

// Test pour search_in_dict
void test_search_in_dict() {
    Dico_t dico = create_dict();
    add_to_dict(dico, "key1", 10);
    int value = search_in_dict(dico, "key1");
    assert(value == 10);
    printf("test_search_in_dict passed\n");
}

// Test pour exist_in_dict
void test_exist_in_dict() {
    Dico_t dico = create_dict();
    add_to_dict(dico, "key1", 10);
    bool result = exist_in_dict(dico, "key1");
    assert(result == true);
    result = exist_in_dict(dico, "key2");
    assert(result == false);
    printf("test_exist_in_dict passed\n");
}

// Test pour remove_dict
void test_remove_dict() {
    Dico_t dico = create_dict();
    add_to_dict(dico, "key1", 10);
    bool result = remove_from_dict(dico, "key1");
    assert(result == true);
    result = remove_from_dict(dico, "key1");
    assert(result == false);
    printf("test_remove_dict passed\n");
}

// Test pour modify_dict
void test_modify_dict() {
    Dico_t dico = create_dict();
    add_to_dict(dico, "key1", 10);
    bool result = modify_in_dict(dico, "key1", 20);
    assert(result == true);
    int value = search_in_dict(dico, "key1");
    assert(value == 20);
    result = modify_in_dict(dico, "key2", 30);
    assert(result == false);
    printf("test_modify_dict passed\n");
}

int main() {
    test_create_dict();
    test_add_to_dict();
    test_search_in_dict();
    test_exist_in_dict();
    test_remove_dict();
    test_modify_dict();
    printf("All tests passed\n");
    return 0;
}