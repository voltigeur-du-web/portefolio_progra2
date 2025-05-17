/*
Auteur: Cédric Libert
Description: file d'entiers. On peut y ajouter des éléments et récupérer à chaque fois l'élément qui est dans la
file depuis le plus longtemps.
Edit: Pierre-André Marchand (2025-02-15)
*/
#ifndef PQ_H
#define PQ_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct PQ; //déclaration du nom de ma structure
typedef struct PQ* PQ_t; //déclaration d'un alias qui désigne le type "pointeur vers struct Queue"

//PRE: /
//POST: initialise une PQ vide avec une relation d'ordre 
PQ_t create_pq(int (*leq)(int,int));

//PRE: pq est definie et taille de pq < taille max,
    //counter est un big int non signé pour compter le nombre de manipulation dans le tri
//POST: ajout de l'élément dans la queue
PQ_t add_to_pq(PQ_t pq, int element,unsigned long long int* counter);

//PRE: pq est definie et de taille > 0, 
    //counter est un big int non signé pour compter le nombre de manipulation dans le tri
//POST: Retourne pq sans l'élément le plus prioritaire
PQ_t serve_pq(PQ_t pq,unsigned long long int* counter);

//PRE: pq est défini
//POST: Retourne True si la file est vide, False sinon
bool is_pq_empty(PQ_t pq);

//PRE: pq est défini
//POST: Retourne True si la file est pleine, False sinon
bool is_pq_full(PQ_t pq);

//PRE: pq est défini et de taille > 0
//POST: Retourne l'élément le plus prioritaire
int peek_pq(PQ_t pq);

//PRE: pq est défini et de taille > 0
//POST: Affiche les éléments composants la priority queue dans la console
void display_pq(PQ_t pq);

#endif
