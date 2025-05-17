#include "priority_queue.h"

#define MAX_SIZE 1000

struct PQ {
    int* heap;
    int size;
    int capacity;
    int (*leq)(int, int);
};

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

// Fonction auxiliaire récursive pour maintenir la propriété du tas en descendant du parent vers ses deux enfants
//PRE: Une file de priorité initialisée et non-vide et l'index de l'élément parent,
    //counter est un big int non signé pour compter le nombre de manipulation dans le tri
//POST: Maintient de la relation d'ordre en descendant du parent initial vers les "feuilles" du tas binaire
void order_lineage_down(PQ_t pq, int parent,unsigned long long int* counter) {
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;
    (*counter)++;
    // Si pq <= 1 : stop
    if(pq->size<=1){
        return;
    }
    // Si pas d'enfants : stop
    else if(right>=pq->size && left>=pq->size){
        return;
    }
    // Si pas de right et left prioritaire sur parent : order on left
    else if(right>=pq->size && pq->leq(pq->heap[left], pq->heap[parent])<0){
        swap(&pq->heap[parent], &pq->heap[left]);
        order_lineage_down(pq, left,counter);
    }
    // Si pas de right et left non prioritaire sur parent :stop
    else if(right>=pq->size){
        return;
    }
    // Si parent prioritaire : stop
    else if(pq->leq(pq->heap[parent], pq->heap[left])<0 && pq->leq(pq->heap[parent], pq->heap[right])<0 ){
        return;
    }
    // Si left prioritaire : order on left
    else if (pq->leq(pq->heap[left], pq->heap[right])<=0) {
        swap(&pq->heap[parent], &pq->heap[left]);
        order_lineage_down(pq, left,counter);
    }
    // Si right prioritaire : order on right
    else if (pq->leq(pq->heap[left], pq->heap[right])>0) {
        swap(&pq->heap[parent], &pq->heap[right]);
        order_lineage_down(pq, right,counter);
    }
}
// Fonction pour ajouter un élément à la file de priorité
PQ_t add_to_pq(PQ_t pq, int element,unsigned long long int* counter) {
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
        (*counter)++;
    }
    return pq;
}

// Fonction pour retirer l'élément le plus prioritaire
PQ_t serve_pq(PQ_t pq,unsigned long long int* counter) {
    if (pq->size == 0) {
        printf("La file de priorité est vide.\n");
        return pq;
    }
    //Put latest element as top
    swap(&pq->heap[0], &pq->heap[pq->size-1]);
    pq->size--;

    //Reorder parent lineage down if necessary (index is parent of added until index = 0 included)
    order_lineage_down(pq,0,counter);
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

void display_pq(PQ_t pq){
    for(int i=0;i<pq->size;i++){
        printf("%i ",pq->heap[i]);
    }
    printf("\n");
}
