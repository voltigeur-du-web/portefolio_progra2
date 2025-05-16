#include "utils_Dict_balance.h"
#include "utils_Dict.h"

#define MAX_CHAR_SIZE 50

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

struct Dico{
    Node_tree_t root;
    int size;
};

//Fonction auxiliaire de rotation des branches d'un noeud
//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire ; le noeud a une hauteur > 2
//POST: Retourne un pointeur vers ce noeud. Il y a rotation vers la droite des branches 
    // par rapport au noeud de départ
Node_tree_t rotate_tree_right(Node_tree_t old){
    Node_tree_t new = old->left;
    Node_tree_t temp = new->right;
    // Effectuer la rotation
    new->right = old;
    old->left = temp;
    // Mettre à jour les hauteurs
    old->height=compute_node_height(old);
    new->height=compute_node_height(new);
    //printf("Old node height is %i ; new node height is %i\n",old->height,new->height);
    return new;
}
    
//Fonction auxiliaire de rotation des branches d'un noeud
//PRE: Un pointeur d'un noeud d'arbre faisant partie d'un dictionnaire ; le noeud a une hauteur > 2
//POST: Retourne un nouveau pointeur vers ce noeud. Il y a rotation vers la gauche des branches 
    // par rapport au noeud de départ
Node_tree_t rotate_tree_left(Node_tree_t old){
    Node_tree_t new = old->right;
    Node_tree_t temp = new->left;
    // Effectuer la rotation
    new->left = old;
    old->right = temp;
    // Mettre à jour les hauteurs
    old->height = compute_node_height(old);
    new->height = compute_node_height(new);
    // Retourner le nouveau racine
    //printf("Old node height is %i ; new node height is %i\n",old->height,new->height);
    return new;
}

//PRE: un noeud node par où commencer le rééquilibrage vers les feuilles & un arbre de recherche binaire non null `tree`
//POST: Retourne un arbre équilibré
Node_tree_t balance_node(Node_tree_t node, Dico_t tree){
    if (node == NULL) return NULL;

    Node_tree_t current_node = node;
    //Déséquilibre à droite -> rotation à gauche
    while(current_node != NULL && compute_node_height(current_node)>2 && compute_node_balance(current_node)>1){
        current_node = rotate_tree_left(current_node);
    }
    //Déséquilibre à gauche -> rotation à droite
    while(current_node != NULL && compute_node_height(current_node)>2 && compute_node_balance(current_node)<-1){
        current_node = rotate_tree_right(current_node);
    }
    //Si input node = root then root = output
    if(tree->root == node) tree->root = current_node; 
    //balance children if relevant
    if(current_node->left != NULL && 
        compute_node_height(current_node->left)>2 && 
        (compute_node_balance(current_node->left)>1 || 
        compute_node_balance(current_node->left)<-1)){

        current_node->left=balance_node(current_node->left, tree);
    }
    if(current_node->right != NULL && 
        compute_node_height(current_node->right)>2 && 
        (compute_node_balance(current_node->right)>1 || 
        compute_node_balance(current_node->right)<-1)){

        current_node->right=balance_node(current_node->right, tree);
    }
    //update height
    if(current_node->left == NULL && current_node->right == NULL) current_node->height = 0;
    else if(current_node->left != NULL && current_node->right != NULL) current_node->height = max(current_node->left->height,current_node->right->height)+1;
    else if(current_node->left != NULL) current_node->height = current_node->left->height+1;
    else current_node->height = current_node->right->height+1;

    return current_node;
}

//PRE: un arbre de recherche binaire initialisé
//POST: Retourne un arbre équilibré
Dico_t balance_tree(Dico_t tree){
    if(tree->root!=NULL && tree->root->height>2){
        balance_node(tree->root,tree);
    } 
    return tree;
}
