#include "queue.h"
#include "listes_chainees.h"

// Structure de la file
struct Queue {
    DC_List_t list;
};

// Noeud de Liste chainée double
struct Node_DC_List {
    int value;
    Node_DC_List_t next;
    Node_DC_List_t prev;
};


// Liste chainée double
struct DC_List{
    int size;
    Node_DC_List_t head;
};

// Initialise une file vide et renvoie un pointeur vers celle-ci
Queue_t new_queue() {
    Queue_t q = (Queue_t)malloc(sizeof(struct Queue));
    if (q == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    q->list = init_DC_list();
    return q;
}

// Renvoie le nombre d'éléments présents dans la file
int size_queue(Queue_t q) {
    return q->list->size;
}

// Ajoute un élément à la fin de la file
void enqueue(Queue_t q, int i) {
    append_DC_list(q->list, i);
}

// Renvoie et enlève le premier élément de la file
int dequeue(Queue_t q) {
    if (size_queue(q) == 0) {
        fprintf(stderr, "Erreur: tentative de défiler une file vide\n");
        exit(1);
    }

    Node_DC_List_t head = q->list->head;
    int value = head->value;

    if (q->list->size == 1) {
        q->list->head = NULL;
    } else {
        q->list->head = head->next;
        q->list->head->prev = NULL;
    }

    free(head);
    q->list->size--;

    return value;
}

// Libère toute la mémoire allouée pour la file
void destroy_queue(Queue_t q) {
    while (size_queue(q) > 0) {
        dequeue(q);
    }
    free(q->list);
    free(q);
}

void display_queue(Queue_t q){
    int i=0;
    int len = size_queue(q);
    int val=0;
    printf("Queue size:%i \n",len);
    display_DC_list(q->list);
}

Queue_t copy_queue(Queue_t original) {
    // Allocate memory for the new structure
    Queue_t copy = new_queue();
    Node_DC_List_t current= original->list->head;
    int i=0;
    while(i < original->list->size){
        enqueue(copy, current->value);
        current = current->next;
        i++;
    }
    return copy;
}
