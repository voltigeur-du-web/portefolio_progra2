#include "tri_gobelets.h"
#include <stdlib.h> 
#include <time.h>  

//Fonction auxiliaire pour vérifier si le tableau est trié
int is_sorted(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; 
        }
    }
    return 1; 
}

int tri_gobelets(int* tab, int size) {
    if (size <= 1) {
        return 0; 
    }
    int count = 0; 
    srand(time(NULL));

    // Boucle jusqu'à ce que le tableau soit trié
    while (!is_sorted(tab, size)) {
        int i = rand() % size;
        int j = rand() % size;
        int temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;

        count++; 
    }
    return count;
}