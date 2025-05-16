#include "pile.h"

struct Stack {
    int size;
    int capacity;
    int *tab;
};

Stack_t new_stack() {
    Stack_t s = (Stack_t)malloc(sizeof(struct Stack));
    if (s == NULL) {
        return NULL;
    }
    s->tab = (int *)malloc(100 * sizeof(int));
    if (s->tab == NULL) {
        free(s);
        return NULL;
    }
    s->size = 0;
    s->capacity = 100;
    return s;
}

int size_stack(Stack_t s) {
    return s->size;
}

void add_to_stack(Stack_t s, int i) {
    if (s->size == s->capacity) {
        s->capacity += 100;
        s->tab = (int *)realloc(s->tab, s->capacity * sizeof(int));
        if (s->tab == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
    }
    s->tab[s->size] = i;
    s->size++;
}

int remove_from_stack(Stack_t s) {
    if (size_stack(s) == 0) {
        fprintf(stderr, "Erreur: tentative de retirer un élément d'une pile vide\n");
        exit(1);
    }
    s->size--;
    return s->tab[s->size];
}

void destroy_stack(Stack_t s) {
    if (s != NULL) {
        if (s->tab != NULL) {
            free(s->tab);
            s->tab = NULL;
        }
        free(s);
        s = NULL;
    }
}

void display_stack(Stack_t s) {
    printf("Stack size: %i\n", size_stack(s));
    printf("Stack capacity: %i\n", s->capacity);
    for (int i = 0; i < s->size; i++) {
        printf("%i\n", s->tab[i]);
    }
}
