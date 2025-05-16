#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Dico;
typedef struct Dico* Dico_t;

//PRE: /
//POST: retourne un dictionnaire vide
Dico_t create_dict();

//PRE: Dico est initialisé
//POST: Supprime le dictionnaire et tous ses composants de la mémoire
    //Retourne 0 si de-allocation ok
    //Retourne 1 sinon
int destroy_dict(Dico_t dico);

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier 
//POST: retourne un boleen 
    //true: si la clé est unique ; la nouvelle clé et sa valeur sont ajoutées au dictionnaire
    //false: si la clé existe déjà dans le dictionnaire
bool add_to_dict(Dico_t dico, const char* key, int value);

//PRE: Dico est initialisé;`key` et `value` est sont initialisés; `key` existe dans le dictionnaire 
//POST: retourne un entier correspondant à la valeur associée à la clé `key` dans le dictionnaire telle que (key, value) in dico; 
    // pas de moditifcation du dictionnaire (key ou value)
int search_in_dict(Dico_t dico, char* key);

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen 
    //true: si la clé existe dans le dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire
bool exist_in_dict(Dico_t dico, char* key);

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)}
    //true: si la clé existe et le couple (key, value) est supprimée du dictionnaire
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool remove_from_dict(Dico_t dico, char* key);

//PRE: Dico est initialisé;`key` est une chaine de caractère initialisée;`value` est un entier
//POST: retourne un boleen : si il existe (key, value) in dico : dict' = dict \ {(key, value)} U {(key, value')}
    //true: si la clé existe et la valeur associée à la clé est modifiée
    //false: si la clé n'existe pas dans le dictionnaire, pas de modification du dictionnaire
bool modify_in_dict(Dico_t dico, char* key, int value);