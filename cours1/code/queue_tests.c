#include <assert.h>
#include "queue.h"

void test_new_queue() {
    Queue_t q = new_queue();
    assert(size_queue(q) == 0);
    destroy_queue(q);
}

void test_enqueue_dequeue() {
    Queue_t q = new_queue();
    enqueue(q, 10);
    assert(size_queue(q) == 1);
    assert(dequeue(q) == 10);
    assert(size_queue(q) == 0);
    destroy_queue(q);
}

void test_multiple_enqueue_dequeue() {
    Queue_t q = new_queue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    assert(size_queue(q) == 3);
    assert(dequeue(q) == 10);
    assert(size_queue(q) == 2);
    assert(dequeue(q) == 20);
    assert(size_queue(q) == 1);
    assert(dequeue(q) == 30);
    assert(size_queue(q) == 0);
    destroy_queue(q);
}

void test_dequeue_empty() {
    Queue_t q = new_queue();
    assert(size_queue(q) == 0);
    destroy_queue(q);
}

int main() {
    test_new_queue();
    test_enqueue_dequeue();
    test_multiple_enqueue_dequeue();
    test_dequeue_empty();
    printf("Tous les tests passent !\n");
    return 0;
}
