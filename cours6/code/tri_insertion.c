#include "tri.h"

unsigned long long int sort(int* tab, int size){
    unsigned long long int counter=0;
    int i, j, moving;
    // On commence au deuxième élément
    for(i=1;i<size; i++){
        moving=tab[i];
        j=i-1;
        // Retour vers les éléments précédent du tableau jusqu'à ce qu'on trouve un nombre plus petit ou égale
        // Les valeurs plus élevées sont décalé à droite vers l'index de la valeur qu'on est en train de déplacer
        while(j>=0 && tab[j]>moving) {
            tab[j+1] = tab[j];
            j--;
            counter++;
        }
        //Insertion de la valeur à insérer
        tab[j+1] = moving;
    }
    return counter;
}