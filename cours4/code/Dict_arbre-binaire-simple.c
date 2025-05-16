#include <string.h>

#include "utils_Dict.h"
#include "Dict.h"

//Déclaration structure
struct Node_tree{
    char* key;
    //const char key[MAX_CHAR_SIZE];
    int height;
    long long int value;
    struct Node_tree* parent;
    struct Node_tree* left;
    struct Node_tree* right;
};
typedef struct Node_tree* Node_tree_t;

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

//PRE: Dico est initialisé
//POST: Supprime le dictionnaire et tous ses composants de la mémoire
    //Retourne 0 si de-allocation ok
    //Retourne 1 sinon
int destroy_dict(Dico_t tree){
    if(tree->root != NULL) destroy_node(tree->root);
    free(tree);
    return 0;
}

// Fonction auxiliaire récursive pour mettre à jour la hauteur des feuille d'un arbre à partir d'un noeud
// PRE: `tree` est un arbre initialisé, `node` est un noeud de cet arbre
// POST: Met à jour la hauteur des noeuds entre le noeud et la racine de l'arbre; 
    // La hauteur `height` étant définie comme le nombre de noeuds jusqu'à la feuille la plus éloignée
    // Retourne un entier 0 si le noeud est null, sinon retourne 1
int update_height_to_root(Node_tree_t node, Dico_t tree){
    if(node == NULL){
        return 0;
    }
    else if(node==tree->root || node->parent == NULL){
        return 1;
    }
    else{
        int left_height = (node->parent->left == NULL) ? 0 : node->parent->left->height;
        int right_height = (node->parent->right == NULL) ? 0 : node->parent->right->height;
        node->parent->height = max(left_height,right_height)+1;
        update_height_to_root(node->parent,tree);
    }
    return 1;
}

//Fonction auxiliaire pour rattacher un noeud aux branches d'un autre noeud
//PRE: `moving` et `base` sont des pointeurs vers deux noeuds d'un même arbre initialisé
//POST: Retourne un booleen `false` si la clé du noeud `moving` est identique à la clé de `base`; sinon retourne `true`
    // Attache le noeud `moving` comme un des descendant du noeud `base`
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

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier 
//POST: retourne un boleen 
    //true: si la clé est unique ; la nouvelle clé et sa valeur sont ajoutées au dictionnaire
    //false: si la clé existe déjà dans le dictionnaire
bool add_to_dict(Dico_t tree, const char* key, long long int value){
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
// PRE: `tree` un arbre initialisé; `key` une chaine de caractère non nul
// POST: Retourne un pointeur vers un noeud de l'arbre:
    // - Soit la clé est trouvée dans l'arbre et c'est le noeud qui la contient
    // - Sinon vers une feuille de l'arbre dans la direction duquel la recherche de la clé a eu lieu mais n'a pas abouti 
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
long long int search_in_dict(Dico_t tree, char* key){
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

bool modify_in_dict(Dico_t tree, char* key, long long int value){
    Node_tree_t node = get_parent_from_key(tree,key);
    if (node==NULL || strcmp(key,node->key)!=0) return false;
    node->value=value;
    return true;
}
