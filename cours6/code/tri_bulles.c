#include "tri.h"
#include "utils.h"

unsigned long long int sort(int* tab, int size){
    unsigned long long int counter=0;
    int i,j;
    //S'arrète à l'avant dernier car sinon pas de permutation possible
    for(i=0;i<size-1;i++){ 
        //Dernier élément i est déjà trié, à exclure
        for(j=0;j<size-i-1;j++) {
            if(tab[j]>tab[j+1]){
                swap(tab,j,j+1);
                
            }
            counter++;
        }
    }
    return counter;
}