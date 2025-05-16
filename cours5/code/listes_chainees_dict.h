#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node_SC_List;
typedef struct Node_SC_List* Node_SC_List_t;

struct SC_List;
typedef struct SC_List* SC_List_t;

//PRE: -
//POST: La liste chainée est initialisée
SC_List_t init_SC_list(void);

//PRE: Une liste chainée initialisée et une parie de clé-valeur qui sont une chaine de charactère et un entier respectivement
//POST: Ajout un nouveau noed à la chaine ayant une structure clé-valeur 
void append_SC_list(SC_List_t list, const char* key, int value);

//PRE: Une liste chainée initialisée non-nulle  et une chaine de charactère `key`
//POST: Le noeud où sa chaine de caractère est égale à l'argument `key` est enlevé de la liste
    // Retourne true si la chaine de caractère d'un noeud de la liste est égale à l'argument `key` (+ retrait du noeud)
    // Retourne false si la chaine de caractère n'a pas été trouvée dans la liste
bool serve_SC_list(SC_List_t list, const char* key);


//PRE: Une liste chainée initialisée et non vide
//POST: Affiche les clé-valeur de chaque élément de la liste chainées
void display_SC_list(SC_List_t list);

//PRE: Une liste chainée initialisée
//POST: Supprime et libère l'allocation en mémoire de la liste chainée
void destroy_SC_list(SC_List_t list);

#endif // LISTS_H
