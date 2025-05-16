#include "priority_queue.h"

#define MAX_SIZE 50

struct PQ {
    int* heap;
    int size;
    int capacity;
    int (*leq)(int, int);
};
typedef struct PQ* PQ_t;

// Fonction pour créer une file de priorité vide
PQ_t create_pq(int (*leq)(int, int)) {
    PQ_t pq = (PQ_t)malloc(sizeof(struct PQ));
    pq->heap = malloc(MAX_SIZE*sizeof(int));
    pq->size = 0;
    pq->capacity = MAX_SIZE;
    pq->leq = leq;
    return pq;
}

// Fonction auxiliaire pour échanger deux éléments
// PRE: 2 pointeurs vers des nombre entiers
// POST: Echange les valeurs entre deux pointeurs 
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction auxiliaire pour maintenir la propriété du tas en remontant d'un enfant à son parent
//PRE: Une file de priorité initialisée et non-vide et l'index de l'élément enfant
//POST: Retourne l'index du parent de l'élément enfant en entrée. 
    // Au sein de la file de priorité, la valeur prioritaire (enfant ou parent) est à la place du parent
int order_lineage_up(PQ_t pq, int child) {
    int parent = (child-1)/2;

    if(child == 0 || child >= pq->size || parent < 0){
        fprintf(stderr,"index out of bound\n");
        exit(1);
    }

    // If parent value > child value, then swap
    if (pq->leq(pq->heap[parent], pq->heap[child])>0) {
        swap(&pq->heap[parent],&pq->heap[child]);
    }
    return parent;
}

// Fonction auxiliaire pour maintenir la propriété du tas en descendant du parent vers ses deux enfants
//PRE: Une file de priorité initialisée et non-vide et l'index de l'élément parent
//POST: Retourne l'index de l'enfant le plus prioritaire si celui-ci est prioritaire sur le parent. 
    // Au sein de la file de priorité, la valeur la plus prioritaire est à la place du parent. 
int order_lineage_down(PQ_t pq, int parent) {
    int left = 2*parent+1;
    int right = 2*parent+2;

    if(parent < 0 || parent >= pq->size){
        fprintf(stderr,"Parent index out of bound\n");
        exit(1);
    }

    // If parent value > child value, then swap with smallest (right or left)
    if (pq->size>1 && (pq->leq(pq->heap[parent], pq->heap[left])>0 || pq->leq(pq->heap[parent], pq->heap[right])>0 )) {
        if(pq->leq(pq->heap[left], pq->heap[right])>0){
            swap(&pq->heap[parent],&pq->heap[right]);
            return right;
        }
        else{
            swap(&pq->heap[parent],&pq->heap[left]);
            return left;
        }
    }
}

// Fonction pour ajouter un élément à la file de priorité
PQ_t add_to_pq(PQ_t pq, int element) {
    if (pq->size == pq->capacity) {
        printf("La file de priorité est pleine.\n");
        return pq;
    }
    pq->size++;

    //Add to last element
    pq->heap[pq->size-1]=element;

    //Reorder parent lineage up if necessary (index is parent of added until index = 0 included)
    int i=pq->size-1;
    while(i > 0){
        i=order_lineage_up(pq,i);
    }
    return pq;
}

// Fonction pour retirer l'élément le plus prioritaire
PQ_t serve_pq(PQ_t pq) {
    if (pq->size == 0) {
        printf("La file de priorité est vide.\n");
        return pq;
    }

    //Put latest element as top
    swap(&pq->heap[0], &pq->heap[pq->size-1]);
    pq->size--;

    //Reorder parent lineage down if necessary (index is parent of added until index = 0 included)
    int i=0;
    while(pq->size>1 && i<=(pq->size-2)/2){
        i=order_lineage_down(pq,i);
    }
    return pq;
}

// Fonction pour vérifier si la file est vide
bool is_pq_empty(PQ_t pq) {
    return pq->size == 0;
}

// Fonction pour vérifier si la file est pleine
bool is_pq_full(PQ_t pq) {
    return pq->size == pq->capacity;
}

// Fonction pour obtenir l'élément le plus prioritaire sans le retirer
int peek_pq(PQ_t pq) {
    if (pq->size == 0) {
        printf("La file de priorité est vide.\n");
        return -1;
    }
    return pq->heap[0];
}

