/*
Auteur: Pierre-André Marchand
Description: pile d'entiers. On peut y ajouter des éléments et récupérer à chaque fois l'élément qui est dans la
file depuis le moins longtemps.
*/
#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>

//Invariant de structure: pour toute Queue initialisée, size(q)>=0

struct Stack; //déclaration du nom de ma structure
typedef struct Stack* Stack_t; //déclaration d'un alias qui désigne le type "pointeur vers struct Stack"

//PRE: /
//POST: initialise une Stack vide et renvoie un pointeur vers celle-ci 
Stack_t new_stack();

//PRE: s est initialisé
//POST: renvoie le nombre d'éléments présents dans s. s n'est pas modifiée.
int size_stack(Stack_t s);

//PRE: s est initialisé
//POST: size(s') = size(s)+1 et le dernier élément de s est i. Le reste n'a pas été modifié
void add_to_stack(Stack_t s, int i);

//PRE: s est initialisé, size(s)>0
//POST: renvoie le dernier élément de s (élément le plus récent mis dans s) et l'enlève de s.
//      size(s')=size(s)-1 
//      Le reste n'est pas modifié.
int remove_from_stack(Stack_t s);

//PRE: s est initialisée
//POST: toute la mémoire allouée pour s est libérée
void destroy_stack(Stack_t s);

//PRE: s est initialisée
//POST: Les values de la stack sont montrés
void display_stack(Stack_t s);

#endif
