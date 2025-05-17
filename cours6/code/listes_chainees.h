#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>

// // Liste chainée simple
// typedef struct SC_List SC_List;

// // Liste chainée double
// typedef struct DC_List DC_List;

// // Liste chainée double circulaire
// typedef struct DC_Circ_List DC_Circ_List;

struct SC_List;
typedef struct SC_List* SC_List_t;
struct Node_SC_List;
typedef struct Node_SC_List* Node_SC_List_t;

struct DC_List;
typedef struct DC_List* DC_List_t;
struct Node_DC_List;
typedef struct Node_DC_List* Node_DC_List_t;

struct DC_Circ_List;
typedef struct DC_Circ_List* DC_Circ_List_t;
struct Node_DC_Circ_List;
typedef struct Node_DC_Circ_List* Node_DC_Circ_List_t;

//Initialisation d'une liste chainée simple
//PRE: Néant
//POST: Retourne une liste chainée simple vide (sans noeuds) - avec une tête allouée en mémoire
SC_List_t init_SC_list(void);

//Ajout d'un noeud à la fin de la liste chainée simple
//PRE: list est une liste chainée simple initialisée
//POST: Ajoute un noeud à la fin de la liste chainée simple
void append_SC_list(SC_List_t list, int value);

//Affichage de la liste chainée simple
//PRE: list est une liste chainée simple initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée simple
void display_SC_list(SC_List_t list);

//Affichage de la liste chainée simple
//PRE: list est une liste chainée simple initialisée
//POST: Détruit la liste chainée et ses noeuds
void destroy_SC_list(SC_List_t list);

//Initialisation d'une liste chainée double
//PRE: Néant
//POST: Retourne une liste chainée double vide (sans noeuds) - avec une tête allouée en mémoire
DC_List_t init_DC_list(void);

//Ajout d'un noeud à la fin de la liste chainée double
//PRE: list est une liste chainée double initialisée
//POST: Ajoute un noeud à la fin de la liste chainée double
void append_DC_list(DC_List_t list, int value);

//Affichage de la liste chainée double
//PRE: list est une liste chainée double initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double
void display_DC_list(DC_List_t list);

//Display previous-current-next 
//PRE: list est une liste chainée double initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double avec les valeurs des noeuds précédents et suivants
void display_prev_now_next_DC_list(DC_List_t list);

//Destruction de la liste chainée double
//PRE: list est une liste chainée double initialisée
//POST: Détruit la liste chainée et ses noeuds
void destroy_DC_list(DC_List_t list);

//Initialisation d'une liste chainée double circulaire
//PRE: Néant
//POST: Retourne une liste chainée double circulaire vide (sans noeuds) - avec une tête allouée en mémoire
DC_Circ_List_t init_DC_Circ_list(void);

//Ajout d'un noeud à la fin de la liste chainée double circulaire
//PRE: list est une liste chainée double circulaire initialisée
//POST: Ajoute un noeud à la fin de la liste chainée double circulaire
void append_DC_Circ_list(DC_Circ_List_t list, int value);

//Affichage de la liste chainée double circulaire sens backward et forward
//PRE: list est une liste chainée double circulaire initialisée
//POST: Affiche les valeurs des noeuds de la liste chainée double circulaire dans les deux sens
void display_DC_Circ_list(DC_Circ_List_t list);

//Destruction de la liste chainée double circulaire
//PRE: list est une liste chainée double circulaire initialisée
//POST: Détruit la liste chainée et ses noeuds
void destroy_DC_Circ_list(DC_Circ_List_t list);


#endif // LISTS_H
