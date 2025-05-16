#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Dico;
typedef struct Dico* Dico_t;

struct Node_tree;
typedef struct Node_tree* Node_tree_t;

//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire ; le noeud a une hauteur > 2
//POST: Retourne un pointeur vers un nouveau noeud après rotation vers la gauche des branches
Node_tree_t rotate_tree_left(Node_tree_t old);

//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire ; le noeud a une hauteur > 2
//POST: Retourne un pointeur vers un nouveau noeud après rotation vers la droite des branches
Node_tree_t rotate_tree_right(Node_tree_t old);

//PRE: un arbre de recherche binaire non null `tree` 
//POST: Retourne un arbre équilibré
Node_tree_t balance_node(Node_tree_t node,Dico_t tree);
