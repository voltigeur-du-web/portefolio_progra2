/*

Auteur: Cédric Libert
Description: file d'entiers. On peut y ajouter des éléments et récupérer à chaque fois l'élément qui est dans la
file depuis le plus longtemps.

*/
#ifndef PQ_H
#define PQ_H

#include <stdlib.h>
#include <stdio.h>


struct PQ; //déclaration du nom de ma structure
typedef struct PQ* PQ_t; //déclaration d'un alias qui désigne le type "pointeur vers struct Queue"

//PRE: /
//POST: initialise une PQ vide avec une relation d'ordre 
PQ_t create(int (*leq)(int,int));


#endif
