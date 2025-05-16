#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int queue(){
    int size = 32;
    int* mytab = malloc(size*sizeof(int));
    //Some code
    free(mytab);
    mytab=NULL;
    return 1;
}

// All in one
int list_chainee(){
    typedef struct chaine_s{
        char *nom;
        char *prenom;
        int age;
        int* next;
        struct chaine_s *next;
    } chaine_s;
    return 1;
}
