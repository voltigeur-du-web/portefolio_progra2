#include "utils_Dict.h"

//Déclaration structure
struct Node_tree{
    char* key;
    //const char key[MAX_CHAR_SIZE];
    int height;
    int value;
    struct Node_tree* parent;
    struct Node_tree* left;
    struct Node_tree* right;
};

//Fonction auxiliaire de calcul de hauteur de noeud
//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire
//POST: Retour un entier étant la hauteur d'un noeud - distance la plus éloignée des feuilles (1 si feuille) 
int compute_node_height(Node_tree_t node){
    if (node == NULL) {
        //fprintf(stderr, "Node est NULL pas de height possible.\n");// La hauteur d'un nœud nul est 0
        //exit(1);
        return 0;
    }
    //feuille
    else if(node->left==NULL && node->right==NULL){
        return 0;
    }
    else{
    int left_height = compute_node_height(node->left);
    int right_height = compute_node_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
    }
}

//Fonction auxiliaire de calcul de balance
//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire
//POST: Retour un entier étant la balance entre la branche de droite / gauche du noeud
    //Si < -1 alors déséquilibre sur la branche de gauche
    //Si > 1 alors déséquilibre sur la branche de droite
int compute_node_balance(Node_tree_t node){
    int left = compute_node_height(node->left);
    int right = compute_node_height(node->right);
    return right - left;
}


//Fonction auxiliaire récursive pour supprimer les nodes
//PRE: Un noeud non-nulle compris dans un arbre initialisé
//POST: Détruit le noeud passé comme argument ainsi que tous les noeuds enfants (désallocation mémoire de node et node->key). 
void destroy_node(Node_tree_t node){
    if(node->left == NULL && node->right == NULL){
        if(node->parent != NULL && strcmp(node->key,node->parent->key)<0) node->parent->left=NULL;
        else if(node->parent != NULL && strcmp(node->key,node->parent->key)>0) node->parent->right=NULL;
        free(node->key);
        free(node);
    } 
    else if(node->left != NULL && node->right != NULL){
        destroy_node(node->right);
        destroy_node(node->left);
    }
    else if(node->left != NULL){
        destroy_node(node->left);
    }
    else if(node->right != NULL){
        destroy_node(node->right);
    }
}

// Fonction auxiliaire pour calculer le maximum entre 2 entiers
// PRE: a et b sont deux entiers
// POST: retourne un nombre entier qui est le maximum entre les deux entrées
int max(int a, int b) {
    return (a > b) ? a : b;
}

