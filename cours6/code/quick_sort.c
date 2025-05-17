#include "tri.h"
#include "utils.h"

int quick_sort(int* tab, int first, int last, unsigned long long int* counter) {
    // 1 seul élément OU 2 éléments ordonnés --> sortie
    if(first>last){
        return 1;
    }
    else if(first==last ||(last-first==1 && tab[first]<=tab[last])){
        return 0;
    }
    //Parcourir jusqu'à last et placer les éléments < pivot à gauche de celui-ci
    int pivot=tab[first];
    int pos_pivot=first;   
    int i,moving;
    for(i=first+1;i<=last;i++){
        if(tab[i]<pivot){
            moving=tab[i];
            swap_shift_right(tab,pos_pivot,i, counter);
            pos_pivot++;
        }
        (*counter)++;
    }
    // Quick sort récursif avec les 2 sous tableaux
    quick_sort(tab, first, pos_pivot,counter);
    quick_sort(tab, pos_pivot+1, last,counter);
}

unsigned long long int sort(int* tab, int size){
    unsigned long long int counter=0;
    quick_sort(tab,0,size-1,&counter);
    return counter;
}