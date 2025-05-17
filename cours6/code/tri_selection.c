#include "tri.h"
#include "utils.h"

// Fonction pour effectuer un tri par sélection
unsigned long long int sort(int* tab, int size) {
    unsigned long long int counter=0;
    int i,j;
    for(i=0;i<size-1; i++) {
        // Trouver l'indice du plus petit élément dans la partie non triée
        int min_index=i;
        for(j=i+1;j<size;j++) {
            if(tab[j]<tab[min_index]){
                min_index = j;
            }
            counter++;
        }
        // Échanger le plus petit élément avec le premier élément non trié
        if (min_index != i) {
            swap(tab,i,min_index);
        }
    }
    return counter;
}
