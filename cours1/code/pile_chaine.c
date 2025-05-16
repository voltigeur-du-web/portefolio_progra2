#include "pile.h"
#include "listes_chainees.h"


struct Node_DC_List {
    int value;
    Node_DC_List_t next;
    Node_DC_List_t prev;
};

struct DC_List{
    int size;
    Node_DC_List_t head;
};

struct Stack {
    DC_List_t list;
};

Stack_t new_stack() {
    Stack_t s = (Stack_t)malloc(sizeof(struct Stack));
    if (s == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    s->list = init_DC_list();
    return s;
}

int size_stack(Stack_t s) {
    return s->list->size;
}

void add_to_stack(Stack_t s, int i) {
    append_DC_list(s->list, i);
}

int remove_from_stack(Stack_t s) {
    if (size_stack(s) == 0) {
        fprintf(stderr, "Erreur: tentative de retirer un élément d'une pile vide\n");
        exit(1);
    }
    Node_DC_List_t current = s->list->head;
    Node_DC_List_t previous = NULL;

    // Traverse to the end of the list
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    // Remove the last element
    int value = current->value;
    if (previous != NULL) {
        previous->next = NULL;
    } else {
        // If the list becomes empty
        s->list->head = NULL;
    }
    free(current);
    s->list->size--;
    return value;
}

void destroy_stack(Stack_t s) {
    if (s != NULL) {
        Node_DC_List_t current = s->list->head;
        while (current != NULL) {
            Node_DC_List_t next = current->next;
            free(current);
            current = next;
        }
        free(s->list);
        free(s);
    }
}

void display_stack(Stack_t s) {
    printf("Stack size: %i\n", size_stack(s));
    Node_DC_List_t current = s->list->head;
    while (current != NULL) {
        printf("%i\n", current->value);
        current = current->next;
    }
}

