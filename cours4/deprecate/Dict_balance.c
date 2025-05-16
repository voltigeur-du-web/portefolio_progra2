#include "Dict.h"
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

//PRE: /
//POST: retourne un dictionnaire vide
Dico_t create_dict(){
    Dico_t tree = (Dico_t)malloc(sizeof(struct Dico));
    tree->root = NULL;
    tree->size=0;
    return tree;
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

//PRE: Dico est initialisé
//POST: Supprime le dictionnaire et tous ses composants de la mémoire
    //Retourne 0 si de-allocation ok
    //Retourne 1 sinon
int destroy_dict(Dico_t tree){
    if(tree->root != NULL) destroy_node(tree->root);
    free(tree);
    return 0;
}


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

//Fonction auxiliaire pour rattacher un noeud aux branches d'un autre noeud
bool attach_node(Node_tree_t moving, Node_tree_t base){
    if(strcmp(moving->key,base->key)==0){
        return false;
    }
    else if(strcmp(moving->key,base->key)<0 && base->left == NULL){
        moving->parent=base;
        base->left=moving;
        return true;
    }
    else if(strcmp(moving->key,base->key)>0 && base->right == NULL){
        moving->parent=base;
        base->right=moving;
        return true;
    }
    else if(strcmp(moving->key,base->key)<0){
        attach_node(moving,base->left);
    }
    else if(strcmp(moving->key,base->key)>0){
        attach_node(moving,base->right);
    }
    return true;
} 

int max(int a, int b) {
    return (a > b) ? a : b;
}

int update_height_to_root(Node_tree_t node, Dico_t tree){
    if(node == NULL || node==tree->root || node->parent == NULL){
        return 0;
    }
    else{
        int left_height = (node->parent->left == NULL) ? 0 : node->parent->left->height;
        int right_height = (node->parent->right == NULL) ? 0 : node->parent->right->height;
        node->parent->height = max(left_height,right_height)+1;
        update_height_to_root(node->parent,tree);
    }
    return 1;
}

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


//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier 
//POST: retourne un boleen 
    //true: si la clé est unique ; la nouvelle clé et sa valeur sont ajoutées au dictionnaire
    //false: si la clé existe déjà dans le dictionnaire
bool add_to_dict(Dico_t tree, const char* key, int value){
    Node_tree_t new_node = (Node_tree_t)malloc(sizeof(struct Node_tree));
    new_node->key = (char*)malloc(strlen(key) + 1); // Allouer de la mémoire pour la clé
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL; 
    new_node->height = 0;
    bool success=false;
    //Racine
    if (tree->root == NULL){
        tree->root = new_node;
        success=true;
    }
    else{
        success = attach_node(new_node,tree->root);
        update_height_to_root(new_node,tree);
    }
    if(success) tree->size++;
    return success;
}

//Fonction auxilliaire
// Renvoie null si impossible
Node_tree_t get_parent_from_key(Dico_t tree,char* key){
    //Arbre vide
    if(tree->root == NULL){
        return NULL;
    }
    Node_tree_t current = tree->root;
    int cmp=strcmp(key,current->key);
    //Stop if key found OR (key not found && bout de l'arbre)
    while(!(cmp==0 || 
            (cmp<0 && current->left == NULL) || 
            (cmp>0 && current->right == NULL))){
        if(cmp<0){
            current = current->left;
        }
        else if(cmp>0){
            current = current->right;
            
        }
        cmp=strcmp(key,current->key);
    }
    return current;
}

//PRE: Dico est initialisé;`key` et `value` est sont initialisés; `key` existe dans le dictionnaire 
//POST: retourne un entier correspondant à la valeur associée à la clé `key` dans le dictionnaire telle que (key, value) in dico; 
    // pas de moditifcation du dictionnaire (key ou value)
int search_in_dict(Dico_t tree, char* key){
    Node_tree_t node = get_parent_from_key(tree,key);
    return node->value;
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé existe dans le dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire
bool exist_in_dict(Dico_t tree, char* key){
    Node_tree_t node = get_parent_from_key(tree,key);
    if (node == NULL) return false;
    return (strcmp(node->key,key)==0);
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)}
    //true: si la clé existe et le couple (key, value) est supprimée du dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool remove_from_dict(Dico_t tree, char* key){
    Node_tree_t node = get_parent_from_key(tree,key);
    Node_tree_t new_node=NULL;
    Node_tree_t moving_node=NULL;
    Node_tree_t current=NULL;
    Node_tree_t sibling=NULL;

    //If node is null or does not correspond to key -> return false
    if (node == NULL || strcmp(node->key,key)!=0) return false;

    //Have 1 child 
    else if((node->left == NULL && node->right != NULL) || (node->left != NULL && node->right == NULL)){
        if (node->left == NULL) new_node = node->right;
        else new_node = node->left;
        //Select node to start parent height update
        current=new_node;
    }

    //Have 2 children
        //Choose child 'heir' (longest branches or left by default) to replace node
    else if(node->left != NULL && node->right != NULL){
        if(compute_node_balance(node)>0){
            new_node=node->right;
            moving_node=node->left;
        } 
        else{
            new_node=node->left;
            moving_node=node->right;
        } 
        
        //Assign moving_node into new_node branches
        moving_node->parent=NULL;
        attach_node(moving_node,new_node);
        //Select node to start parent height update
        current=moving_node;
    }
    //Feuille
    else if(tree->size>2){
        current=node->parent;
        current->height=0;
    }
    
    // Change in parent
    if(node->parent==NULL) tree->root=new_node;
    else if(strcmp(key,node->parent->key)<0) node->parent->left=new_node;
    else node->parent->right=new_node;

    //Update height
    update_height_to_root(current,tree);

    //de-alloc memory for node
    free(node->key);
    free(node);
    tree->size--;
    return true;
}

bool modify_in_dict(Dico_t tree, char* key, int value){
    Node_tree_t node = get_parent_from_key(tree,key);
    if (node==NULL || strcmp(key,node->key)!=0) return false;
    node->value=value;
    return true;
}
