#include "listes_chainees_dict.h"

struct Node_SC_List{
    char* key;
    int value;
    struct Node_SC_List* next;
};
typedef struct Node_SC_List* Node_SC_List_t;

struct SC_List{
    Node_SC_List_t head;
    int size;
};
typedef struct SC_List* SC_List_t;

//PRE: -
//POST: La liste chainée est initialisée
SC_List_t init_SC_list(void){
    SC_List_t list = malloc(sizeof(struct SC_List));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    list->size=0;
    list->head=NULL;
    return list;
}

//PRE: Une liste chainée initialisée et une parie de clé-valeur qui sont une chaine de charactère et un entier respectivement
//POST: Ajout un nouveau noed à la chaine ayant une structure clé-valeur 
void append_SC_list(SC_List_t list, const char* key, int value){
        Node_SC_List_t new = malloc(sizeof(struct Node_SC_List));
        if (new == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(1);
        }
        new->value=value;
        new->key = (char*)malloc(strlen(key) + 1);
        strcpy(new->key,key); 
        new->next=NULL;

        if(list->size==0){
            list->head=new;
        }
        else if (list->size>=1){
            Node_SC_List_t previous = list->head;
            while (previous->next != NULL ){
                previous = previous->next;
            }
            previous->next = new;
        }
        list->size++;
}

//PRE: Une liste chainée initialisée non-nulle et une clé
//POST: Si la clé existe dans la chaine alors le noeud ayant une structure clé-valeur est enlevé 
    // Retourne true si la cré est trouvée
    // Retourne false sinon
bool serve_SC_list(SC_List_t list, const char* key){
    Node_SC_List_t new = malloc(sizeof(struct Node_SC_List));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    if(list == NULL || list->size==0 || list->head == NULL) return false;
    else if(list->size==1 && strcmp(list->head->key,key)==0){
        list->head=NULL;
        list->size--;
        return true;
    }
    Node_SC_List_t current=NULL;
    Node_SC_List_t previous=NULL;
    Node_SC_List_t next=list->head;
    bool found=false;
    while(next !=NULL && !found){
        previous=current;
        current=next;
        next=current->next;
        found = strcmp(current->key,key)==0 ? true : false;
    }
    if (!found) return false;
    else{
        //head
        if(previous == NULL && next != NULL) list->head = next;
        //middle
        else if (next != NULL) previous->next = next;
        //tail
        free(current);
        list->size--;
        return true;
    }
}

//PRE: Une liste chainée initialisée et non vide
//POST: Affiche les clé-valeur de chaque élément de la liste chainées
void display_SC_list(SC_List_t list){
    Node_SC_List_t current = list->head;
    printf("Liste chainée simple\n");
    while (current != NULL){
        printf("key=%s value=%i\n", current->key, current->value);
        current = current->next;
    }
}

//PRE: Une liste chainée initialisée
//POST: Supprime et libère l'allocation en mémoire de la liste chainée
void destroy_SC_list(SC_List_t list){
    Node_SC_List_t current = list->head;
    Node_SC_List_t previous = NULL;
    while (current != NULL){
        previous = current;
        current = current->next;
        free(previous);
    }
    free(list);
}