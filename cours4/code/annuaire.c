#include "Dict.h"
#include <stdbool.h>
#include <string.h>
#define MAX_CHAR_SIZE 50

// Determiner OS pour commande du clear console
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif
// Clear console (dependant de l'OS)
// PRE: macro variable CLEAR_COMMAND qui dépendant de l'OS
// POST: introduit un clear console
void clear_console(void) {
    system(CLEAR_COMMAND);
}

//Structures à déclarer
struct Node_tree{
    char* key;
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

//PRE: Auncune
//POST: Vide le tampon d'entrée rempli par scanf  (necessaire pour utiliser fgets)
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//PRE: Un dictionnaire initialisé & une entrée utilisateur de numéro  entre 0 et (2^31)-1 & une entrée utilisateur de nom de max 50 caractères 
//POST: L'entrée est ajoutée à l'annuaire si le nom d'utilisateur n'existe pas dans le dictionnaire
void menu_enter(Dico_t phone_book){
    clear_stdin();
    char key[MAX_CHAR_SIZE];
    long long int number;
    printf("Création d'une nouvelle entrée\n");
    printf("Nom: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key,"\n")]='\0';
    printf("Numero:");
    scanf("%lli",&number);
    bool added = add_to_dict(phone_book,key,number);
    if(added){
        printf("Le numéro %lli de %s a été ajouté à l'annuaire\n",number,key);
    }
    else{
        printf("Le nom %s existe déjà dans l'annuaire. L'entrée est annulée\n",key);
    }
}
//PRE: Un dictionnaire initialisé et non-vide & une entrée utilisateur de nom  de max 50 caractères 
//POST: Affiche le numéro correspondant au nom si celui-ci existe dans l'annuaire 
void menu_search(Dico_t phone_book){
    clear_stdin();
    char key[MAX_CHAR_SIZE];
    long long int number;
    printf("Recherche d'une entrée existante\n");
    printf("Nom: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key,"\n")]='\0';
    bool found = exist_in_dict(phone_book,key);
    if(found){
        number = search_in_dict(phone_book,key);
        printf("Le numéro associé au nom %s est %lli\n",key,number);
    }
    else{
        printf("Le nom %s na pas été trouvé dans l'annuaire\n",key);
    }
}
//PRE: Un dictionnaire initialisé et non-vide & une entrée utilisateur de numéro  entre 0 et (2^31)-1 & une entrée utilisateur de nom de max 50 caractères 
//POST: L'entrée correspondante au nom entré par l'utilisateur est modifiée avec le numéro si le nom existe dans le dictionnaire
void menu_modify(Dico_t phone_book){
    clear_stdin();
    char key[MAX_CHAR_SIZE];
    long long int number;
    printf("Modification d'une entrée existante\n");
    printf("Nom: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key,"\n")]='\0';
    printf("Numero:");
    scanf("%lli",&number);
    bool found = exist_in_dict(phone_book,key);
    if(found){
        long long int old_number = search_in_dict(phone_book,key);
        modify_in_dict(phone_book,key,number);
        printf("Le numéro associé au nom %s a été transformé: %lli -> %lli\n",key,old_number,number);
    }
    else{
        printf("Le nom %s na pas été trouvé dans l'annuaire\n",key);
    }
}
//PRE: Un dictionnaire initialisé et non-vide & une entrée utilisateur de nom  de max 50 caractères 
//POST:  L'entrée correspondante au nom entré par l'utilisateur est supprimée de l'annuaire si le nom existe dans le dictionnaire
void menu_delete(Dico_t phone_book){
    clear_stdin();
    char key[MAX_CHAR_SIZE];
    long long int number;
    printf("Suppression d'une entrée existante\n");
    printf("Nom: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key,"\n")]='\0';
    bool found = exist_in_dict(phone_book,key);
    if (found) {
        number = search_in_dict(phone_book,key);
        found = remove_from_dict(phone_book,key);
    }
    if(found){
        printf("L'entrée de %s (numéro: %lli) a été supprimé de l'annuaire\n",key,number);
    }
    else{
        printf("Le nom %s n'a pas été trouvé dans l'annuaire\n",key);
    }
}
//PRE: Un dictionnaire initialisé & des entrées d'entier par l'utilisateur
//POST: Choix d'une option
void menu(Dico_t phone_book){
    unsigned int menu_selection=0;
    bool keep_going=true;
    while(keep_going){
        //clear_console();
        while(menu_selection<1 || menu_selection>5){
            printf("Que souhaitez-vous faire ?\n"); 
            printf("(1) Entrer une nouvelle entrée dans l'annuaire (2) Chercher un numéro de téléphone par nom \n"); 
            printf("(3) Modifier un numéro de téléphone (4) Supprimer une entrée de l'annuaire\n"); 
            printf("(5) Quitter l'annuaire:\n");                
            scanf("%i",&menu_selection);
        }
        //clear_console();
        if (menu_selection==1){           
            menu_enter(phone_book);
            balance_tree(phone_book);
        }
        else if (menu_selection==2){
            menu_search(phone_book);
        }
        else if (menu_selection==3){
            menu_modify(phone_book);
        }
        else if (menu_selection==4){
            menu_delete(phone_book);
            balance_tree(phone_book);
        }
        else if (menu_selection==5){
            printf("Arrêt du programme...\n");
            keep_going=false;
        }
        else{
            fprintf(stderr,"Option de menu inconnue\n");
            exit(1);       
        }           
        menu_selection=0;
        // clear_stdin();
        // printf("Appuyer sur n'importe quelle touche pour continuer\n");
        // getchar();
    }
}  

int main(){
    Dico_t phone_book = create_dict();
    menu(phone_book);
    destroy_dict(phone_book);
}