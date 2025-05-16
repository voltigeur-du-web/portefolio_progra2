#include <assert.h>
#include "listes_chainees_dict.h"

struct Node_SC_List{
    char* key;
    int value;
    struct Node_SC_List* next;
};

struct SC_List{
    Node_SC_List_t head;
    int size;
};

struct Hash_table{
    SC_List_t list;
    int size;
};

// Test function for init_SC_list
void test_init_SC_list() {
    SC_List_t list = init_SC_list();
    assert(list != NULL); // Ensure the list is initialized
    printf("test_init_SC_list passed.\n");
}

// Test function for append_SC_list
void test_append_SC_list() {
    SC_List_t list = init_SC_list();
    assert(list->size==0);
    append_SC_list(list, "key1", 10);
    assert(list->size==1);
    append_SC_list(list, "key2", 20);
    assert(list->size==2);
    printf("test_append_SC_list passed.\n");
}

void test_serve_SC_list() {
    SC_List_t list = init_SC_list();
    append_SC_list(list, "key1", 10);
    append_SC_list(list, "key2", 20);
    bool result = serve_SC_list(list,"key1");
    assert(result==true);
    assert(list->size==1);
    result = serve_SC_list(list,"key1");
    assert(result==false);
    assert(list->size==1);
    result = serve_SC_list(list,"key2");
    assert(result==true);
    assert(list->size==0);
    printf("test_serve_SC_list passed.\n");
}


// Test function for display_SC_list
void test_display_SC_list() {
    SC_List_t list = init_SC_list();
    append_SC_list(list, "key1", 10);
    append_SC_list(list, "key2", 20);
    printf("Expected output:\nkey1: 10\nkey2: 20\nActual output:\n");
    display_SC_list(list); // Verify visually for now
    printf("test_display_SC_list passed.\n");
}

// Test function for destroy_SC_list
void test_destroy_SC_list() {
    SC_List_t list = init_SC_list();
    append_SC_list(list, "key1", 10);
    destroy_SC_list(list);
    printf("test_destroy_SC_list passed.\n");
}

// Main function to run all tests
int main() {
    test_init_SC_list();
    test_append_SC_list();
    test_serve_SC_list();
    test_display_SC_list();
    test_destroy_SC_list();
    printf("All tests passed.\n");
    return 0;
}