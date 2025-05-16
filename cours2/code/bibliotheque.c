// Auteur: Pierre-André Marchand
// Description: Programme pour encoder des livres (titre, année, nombre de pages). 
    // En se basant sur 2025 - année + n. pages, une priorité est calculée
    // Le livre avec le plus petit score de priorité est suggéré comme lecture et est enlevé de la liste

#include "priority_queue.h"
#include <string.h>
#define MAX_STRING 50 
#define MAX_SIZE 100

typedef struct {
    int year;
    int n_pages;
    int priority;
    char title[MAX_STRING];
} Books;

typedef Books* Books_t;

struct PQ {
    int* heap;
    int size;
    int capacity;
    int (*leq)(int, int);
};

//PRE: -
//POST: Une liste de livre (Books_t) est crée
Books_t create_books(void){
    Books_t my_books = malloc(MAX_SIZE*sizeof(Books));
    return my_books;
}

//PRE: Nécessite l'année du livre, son nombre de page et un entier "counter" qui incrémente à chaque ajout de livre
//POST: Retourne un entier qui représente la priorité (prioritaire = entier le plus petit). 
    // La pénalité est calculée comme: (2025-year) + n_pages + nombre d'ajout (pénalisant les plus récents)
int compute_priorities(int year, int n_pages, int counter){
    return 2025-year+n_pages+counter;
}

//PRE: Auncune
//POST: Vide le tampon d'entrée rempli par scanf  (necessaire pour utiliser fgets)
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//PRE: Une chaine de caractère
//POST: Un entier naturel qui est la longueur de la chaine de caractère
int taille_str(char* str){
    int i=0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

//PRE: my_books et my_priorities sont initialisées ; un entier "counter" est défini.
//POST: Ajoute des livres à la liste
int encode_books(Books_t my_books, PQ_t my_priorities, int counter){
    if (!is_pq_full(my_priorities)) {
        printf("Veuillez encoder votre livre \n");
        printf("- Titre du livre:");
        fgets(my_books[my_priorities->size].title, sizeof(my_books[my_priorities->size].title), stdin);
        my_books[my_priorities->size].title[strcspn(my_books[my_priorities->size].title, "\n")] = '\0';

        printf("- Année du livre:");
        scanf("%i",&my_books[my_priorities->size].year);

        printf("- Nombre de pages du livre:");
        scanf("%i",&my_books[my_priorities->size].n_pages);

        my_books[my_priorities->size].priority = compute_priorities(my_books[my_priorities->size].year,my_books[my_priorities->size].n_pages,counter);
        // printf("Titre %s Année %i Pages %i Priority %i\n",
        //     my_books[my_priorities->size].title,
        //     my_books[my_priorities->size].year,
        //     my_books[my_priorities->size].n_pages,
        //     my_books[my_priorities->size].priority);

        my_priorities = add_to_pq(my_priorities, my_books[my_priorities->size].priority);
        counter++;
    }
    else{
        printf("La file de priorité est pleine.\n");
    }
    clear_stdin();
    return counter;
}

//PRE: Requiert une liste de livres (type Books_t) initiée et non vide, 
    // requiert un entier "place" compris entre [0;size-1[
    // requiert un entier "size" indiquant la taille de la liste 
//POST: Retourne une liste de livre où l'élément à "place" est remplacé par son suivant et ainsi de suite jusqu'à la fin de la liste
    // NB: Les éléments au-delà de la fin de la liste de sont pas mis à NULL vu qu'ils ne seront pas tenu en compte ultérieurement 
Books_t shift_left_books(Books_t my_books, int place, int size){
    int i=place;
    while (i<size-1){
        my_books[i]=my_books[i+1];
        i++;
    }
    return my_books;
}

//PRE: File de priorité des livres est initialisée et non nulle ; Liste de livres est initialisée et non nulle 
//POST: Retourne une suggestion de livre à l'écran; enlève l'élément le plus priorité de la queue; place en dernière position de la liste de livre le livre suggéré
void suggest_book(Books_t my_books, PQ_t my_priorities){
    if(!is_pq_empty(my_priorities)){
        int priority = peek_pq(my_priorities);
        bool found=false;
        int i=0;
        while(found==false && i<my_priorities->size){
            if(my_books[i].priority == priority) found=true;
            else i++;
        }
        if(found){
            printf("Suggestion à lire: %s \n",my_books[i].title);
            my_books = shift_left_books(my_books, i, my_priorities->size);
            my_priorities = serve_pq(my_priorities);
        }
        else{
            printf("Priorité non trouvée dans la liste de livre \n");
        }
    }
    else{
        printf("La liste de livres est vide. Pas de suggestion possible\n");
    }
}


//PRE: Requiert deux entiers
//POST: Retourne la différence de a et b
int leq(int a, int b){
    return a-b;
}

void main(){
    int counter=0;
    int menu=1;
    Books_t my_books = create_books();
    PQ_t my_priorities = create_pq(leq);
    my_priorities->size=0;
    my_priorities->capacity=MAX_SIZE;
    while(true){
        if(menu==-1){
            printf("Arrêt du programme\n");
            free(my_books);
            free(my_priorities); 
            exit(0);
        }
        else if(menu==1){
            counter = encode_books(my_books, my_priorities, counter);
        }
        else if(menu==2){
            suggest_book(my_books, my_priorities);
        }
        printf("Que souhaitez-vous faire ? Encoder un livre (1), Recevoir une suggestion(2), Arrêter le programme (-1)?");
        scanf("%i",&menu);
        clear_stdin();
    } 
}