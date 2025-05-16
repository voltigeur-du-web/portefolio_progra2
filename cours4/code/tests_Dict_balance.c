#include "utils_Dict_balance.h"
#include "Dict.h"
#include <assert.h>
#define MAX_CHAR_SIZE 50

// Déclaration structure
struct Node_tree{
    char* key;
    //const char key[MAX_CHAR_SIZE];
    int height;
    int value;
    struct Node_tree* parent;
    struct Node_tree* left;
    struct Node_tree* right;
};

typedef struct Node_tree* Node_tree_t;

struct Dico{
    Node_tree_t root;
    int size;
};

void printTree(Node_tree_t node, int depth) {
    if (node == NULL) {
        return;
    }

    // Imprimer le nœud actuel avec des espaces pour l'indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("key %s height %i\n", node->key,node->height);

    
    // Récursivement imprimer les sous-arbres gauche et droit
    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}

// Test pour create_dict
void test_create_dict() {
    Dico_t dico = create_dict();
    assert(dico != NULL);
    assert(dico->root == NULL);
    assert(dico->size == 0);
    int output = destroy_dict(dico);
    assert(output == 0);
    // Ajoutez d'autres vérifications si nécessaire
    printf("test_create_dict passed\n");
}

// Test pour add_to_dict
void test_add_to_dict() {
    Dico_t dico = create_dict();
    bool result = add_to_dict(dico, "key1", 10);
    assert(result == true);
    result = add_to_dict(dico, "key1", 20);
    assert(result == false);
    assert(dico->size == 1);
    result = add_to_dict(dico, "key2", 20);
    assert(result == true);
    assert(dico->size == 2);
    result = add_to_dict(dico, "key3", 20);
    printTree(dico->root,3);
    assert(result == true);
    assert(dico->size == 3);
    
    printTree(dico->root,2);
    int output = destroy_dict(dico);
    assert(output == 0);
    printf("test_add_to_dict passed\n");
}

// Test pour search_in_dict
void  test_exist_search_in_dict() {
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    int value;
    bool exist;
    exist=exist_in_dict(dico,"key");
    assert(!exist);
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        exist=exist_in_dict(dico,buffer);
        assert(exist == true);
        value=search_in_dict(dico,buffer);
        assert(value == i);
    }
    for(i=0;i<10;i++){
        sprintf(buffer, "String_%c", 'a' + i);
        exist=exist_in_dict(dico,buffer);
        assert(exist == false);
    }
    int output = destroy_dict(dico);
    assert(output == 0);
    printf("test_exist_search_in_dict passed\n");
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
    int output = destroy_dict(dico);
    assert(output == 0);
    printf("test_modify_dict passed\n");
}

void  test_node_heights_unbalanced() {
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    assert(dico->root->height == 9);
    Node_tree_t feuille = dico->root->right->right->right->right->right->right->right->right->right;
    assert(feuille->height == 0);
    printf("test_node_heights_unbalanced passed\n");
}



void test_rotate (){
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    dico->root = rotate_tree_left(dico->root);
    dico->root = rotate_tree_left(dico->root);
    dico->root = rotate_tree_left(dico->root);
    dico->root = rotate_tree_left(dico->root);
    dico->root = rotate_tree_left(dico->root);
    printTree(dico->root,dico->root->height);
    printf("----------------------\n");
    assert(strcmp(dico->root->key,"String f")==0);

    dico->root = rotate_tree_right(dico->root);
    dico->root = rotate_tree_right(dico->root);
    dico->root = rotate_tree_right(dico->root);
    dico->root = rotate_tree_right(dico->root);
    dico->root = rotate_tree_right(dico->root);
    printTree(dico->root,dico->root->height);
    printf("----------------------\n");
    assert(strcmp(dico->root->key,"String a")==0);

    destroy_dict(dico);
    printf("test_rotate passed\n");
}

void test_compute_height(){
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
        //printf("Root height %i\n",dico->root->height);
    }
    int h1 = compute_node_height(dico->root);
    assert(h1 == 9);
    int h2 = compute_node_height(dico->root->right->right->right->right->right->right->right->right->right);
    assert(h2 == 0);
    destroy_dict(dico);
    printf("test_compute_height passed\n");
}

void test_compute_node_balance(){
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    int b1=compute_node_balance(dico->root);
    assert(b1 == 8);
    for(i=0;i<9;i++){
        dico->root=rotate_tree_left(dico->root);
    }
    int b2=compute_node_balance(dico->root);
    assert(b2 == -8);
    destroy_dict(dico);
    printf("test_compute_balance passed\n");
}

void test_balance_tree(){
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    int value;
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    printTree(dico->root,dico->root->height);
    printf("----------------------\n");
    balance_tree(dico);
    printTree(dico->root,dico->root->height);
    printf("----------------------\n");
    assert(dico->root->height==3);
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        value=search_in_dict(dico,buffer);
        assert(value == i);
    }
    destroy_dict(dico);
    printf("test_balance_tree passed\n");
}

// Test pour remove_dict
void test_remove_dict() {
    Dico_t dico = create_dict();
    int i = 0; 
    char buffer[10];
    bool result;
    for(i=0;i<10;i++){
        sprintf(buffer, "String %c", 'a' + i);
        add_to_dict(dico, buffer, i);
    }
    assert(dico->size == 10);
    result = remove_from_dict(dico, "String b");
    assert(result == true);
    assert(dico->size == 9);
    result = exist_in_dict(dico, "String b");
    assert(result == false);
    result = remove_from_dict(dico, "String b");
    assert(result == false);
    assert(dico->size == 9);
    result = remove_from_dict(dico, "String j");
    assert(dico->size == 8);
    assert(dico->root->height == 7);
    result = remove_from_dict(dico, "String a");
    printTree(dico->root,dico->size);
    assert(result == true);
    assert(dico->size == 7);
    assert(strcmp(dico->root->key,"String c")==0);
    printf("test_remove_dict passed\n");
}

int main() {
    test_create_dict();
    test_add_to_dict();
    test_exist_search_in_dict();
    test_modify_dict();
    test_node_heights_unbalanced();
    test_rotate();
    test_compute_height();
    test_compute_node_balance();
    test_balance_tree();
    test_remove_dict();
    printf("All tests passed\n");
    return 0;
}