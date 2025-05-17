#include "tri.h"
#include "priority_queue.h"

struct PQ {
    int* heap;
    int size;
    int capacity;
    int (*leq)(int, int);
};

int leq(int a, int b){
    return a-b;
}

unsigned long long int sort(int* tab, int size){
    unsigned long long int counter=0;
    PQ_t pq = create_pq(leq);
    int i;
    for(i=0;i<size;i++){
        add_to_pq(pq,tab[i],&counter);
    }
    for(i=0;i<size;i++){
        tab[i]=peek_pq(pq);
        serve_pq(pq,&counter);        
    }
    free(pq->heap);
    free(pq);
    return counter;
}