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
//POST: initialise une PQ vide avec une relation d'ordre leq 
PQ_t create(int (*leq)(int,int));

//PRE: pq est initialisée
//POST: pq = pq' U {item}
void enqueue(PQ_t pq, int item);

//PRE: pq est initialisée, taille(pq)>0
//POST: pq = pq' \ {x} tq x est l'élément le plus prioritaire de pq
//      renvoie x
int serve(PQ_t pq);

//PRE: pq est initialisée, taille(pq)>0
//POST: renvoie x tq x est l'élément le plus prioritaire de pq      
int peek(PQ_t pq);

//PRE: pq initialisée
//POST: renvoie 1 si pq est vide, 0 sinon
int empty(PQ_t pq);


#endif
