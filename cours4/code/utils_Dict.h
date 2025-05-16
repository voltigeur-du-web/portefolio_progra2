#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Node_tree;
typedef struct Node_tree* Node_tree_t;

//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire
//POST: Retour un entier étant la hauteur de ce noeud; soit le nombre de node aux feuilles les plus éloignées (0 si feuille) 
int compute_node_height(Node_tree_t node);

//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire
//POST: Retour un entier étant la balance entre la branche de droite / gauche du noeud
    //Si < -1 alors déséquilibre sur la branche de gauche
    //Si > 1 alors déséquilibre sur la branche de droite
int compute_node_balance(Node_tree_t node);

//Fonction auxiliaire récursive pour supprimer les nodes
//PRE: Un noeud non-nulle compris dans un arbre initialisé
//POST: Détruit le noeud passé comme argument ainsi que tous les noeuds enfants (désallocation mémoire de node et node->key). 
void destroy_node(Node_tree_t node);

// Fonction auxiliaire pour calculer le maximum entre 2 entiers
// PRE: a et b sont deux entiers
// POST: retourne un nombre entier qui est le maximum entre les deux entrées
int max(int a, int b);
