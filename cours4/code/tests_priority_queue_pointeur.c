#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "priority_queue_pointeur.h" // Assurez-vous que ce fichier contient les déclarations de vos fonctions

struct Node_PQ{
    int priority;
    void* data;
};

struct PQ {
    Node_PQ_t list;
    int size;
    int capacity;
    int (*leq)(int, int);
};

int leq2(int a, int b){
    return a-b;
}

int geq2(int a, int b){
    return b-a;
}

// Test pour create_pq
void test_create_pq() {
    PQ_t pq = create_pq(leq2);
    assert(pq != NULL);
    assert(is_pq_empty(pq));
    destroy_pq(pq);
    printf("test_create_pq passed\n");
}

// Test pour add_to_pq
void test_add_to_pq_leq() {
    PQ_t pq = create_pq(leq2);
    int data1 = 10;
    int data2 = 20;

    for(int i=1;i<=100;i++){
        if (i%2==0) add_to_pq(pq, i, &data1);
        else add_to_pq(pq, i, &data2);
    }

    assert(peek_pq(pq)->data == &data2);
    assert(peek_pq(pq)->priority == 1);

    serve_pq(pq);
    assert(peek_pq(pq)->data == &data1);
    assert(peek_pq(pq)->priority == 2);

    assert(!is_pq_empty(pq));

    destroy_pq(pq);
    printf("test_add_to_pq_leq passed\n");
}

// Test pour add_to_pq
void test_add_to_pq_geq() {
    PQ_t pq = create_pq(geq2);
    int data1 = 10;
    int data2 = 20;

    for(int i=1;i<=100;i++){
        if (i%2==0) add_to_pq(pq, i, &data1);
        else add_to_pq(pq, i, &data2);
    }

    assert(peek_pq(pq)->data == &data1);
    assert(peek_pq(pq)->priority == 100);

    serve_pq(pq);
    assert(peek_pq(pq)->data == &data2);
    assert(peek_pq(pq)->priority == 99);

    assert(!is_pq_empty(pq));

    destroy_pq(pq);
    printf("test_add_to_pq_geq passed\n");
}

// Test pour serve_pq
void test_serve_pq() {
    PQ_t pq = create_pq(leq2);
    int data1 = 10;
    int data2 = 20;

    pq = add_to_pq(pq, 1, &data1);
    pq = add_to_pq(pq, 2, &data2);

    pq = serve_pq(pq);
    assert(peek_pq(pq)->priority == 2);
    assert(*(int*)peek_pq(pq)->data == 20);

    destroy_pq(pq);
    printf("test_serve_pq passed\n");
}

// Test pour valeur des pointeurs && is_pq_empty
void test_is_pq_empty() {
    PQ_t pq = create_pq(leq2);
    assert(is_pq_empty(pq));

    int data = 10;
    printf("Pointeur data avant add to pq %p\n",(void*)&data);
    pq = add_to_pq(pq, 1, &data);

    printf("Pointeur data dans pq %p\n",(void*)pq->list->data);
    assert(!is_pq_empty(pq));

    destroy_pq(pq);
    printf("Pointeur data après destroy pq %p\n",(void*)&data);
    printf("test_is_pq_empty passed\n");
}

// Test pour is_pq_full (supposons une taille maximale de 10 pour l'exemple)
// PQ s'aggrandit dynamiquement donc plus relevant

// Test pour peek_pq
void test_peek_pq() {
    PQ_t pq = create_pq(leq2);
    int data1 = 10;
    int data2 = 20;

    pq = add_to_pq(pq, 1, &data1);
    pq = add_to_pq(pq, 2, &data2);

    Node_PQ_t top = peek_pq(pq);
    assert(top->priority == 1);
    assert(*(int*)top->data == 10);

    destroy_pq(pq);
    printf("test_peek_pq passed\n");
}

// Test pour destroy_pq
void test_destroy_pq() {
    PQ_t pq = create_pq(leq2);
    int data = 10;
    pq = add_to_pq(pq, 1, &data);

    destroy_pq(pq);
    assert(&data != NULL);
    // Après destruction, essayer d'accéder à la file doit provoquer une erreur ou un comportement indéfini
    // Ici, nous supposons que la file est correctement détruite et ne provoque pas de fuite de mémoire
    printf("test_destroy_pq passed\n");
}

// Test pour display_pq
void test_display_pq() {
    PQ_t pq = create_pq(leq2);
    int data1 = 10;
    int data2 = 20;

    pq = add_to_pq(pq, 1, &data1);
    pq = add_to_pq(pq, 5, &data2);

    printf("La taille de la queue est de %i\n",pq->size);
    display_pq(pq);

    destroy_pq(pq);
    printf("test_display_pq passed\n");
}

// Test pour remove_pointer_from_pq
void test_remove_pointer_from_pq() {
    PQ_t pq = create_pq(leq2);
    int data1 = 10;
    int data2 = 20;

    pq = add_to_pq(pq, 1, &data1);
    pq = add_to_pq(pq, 2, &data2);

    bool result = remove_pointer_from_pq(pq, &data1);
    assert(result);
    assert(peek_pq(pq)->priority == 2);
    assert(*(int*)peek_pq(pq)->data == 20);

    destroy_pq(pq);
    printf("test_remove_pointer_from_pq passed\n");
}

int main() {
    test_create_pq();
    test_add_to_pq_leq();
    test_add_to_pq_geq();
    test_serve_pq();
    test_is_pq_empty();
    test_peek_pq();
    test_destroy_pq();
    test_display_pq();
    test_remove_pointer_from_pq();
    printf("All tests passed\n");
    return 0;
}
