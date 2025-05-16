#include <stdio.h>
#include <assert.h>
#include "priority_queue_struct.h"

struct Stats{
    char name[50];
    int pv;
    int speed;
    int x;
    int y;
};

struct PQ {
    Stats_t players;
    int size;
    int capacity;
    int (*leq)(int, int);
};

// Fonction de comparaison pour les tests
int leq(int a, int b) {
    return a - b;
}

void test_create_pq() {
    PQ_t pq = create_pq(leq, 10);
    assert(is_pq_empty(pq));
    assert(!is_pq_full(pq));
    destroy_pq(pq);
    printf("Test create_pq passed.\n");
}

void test_add_to_pq() {
    PQ_t pq = create_pq(leq, 10);
    struct Stats s1 = {"Fighter1", 10, 5, 0, 0};
    struct Stats s2 = {"Fighter2", 20, 15, 0, 0};

    pq = add_to_pq(pq, s1);
    assert(pq->size == 1);

    pq = add_to_pq(pq, s2);
    assert(pq->size == 2);

    destroy_pq(pq);
    printf("Test add_to_pq passed.\n");
}

//PRE
//POST
void display_fighters(PQ_t picked_fighters){    
    for(int i=0;i<picked_fighters->size;i++){
    printf("Nom: %s PV: %i Speed: %i X: %i Y: %i\n",
        picked_fighters->players[i].name,
        picked_fighters->players[i].pv,
        picked_fighters->players[i].speed,
        picked_fighters->players[i].x,
        picked_fighters->players[i].y);
    }
}


void test_serve_pq() {
    PQ_t pq = create_pq(leq, 10);
    struct Stats s1 = {"Fighter1", 10, 5, 0, 0};
    struct Stats s2 = {"Fighter2", 20, 15, 0, 0};

    int i;
    for(i=0;i<10;i++){
        printf("add_to_pq %i\n",i);
        s1.pv=i;
        pq = add_to_pq(pq, s1);
    }
    assert(pq->size == 10);
    //assert(is_pq_full(pq));
     
    display_fighters(pq);

    for(int i=10;i>0;i--){
        printf("serve_pq %i\n",i);
        pq = serve_pq(pq);
        assert(pq->size==i-1);
        printf("taille pq %i\n",pq->size);
        display_fighters(pq);
    }
    assert(is_pq_empty(pq));

    destroy_pq(pq);
    printf("Test serve_pq passed.\n");
}

void test_is_pq_empty_and_full() {
    PQ_t pq = create_pq(leq, 2);
    struct Stats s1 = {"Fighter1", 10, 5, 0, 0};
    struct Stats s2 = {"Fighter2", 20, 15, 0, 0};

    assert(is_pq_empty(pq));
    pq = add_to_pq(pq, s1);
    assert(!is_pq_empty(pq));

    pq = add_to_pq(pq, s2);
    assert(is_pq_full(pq));

    destroy_pq(pq);
    printf("Test is_pq_empty_and_full passed.\n");
}

void test_swap() {
    struct Stats fighter1 = {"Fighter1", 100, 50, 10, 20};
    struct Stats fighter2 = {"Fighter2", 200, 60, 30, 40};

    // Avant l'échange
    printf("Avant l'échange:\n");
    printf("Fighter1: %s, PV: %d, Speed: %d\n", fighter1.name, fighter1.pv, fighter1.speed);
    printf("Fighter2: %s, PV: %d, Speed: %d\n", fighter2.name, fighter2.pv, fighter2.speed);

    // Échanger les contenus
    swap(&fighter1, &fighter2);

    // Après l'échange
    printf("Après l'échange:\n");
    printf("Fighter1: %s, PV: %d, Speed: %d\n", fighter1.name, fighter1.pv, fighter1.speed);
    printf("Fighter2: %s, PV: %d, Speed: %d\n", fighter2.name, fighter2.pv, fighter2.speed);

    // Vérifications
    assert(strcmp(fighter1.name, "Fighter2") == 0);
    assert(fighter1.pv == 200);
    assert(fighter1.speed == 60);
    assert(strcmp(fighter2.name, "Fighter1") == 0);
    assert(fighter2.pv == 100);
    assert(fighter2.speed == 50);

    printf("Test swap passed.\n");
}


int main() {
    test_create_pq();
    test_add_to_pq();
    test_serve_pq();
    test_is_pq_empty_and_full();
    test_swap();
    return 0;
}
