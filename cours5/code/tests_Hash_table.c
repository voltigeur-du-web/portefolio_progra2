#include <assert.h>
#include <stdio.h>
#include "Hash_table.h"  // Assurez-vous que ce fichier contient les déclarations de votre header
#include "listes_chainees_dict.h" 
#define MAX_TABLE_SIZE 10

struct SC_List{
    Node_SC_List_t head;
    int size;
};

struct Hash_table{
    SC_List_t list;
    int size;
    int capacity;
    int load;
};

void test_hash() {
    const char* key = "test";
    int hash_value = hash(key,MAX_TABLE_SIZE);
    // Vérifiez que la valeur de hachage est dans une plage attendue
    assert(hash_value >= 0);
    printf("test_hash passed\n");
}

void test_create_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    assert(table != NULL);
    assert(table->size == 0);
    for(int i=0;i<MAX_TABLE_SIZE;i++){
        assert(table[i].list->size==0);
    }

    destroy_hash_table(table);
    printf("test_create_hash_table passed\n");
}

void test_add_to_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    bool result;
    const char* key = "key1";
    int value = 42;

    result = add_to_hash_table(&table, "key1", 42);
    assert(result == true);
    assert(exist_in_hash_table(table, key) == true);
    assert(search_in_hash_table(table, key) == value);

    int i;
    int j;
    char buffer[50]; 
    for(i=0;i<50;i++){
        j= i <= 25 ? 0 : 1;
        sprintf(buffer, "%c%c",'a'+j,'a'+(i%26));
        printf("Doing key %s\n",buffer);
        result = add_to_hash_table(&table, buffer, i);
        assert(result == true);
        assert(exist_in_hash_table(table, buffer) == true);
        assert(search_in_hash_table(table, buffer) == i);
        printf("Taille de list %i = %i\n",hash(buffer,table->capacity),table[hash(buffer,table->capacity)].list->size);
    }

    destroy_hash_table(table);
    printf("test_add_to_hash_table passed\n");
}

void test_exist_in_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    const char* key = "key1";
    int value = 42;
    add_to_hash_table(&table, key, value);
    assert(exist_in_hash_table(table, key) == true);
    assert(exist_in_hash_table(table, "nonexistent_key") == false);
    printf("test_exist_in_hash_table passed\n");
}

void test_search_in_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    const char* key = "key1";
    int value = 42;
    add_to_hash_table(&table, key, value);
    assert(search_in_hash_table(table, key) == value);
    printf("test_search_in_hash_table passed\n");
}

void test_remove_in_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    int i;
    int j;
    char buffer[50]; 
    bool result;
    for(i=0;i<50;i++){
        j= i <= 25 ? 0 : 1;
        sprintf(buffer, "%c%c",'a'+j,'a'+(i%26));
        add_to_hash_table(&table, buffer, i);
    }
    for(i=0;i<50;i++){
        j= i <= 25 ? 0 : 1;
        sprintf(buffer, "%c%c",'a'+j,'a'+(i%26));
        result = remove_in_hash_table(table, buffer);
        assert(result==true);
        printf("Taille de list %i = %i\n",hash(buffer,table->capacity),table[hash(buffer,table->capacity)].list->size);
    }
    for(i=0;i<50;i++){
        j= i <= 25 ? 0 : 1;
        sprintf(buffer, "%c%c",'a'+j,'a'+(i%26));
        result = remove_in_hash_table(table, buffer);
        assert(result==false);
    }
    printf("test_remove_in_hash_table passed\n");
}

void test_modify_in_hash_table() {
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    const char* key = "key1";
    int value = 42;
    add_to_hash_table(&table, key, value);

    int new_value = 100;
    bool result = modify_in_hash_table(table, key, new_value);
    assert(result == true);
    assert(search_in_hash_table(table, key) == new_value);

    result = modify_in_hash_table(table, "nonexistent_key", 50);
    assert(result == false);

    printf("test_modify passed\n");
}

int main() {
    test_hash();
    test_create_hash_table();
    test_add_to_hash_table();
    test_exist_in_hash_table();
    test_search_in_hash_table();
    test_remove_in_hash_table();
    test_modify_in_hash_table();

    printf("All tests passed!\n");
    return 0;
}
