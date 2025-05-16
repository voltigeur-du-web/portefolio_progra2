#include "Dict.h"
#include "Hash_table.h"
#define MAX_TABLE_SIZE 10

struct Dico{
    Hash_table_t table;
};

//PRE: /
//POST: retourne un dictionnaire vide
Dico_t create_dict(){
    Dico_t dict = (Dico_t)malloc(sizeof(struct Dico));
    if (dict == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    Hash_table_t table = create_hash_table(MAX_TABLE_SIZE);
    dict->table=table;
    return dict;
}

//PRE: Dico est initialisé
//POST: Supprime le dictionnaire et tous ses composants de la mémoire
    //Retourne 0 si de-allocation ok
int destroy_dict(Dico_t dico){
    destroy_hash_table(dico->table);
    free(dico);
    return 0;
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier 
//POST: retourne un boleen 
    //true: si la clé est unique ; la nouvelle clé et sa valeur sont ajoutées au dictionnaire
    //false: si la clé existe déjà dans le dictionnaire
bool add_to_dict(Dico_t dico, const char* key, int value){
    bool result = add_to_hash_table(&dico->table,key,value);
    return result;
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé existe dans le dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire
bool exist_in_dict(Dico_t dico, char* key){
    bool result = exist_in_hash_table(dico->table,key);
    return result;
}

//PRE: Dico est initialisé;`key` et `value` est sont initialisés; `key` existe dans le dictionnaire 
//POST: retourne un entier correspondant à la valeur associée à la clé `key` dans le dictionnaire telle que (key, value) in dico; 
// pas de moditifcation du dictionnaire (key ou value)
int search_in_dict(Dico_t dico, char* key){
    if(exist_in_dict(dico, key)){
        int value = search_in_hash_table(dico->table,key);
        return value;
    }
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)}
    //true: si la clé existe et le couple (key, value) est supprimée du dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool remove_from_dict(Dico_t dico, char* key){
    bool result = remove_in_hash_table(dico->table,key);
    return result;
}

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)} U {(key, value')}
    //true: si la clé existe et la valeur associée à la clé est modifiée
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool modify_in_dict(Dico_t dico, char* key, int value){
    bool result = modify_in_hash_table(dico->table,key,value);
    return result;
}
