#include "queue.h"

struct Queue {
    int size;
    int capacity;
    int *tab;
    int offset;
    int last;
};

Queue_t new_queue() {
    Queue_t q = (Queue_t)malloc(sizeof(struct Queue));
    if (q == NULL) {
        return NULL;
    }
    q->tab = (int *)malloc(100 * sizeof(int));
    if (q->tab == NULL) {
        free(q);
        return NULL;
    }
    q->size = 0;
    q->offset = 0;
    q->last = -1;
    q->capacity = 100;
    return q;
}

int size_queue(Queue_t q) {
    return q->size;
}

void enqueue(Queue_t q, int i) {
    if (q->size == q->capacity) {
        q->capacity += 100;
        q->tab = (int *)realloc(q->tab, q->capacity * sizeof(int));
        if (q->tab == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
    }
    q->tab[q->size] = i;
    q->size++;
    q->last++;
}

void display(Queue_t q) {
    int i = q->offset;
    int len = size_queue(q);
    printf("Queue size: %i\n", len);
    printf("Queue capacity: %i\n", q->capacity);
    printf("Queue offset: %i\n", q->offset);
    printf("Queue last: %i\n", q->last);
    while (i <= q->last) {
        printf("%i\n", q->tab[i]);
        i++;
    }
}

int dequeue(Queue_t q) {
    if (size_queue(q) == 0) {
        fprintf(stderr, "Erreur: tentative de défiler une file vide\n");
        exit(1);
    }
    int first = q->tab[q->offset];
    q->offset++;
    q->size--;

    if (q->capacity > 100 && q->size < q->capacity && q->size % 100 == 0) {
        q->capacity = q->size;
        int *new_tab = (int *)malloc(q->capacity * sizeof(int));
        if (new_tab == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
        for (int i = 0; i < q->size; i++) {
            new_tab[i] = q->tab[q->offset + i];
        }
        free(q->tab);
        q->tab = new_tab;
        q->offset = 0;
        q->last = q->size - 1;
    }
    return first;
}

void destroy_queue(Queue_t q) {
    if (q != NULL) {
        if (q->tab != NULL) {
            free(q->tab);
            q->tab = NULL;
        }
        free(q);
        q = NULL;
    }
}

