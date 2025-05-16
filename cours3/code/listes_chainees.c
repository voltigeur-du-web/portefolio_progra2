#include <stdio.h>
#include <stdlib.h>
#include "listes_chainees.h"

// Noeud de Liste chainée simple
struct Node_SC_List {
    int value;
    Node_SC_List_t next;
};

// Liste chainée simple
struct SC_List{
    int size;
    Node_SC_List_t head;
} ;

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

// Noeud de Liste chainée double circulaire
struct Node_DC_Circ_List {
    int value;
    Node_DC_Circ_List_t next;
    Node_DC_Circ_List_t prev;
} ;

// Liste chainée double circulaire
 struct DC_Circ_List{
    int size;
    Node_DC_Circ_List_t head;
};

//Initialisation d'une liste chainée simple
//PRE: Néant
//POST: Retourne une liste chainée simple vide (sans noeuds) - avec une tête allouée en mémoire
SC_List_t init_SC_list(void){
    SC_List_t list = malloc(sizeof(struct SC_List));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    list->size=0;
    list->head=NULL;
    return list;
}

//Ajout d'un noeud à la fin de la liste chainée simple
//PRE: list est une liste chainée simple initialisée
//POST: Ajoute un noeud à la fin de la liste chainée simple
void append_SC_list(SC_List_t list, int value){
        Node_SC_List_t new = malloc(sizeof(struct Node_SC_List));
        if (new == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
        new->value=value;
        new->next=NULL;

        if(list->size==0){
            list->head=new;
        }
        else if (list->size>1){
            Node_SC_List_t previous = list->head;
            while (previous->next != NULL ){
                previous = previous->next;
            }
            previous->next = new;
        }
        list->size++;
}

//Affichage de la liste chainée simple
//PRE: list est une liste chainée simple initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée simple
void display_SC_list(SC_List_t list){
    Node_SC_List_t current = list->head;
    printf("Liste chainée simple\n");
    while (current != NULL){
        printf("%i\n", current->value);
        current = current->next;
    }
}

// Fonction auxiliaire pour supprimer un noeud
void destroy_Node_SC_list(Node_SC_List_t node) {
    if (node == NULL) {
        return;
    }
    if (node->next != NULL) {
        destroy_Node_SC_list(node->next);
    }
    free(node);
}

// Destruction de la liste chaînée simple
//PRE: list est une liste chaînée simple initialisée
//POST: Détruit la liste chaînée et ses noeuds
void destroy_SC_list(SC_List_t list) {
    if (list == NULL) {
        return;
    }
    destroy_Node_SC_list(list->head);
    list->head = NULL;
    free(list); 
}


//Initialisation d'une liste chaînée double
//PRE: Néant
//POST: Retourne une liste chaînée double vide (sans noeuds) - avec une tête allouée en mémoire
DC_List_t init_DC_list(void){
    DC_List_t list = (DC_List_t)malloc(sizeof(struct DC_List));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    list->size=0;
    list->head=NULL;
    return list;
}

//Ajout d'un noeud à la fin de la liste chainée double
//PRE: list est une liste chainée double initialisée
//POST: Ajoute un noeud à la fin de la liste chainée double
void append_DC_list(DC_List_t list, int value){
        Node_DC_List_t new = malloc(sizeof(struct Node_DC_List));
        if (new == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
        new->value=value;
        new->next=NULL;
        new->prev=NULL;
        
        if(list->size==0){
            list->head=new;
        }

        else if (list->size>0){
            struct Node_DC_List *previous = list->head;
            while (previous->next != NULL ){
                previous = previous->next;
            }
            previous->next = new;
            if(list->size>1){
                new->prev=previous;
            }
        }
        list->size++;
}

//Affichage de la liste chainée double
//PRE: list est une liste chainée double initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double
void display_DC_list(DC_List_t list){
    Node_DC_List_t current = list->head;
    printf("Liste chainée double\n");
    while (current != NULL){
        printf("%i\n", current->value);
        current = current->next;
    }
}

//Display previous-current-next 
//PRE: list est une liste chainée double initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double avec les valeurs des noeuds précédents et suivants
void display_prev_now_next_DC_list(DC_List_t list){
    Node_DC_List_t current = list->head;
    Node_DC_List_t previous = NULL;
    printf("Liste chainée double previous-current-next\n");
    while (current != NULL){
        if(current->prev != NULL){
            previous = current->prev;
            printf("previous: %i\n", previous->value);
        }
        printf("current: %i\n", current->value);
        current = current->next;
        if(current != NULL){
            printf("next: %i\n", current->value);
        }
    }
}

// Fonction auxiliaire pour supprimer un noeud
void destroy_Node_DC_list(Node_DC_List_t node) {
    if (node == NULL) {
        return;
    }
    if (node->next != NULL) {
        destroy_Node_DC_list(node->next);
    }
    free(node);
}

// Destruction de la liste chaînée simple
//PRE: list est une liste chaînée simple initialisée
//POST: Détruit la liste chaînée et ses noeuds
void destroy_DC_list(DC_List_t list) {
    if (list == NULL) {
        return;
    }
    destroy_Node_DC_list(list->head);
    list->head = NULL;
    free(list); 
}

//Initialisation d'une liste chainée double circulaire
//PRE: Néant
//POST: Retourne une liste chainée double circulaire vide (sans noeuds) - avec une tête allouée en mémoire
DC_Circ_List_t init_DC_Circ_list(void){
    DC_Circ_List_t list = malloc(sizeof(struct DC_Circ_List));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    list->size=0;
    list->head=NULL;
    return list;
}

//Ajout d'un noeud à la fin de la liste chainée double circulaire
//PRE: list est une liste chainée double circulaire initialisée
//POST: Ajoute un noeud à la fin de la liste chainée double circulaire
void append_DC_Circ_list(DC_Circ_List_t list, int value){
    Node_DC_Circ_List_t new = malloc(sizeof(struct Node_DC_Circ_List));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    new->value=value;
    new->next=NULL;
    new->prev=NULL;
    
    if(list->size==0){
        list->head=new;
    }

    else if (list->size==1){
        Node_DC_Circ_List_t first = list->head;
        first->next = new;
        first->prev = new;
        new->prev = first;
        new->next = first;
    }

    else if (list->size>1){
        Node_DC_Circ_List_t first = list->head;
        Node_DC_Circ_List_t last = first->prev;
        first->prev = new;
        new->prev = last;
        new->next = first;
        last->next = new;
    }
    list->size++;
}

//Affichage de la liste chainée double circulaire sens backward et forward
//PRE: list est une liste chainée double circulaire initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double circulaire dans les deux sens
void display_DC_Circ_list(DC_Circ_List_t list){
    Node_DC_Circ_List_t forward = list->head;
    Node_DC_Circ_List_t backward = list->head;
    printf("Liste chainée double circulaire backward:\n");
    for(int i=0; i<list->size; i++){
        printf("Forward: %i\n", forward->value);
        printf("Backward: %i\n", backward->value);
        forward = forward->next;
        backward = backward->prev;
    }
}

// Destruction de la liste chaînée circulaire
void destroy_DC_Circ_list(DC_Circ_List_t list) {
    int counter=0;
    Node_DC_Circ_List_t current=list->head;
    Node_DC_Circ_List_t previous=NULL;
    while(counter<list->size){
        previous=current;
        current=current->next;
        previous->next=NULL;
        previous->prev=NULL;
        free(previous);
        counter++;
    }
    free(list);
}

//tests on listes_chainees.c
// int main(){
//     SC_List_t my_SC_list = init_SC_list();
//     DC_List_t my_DC_list = init_DC_list();
//     DC_Circ_List_t my_DC_Circ_list = init_DC_Circ_list();

//     for (int i=0; i<10; i++){
//         append_SC_list(my_SC_list, i);
//         append_DC_list(my_DC_list, i);
//         append_DC_Circ_list(my_DC_Circ_list, i);
//     }

//     display_SC_list(my_SC_list);
//     destroy_SC_list(my_SC_list);

//     display_DC_list(my_DC_list);
//     destroy_DC_list(my_DC_list);

//     display_prev_now_next_DC_list(my_DC_list);

//     display_DC_Circ_list(my_DC_Circ_list);
//     destroy_DC_Circ_list(my_DC_Circ_list);

//    return 0;
// }
