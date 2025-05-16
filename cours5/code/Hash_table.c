#include "listes_chainees_dict.h"
#include "Hash_table.h"

struct Node_SC_List{
    char* key;
    int value;
    struct Node_SC_List* next;
};

struct SC_List{
    Node_SC_List_t head;
    int size;
};

struct Hash_table{
    SC_List_t list;
    int size;
    int capacity;
    int load;
};

//PRE: Une chaine de caractère non vide
//POST: Retourne la valeur de hachage de la clé
int hash(const char* key, int capacity){
    srand(123);
    int hash = 0;
    int randNum;
    while (*key != '\0') {
        randNum = rand()%1000;
        hash = (hash +  ((int)*key)*randNum) % capacity;
        key++;
    }
    return hash ;
}

//PRE: /
//POST: retourne une table de hachage vide
Hash_table_t create_hash_table(int capacity){
    Hash_table_t ht = malloc(capacity*sizeof(struct Hash_table));
    if (ht == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    int i;
    for(i=0;i<capacity;i++){
        ht[i].list = init_SC_list(); 
    }
    ht->size=0;
    ht->load=0;
    ht->capacity=capacity;
    return ht;
}

//PRE: Une hash table initialisée
//POST: Désalloue la hash table de la mémoire et ses composants
void destroy_hash_table(Hash_table_t ht){
    int i;
    for(i=0;i<ht->capacity;i++){
         destroy_SC_list(ht[i].list); 
    }
    free(ht);
}

//Fonction auxiliaire
int exist_in_list(Node_SC_List_t node, const char* key){
    if(strcmp(key,node->key)==0) return true;
    else if(node->next==NULL) return false;
    else{
        return exist_in_list(node->next,key);
    }
}

//PRE: Une hash table initialisée non-vide
//POST: Nouveau pointeur vers une hash table agrandie comprenant les éléments précédemment présent
    // La table de l'input est détruite
Hash_table_t extend_hash_table(Hash_table_t ht){
    Hash_table_t new_ht=create_hash_table(ht->capacity*2);
    new_ht->capacity=ht->capacity*2;
    int i;
    Node_SC_List_t node;
    for(i=0;i<ht->capacity;i++){
        node=ht[i].list->head;
        while(node!=NULL){
            add_to_hash_table(&new_ht,node->key,node->value);
            node=node->next;
        }
    }
    destroy_hash_table(ht);
    return new_ht;
}

//PRE: Le (double) pointeur vers une table de hachage initialisée;`key` est une chaîne de caractère initialisée
//POST: retourne un booléen 
    //true: si la clé existe dans la table de hachage
    //false: si la clé n'existe pas dans la table de hachage
bool add_to_hash_table(Hash_table_t* ht_ptr, const char* key, int value){
    Hash_table_t ht=*ht_ptr;
    int index = hash(key,ht->capacity);
    SC_List_t list = ht[index].list;
    //printf("Index of table %i having pointer %p\n",index,&ht[index]);
    bool found = false;
    if(list->size==0){
        append_SC_list(list,key,value);
        ht->size++;
        ht->load++;
        int load_threshold=(ht->capacity*2)/3;
        if(load_threshold<ht->load){
            *ht_ptr = extend_hash_table(ht);
        }
        //extend
        return true;
    }
    else if(list->size>0){
        found = exist_in_list(list->head,key);
    }
    if(!found){
        append_SC_list(list,key,value);
        ht->size++;
        return true;
    }
    else return false;
}

//PRE: Une table de hachage initialisée;`key` est une chaine de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé existe dans la table de hachage
    //false: si la clé n'existe pas dans la table de hachage
bool exist_in_hash_table(Hash_table_t ht, const char* key){
    int index = hash(key,ht->capacity);
    SC_List_t list = ht[index].list;
    bool found = false;
    if(list->size>0){
        found = exist_in_list(list->head,key);
    }
    return found;
}

int search_in_list(Node_SC_List_t node, const char* key){
    if(strcmp(key,node->key)==0) return node->value;
    else if(node->next==NULL) return 0;
    else{
        return search_in_list(node->next,key);
    }
}

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & `key` existe dans la table de hachage
//POST: retourne un entier correspondant à la valeur associée à la clé `key` dans la table de hachage telle que (key, value) in table;
int search_in_hash_table(Hash_table_t ht, const char* key){
    if(exist_in_hash_table(ht,key)){
        int index = hash(key,ht->capacity);
        SC_List_t list = ht[index].list;
        return search_in_list(list->head,key);
    }
    else{
        fprintf(stderr,"key did not exist in hash table\n");
        exit(1);
    }
}

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & `key` existe dans la table de hachage
//POST: Retire l'élément' `key`-`value` de la hash table
    //true: si la clé existe et le couple (key, value) est supprimée du dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool remove_in_hash_table(Hash_table_t ht, const char* key){
    int index = hash(key,ht->capacity);
    SC_List_t list = ht[index].list;
    bool result = serve_SC_list(list,key);
    return result;
}

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & 
//  `key` existe dans la table de hachage & `value` est un entier
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)} U {(key, value')}
        //true: si la clé existe et la valeur associée à la clé est modifiée
        //false: si la clé n'existe pas dans le dictionnaire, pas de modification de la hash table
bool modify_in_hash_table(Hash_table_t ht, const char* key, int value){
    int index = hash(key,ht->capacity);
    SC_List_t list = ht[index].list;
    Node_SC_List_t current=list->head;
    while(current != NULL){
        if(strcmp(key,current->key)==0){
            current->value=value;
            return true;
        }
        current=current->next;
    }
    return false;
}
