#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Hash_table;
typedef struct Hash_table* Hash_table_t;

//PRE: Une chaine de caractère non vide
//POST: Retourne la valeur de hachage de la clé
int hash(const char* key, int capacity);

//PRE: /
//POST: retourne une table de hachage vide
Hash_table_t create_hash_table(int capacity);

//PRE: Une table de hachage initialisée
//POST: Désalloue la table de hashage et ses composants de la mémoire
void destroy_hash_table(Hash_table_t ht);

//PRE: Une table de hachage initialisée et non vide
//POST: Une nouvelle table de hachage élargie comprenant les entrées de la table d'input
Hash_table_t extend_hash_table(Hash_table_t table);

//PRE: Le (double) pointeur vers une table de hachage initialisée;`key` est une chaîne de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé n'existe pas apriori dans la table de hachage; la clé et l'entier sont ajouté à la table de hashage 
    //false: si la clé existe dans la table de hachage; la clé et l'entier ne sont pas ajouté à la table de hashage 
bool add_to_hash_table(Hash_table_t* table_ptr, const char* key, int value);

//PRE: Une table de hachage initialisée;`key` est une chaine de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé existe dans la table de hachage
    //false: si la clé n'existe pas dans la table de hachage
bool exist_in_hash_table(Hash_table_t table, const char* key);

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & `key` existe dans la table de hachage
//POST: retourne un entier correspondant à la valeur associée à la clé `key` dans la table de hachage telle que (key, value) in table;
int search_in_hash_table(Hash_table_t table, const char* key);

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & `key` existe dans la table de hachage
//POST: Retire l'élément' `key`-`value` de la hash table
    //true: si la clé existe et le couple (key, value) est supprimée du dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool remove_in_hash_table(Hash_table_t table, const char* key);

//PRE: Une table de hachage initialisée &`key` est une chaine de caractère initialisée & 
//  `key` existe dans la table de hachage & `value` est un entier
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)} U {(key, value')}
        //true: si la clé existe et la valeur associée à la clé est modifiée
        //false: si la clé n'existe pas dans le dictionnaire, pas de modification de la hash table
bool modify_in_hash_table(Hash_table_t table, const char* key, int value);


