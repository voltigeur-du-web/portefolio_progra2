#include <stdio.h>
#include <assert.h>
#include "priority_queue.h"

// Fonction de comparaison pour la file de priorité
int leq(int a, int b) {
    return a - b;
}

void test_create_pq() {
    PQ_t pq = create_pq(leq);
    assert(is_pq_empty(pq));
    assert(!is_pq_full(pq));
    printf("test_create passed\n");
}

void test_add_to_pq() {
    PQ_t pq = create_pq(leq);
    pq = add_to_pq(pq, 10);
    assert(!is_pq_empty(pq));
    assert(peek_pq(pq) == 10);
    printf("test_enqueue passed\n");
}

void test_serve_pq() {
    PQ_t pq = create_pq(leq);
    pq = add_to_pq(pq, 10);
    pq = add_to_pq(pq, 20);
    pq = serve_pq(pq);
    assert(peek_pq(pq) == 20);
    printf("test_serve passed\n");
}

void test_is_pq_empty() {
    PQ_t pq = create_pq(leq);
    assert(is_pq_empty(pq));
    pq = add_to_pq(pq, 10);
    assert(!is_pq_empty(pq));
    printf("test_is_empty passed\n");
}

void test_is_pq_full() {
    PQ_t pq = create_pq(leq);
    assert(!is_pq_full(pq));
    // Assuming the maximum size is known, for example, 100
    for (int i = 0; i < 100; i++) {
        pq = add_to_pq(pq, i);
    }
    assert(is_pq_full(pq));
    printf("test_is_full passed\n");
}

void test_peek_pq() {
    PQ_t pq = create_pq(leq);
    pq = add_to_pq(pq, 10);
    pq = add_to_pq(pq, 20);
    assert(peek_pq(pq) == 10);
    pq = serve_pq(pq);
    assert(peek_pq(pq) == 20);
    printf("test_peek passed\n");
}

int main() {
    test_create_pq();
    test_add_to_pq();
    test_serve_pq();
    test_is_pq_empty();
    test_is_pq_full();
    test_peek_pq();
    printf("All tests passed\n");
    return 0;
}
