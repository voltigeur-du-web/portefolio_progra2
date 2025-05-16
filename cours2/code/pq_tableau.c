#include "priority_queue.h"
#define TAILLE_MAX 100

// Structure de la file de priorité basée sur un tableau non trié
typedef struct PQ{
    int* tab;
    int taille;
    int cap;
    int offset;
    int (*leq)(int,int);
} PQ;

PQ_t create_pq(int (*leq)(int,int)){
    PQ_t pq = malloc(sizeof(PQ));
    if (pq == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    pq->tab = malloc(sizeof(int)*TAILLE_MAX);
    if (pq->tab == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    pq->taille = 0;
    pq->cap = 100;
    pq->offset = 0;
    pq->leq = leq;
    return pq;
}

bool is_pq_empty(PQ_t pq){
    if(pq->taille>0) return false;
    else return true;
}

bool is_pq_full(PQ_t pq){
    if (pq->taille>=TAILLE_MAX) return true;
    else return false;
}

//Fonction auxiliaire tri à bulle
// PRE: Une file de priorité sous forme de tableau
// POST: Ordonne par priorité les valeurs entières de tableau
void sort_pq(PQ_t pq) {
    int temp;
    for (int i = 0; i < pq->taille - 1; i++) {
        for (int j = 0; j < pq->taille - i - 1; j++) {
            if (pq->leq(pq->tab[j], pq->tab[j + 1]) > 0) {
                // Échanger pq->tab[j] et pq->tab[j + 1]
                temp = pq->tab[j];
                pq->tab[j] = pq->tab[j + 1];
                pq->tab[j + 1] = temp;
            }
        }
    }
}

PQ_t add_to_pq(PQ_t pq,int elem){
    if(is_pq_full(pq)){
        printf("Ajout impossible de l'élément car la queue est pleine\n");
        return pq;
    }
    pq->taille++;
    // Besoin d'un realloc si la taille excède la capacité 
    if(pq->taille>pq->cap){
        pq->cap += 100;
        pq->tab = (int *)realloc(pq->tab, pq->cap * sizeof(int));
        if (pq->tab == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
    }
    if(pq->taille==1){
        pq->tab[0]=elem;
    }
    else if (pq->taille>1){
        pq->tab[pq->taille-1]=elem;
        //Est-ce que l'ordre est brisé dans la PQ ?
        if (pq->leq(pq->tab[pq->taille-2],elem)>0){
            sort_pq(pq);
        }
    }

    return pq;
}

PQ_t serve_pq(PQ_t pq){
    if(is_pq_empty(pq)){
        printf("Retrait impossible de l'élément car la queue est vide\n");
        return pq;
    }
    pq->offset++;
    pq->taille--;
    // Si la taille du tableau atteint la tranche inférieur de capacité: réduction de la taille et reset de l'offset
    if (pq->cap > 100 && pq->taille < pq->cap && pq->taille % 100 == 0) {
        pq->cap = pq->taille;
        int *new_tab = (int *)malloc(pq->cap * sizeof(int));
        if (new_tab == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
        for (int i = 0; i < pq->taille; i++) {
            new_tab[i] = pq->tab[pq->offset + i];
        }
        free(pq->tab);
        pq->tab = new_tab;
        pq->offset = 0;
    }
    return pq;
}

int peek_pq(PQ_t pq){
    if(is_pq_empty(pq)){
        printf("La queue est vide\n");
    }
    else return pq->tab[pq->offset];
}

void display_pq(PQ_t pq){
    for(int i=pq->offset;i<pq->taille+pq->offset;i++){
        printf("%i\n",pq->tab[i]);
    }
}