#include "priority_queue_struct.h"

#define MAX_SIZE 50

struct Node_PQ{
    int priority;
    int id;
};

struct PQ {
    Node_PQ_t players;
    int size;
    int capacity;
    int (*leq)(int, int);
};

// Fonction pour créer une file de priorité vide
PQ_t create_pq(int (*leq)(int, int),int size) {
    PQ_t pq = (PQ_t)malloc(sizeof(struct PQ));
    pq->players = malloc(size*sizeof(struct Node_PQ));
    pq->size = 0;
    pq->capacity = size;
    pq->leq = leq;
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

// Fonction pour échanger deux éléments
void swap(struct Node_PQ *a, struct Node_PQ *b) {
    struct Node_PQ temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour maintenir la propriété du tas (playersify)
int order_lineage_up(PQ_t pq, int child) {
    int parent = (child-1)/2;

    if(child == 0 || child >= pq->size || parent < 0){
        fprintf(stderr,"index out of bound\n");
        exit(1);
    }

    // If parent value > child value, then swap
    if (pq->leq(pq->players[parent].priority, pq->players[child].priority)>0) {
        swap(&pq->players[parent],&pq->players[child]);
    }
    return parent;
}


int order_lineage_down(PQ_t pq, int parent) {
    int left = 2*parent+1;
    int right = 2*parent+2;

    //Seulement un élément dans l'arbre ou il n'y a plus d'enfant dans la branche
    if (pq->size<=1 || !(pq->size-1>=right || pq->size-1>=left)){
        //printf("Size <=1 ou plus d'enfant dans la branche\n");
        return 0;
    } 
    //Seulement un enfant à gauche et enfant plus petit que parent
    else if(pq->size-1>=left && pq->size-1<right && pq->leq(pq->players[parent].priority, pq->players[left].priority)>0){
        //printf("Enfant à gauche seulement et parent plus grand\n");
        swap(&pq->players[parent],&pq->players[left]);
        return 0;
    }
    //Seulement un enfant à gauche et parent plus petit que enfant
    else if(pq->size-1>=left && pq->size-1<right){
        //printf("Enfant à gauche seulement et parent plus petit\n");
        return 0;
    }
    //Deux enfants, parent plus petit qu'un des deux, gauche est plus petit que droit
    else if((pq->leq(pq->players[parent].priority, pq->players[left].priority)>0 || pq->leq(pq->players[parent].priority, pq->players[right].priority)>0) && 
    pq->leq(pq->players[left].priority, pq->players[right].priority)<=0){
        //printf("Enfants à droite et gauche, parent plus grand qu'un enfant, gauche plus petit que droite\n");
        swap(&pq->players[parent],&pq->players[left]);
        order_lineage_down(pq,left);
    }
    //Deux enfants, parent plus petit qu'un des deux, droit est plus petit que gauche
    else if((pq->leq(pq->players[parent].priority, pq->players[left].priority)>0 || pq->leq(pq->players[parent].priority, pq->players[right].priority)>0) && 
    pq->leq(pq->players[right].priority, pq->players[left].priority)<0){
        //printf("Enfants à droite et gauche, parent plus grand qu'un enfant, droite plus petit que gauche\n");
        swap(&pq->players[parent],&pq->players[right]);
        order_lineage_down(pq,right);
    }
    else{
        //printf("Else\n");
        return 0;
    } 
}

// Fonction pour ajouter un élément à la file de priorité
PQ_t add_to_pq(PQ_t pq, int priority, int id) {
    if (is_pq_full(pq)) {
        printf("La file de priorité est pleine.\n");
        return pq;
    }
    pq->size++;

    //Add to last element
    pq->players[pq->size-1].id=id;
    pq->players[pq->size-1].priority=priority;

    //Reorder parent lineage up if necessary (index is parent of added until index = 0 included)
    int i=pq->size-1;
    while(i > 0){
        i=order_lineage_up(pq,i);
    }
    return pq;
}

// Fonction pour retirer l'élément le plus prioritaire
PQ_t serve_pq(PQ_t pq) {
    if (is_pq_empty(pq)) {
        printf("La file de priorité est vide.\n");
        return pq;
    }

    //Put latest element as top
    swap(&pq->players[0], &pq->players[pq->size-1]);
    pq->size--;

    //Reorder parent lineage down if necessary (index is parent of added until index = 0 included)
    int zero=0;
    order_lineage_down(pq,zero);
    return pq;
}

// Fonction pour détruire la file de priorité avec structure
void destroy_pq(PQ_t pq){
    free(pq->players);
    free(pq);
}

// Fonction pour obtenir l'élément le plus prioritaire sans le retirer
struct Node_PQ peek_pq(PQ_t pq) {
    if (is_pq_empty(pq)) {
        printf("La file de priorité est vide.\n");
    }
    else{
        return pq->players[0];
    }
    
}

