/*
Auteur: Pierre-André Marchand
Description: Permet de jouer à un jeu de bataille de base sans interactions
*/

#include <string.h>
#include <stdbool.h>
#include "pile.h"
#include "queue.h"
#include <time.h>

typedef struct Dico{
    int id;
    int force;
    char couleur[10];
    char nom[10];
} Dico;

//PRE: Structure Dico définie ayant pour alias Dico
//POST: Une structure dico représente les 52 cartes possibles. 
    //Chaque carte porte un id (0:51), une force (0:12), une couleur (coeur, carreau, trèfle, pique)
    //et un nom correspondant à sa force (nombre, valet, dame, roi, as)
Dico* init_cartes_dico(){
    int force;
    Dico* carte = (Dico*)malloc(52 * sizeof(Dico)); // Allouer de la mémoire pour 52 cartes
    if (carte == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    for(int i=0;i<52;i++){
        carte[i].id=i;
        carte[i].force = i % 13;

        switch (carte[i].force){
            case 0:
                strcpy(carte[i].nom, "2");    
                break;
            case 1:
                strcpy(carte[i].nom, "3");    
                break;
            case 2:
                strcpy(carte[i].nom, "4");    
                break;
            case 3:
                strcpy(carte[i].nom, "5");    
                break;
            case 4:
                strcpy(carte[i].nom, "6");    
                break;
            case 5:
                strcpy(carte[i].nom, "7");    
                break;
            case 6:
                strcpy(carte[i].nom, "8");    
                break;
            case 7:
                strcpy(carte[i].nom, "9");    
                break;
            case 8:
                strcpy(carte[i].nom, "10");    
                break;
            case 9:
                strcpy(carte[i].nom, "valet");    
                break;
            case 10:
                strcpy(carte[i].nom, "dame");    
                break;
            case 11:
                strcpy(carte[i].nom, "roi");    
                break;
            case 12:
                strcpy(carte[i].nom, "as");    
                break;      
            default:
                fprintf(stderr, "Force de carte non supportée\n");
                exit(1);
        }   
        if(i<13){
            strcpy(carte[i].couleur, "pique");  
        }
        else if(i<13*2){
            strcpy(carte[i].couleur, "trefle");  
        }
        else if(i<13*3){
            strcpy(carte[i].couleur, "carreau");  
        }
        else{
            strcpy(carte[i].couleur, "coeur");  
        }
    }
    return carte;
}

//PRE: Une stack source et tmp sont initialisées. Une queue hand_a et hand_b sont initialisées.
//POST: Chaque queue (hand_a du joueur A et hand_b B) contient 26 nombres entiers (0:51) réparti aléatoirement 
void distribute(Stack_t source,Stack_t tmp,Queue_t hand_a,Queue_t hand_b){
    srand(time(NULL));
    //Build source
    int i;
    for(i=0;i<52;i++){
        add_to_stack(source,i);
    }

    //Random distribution of the cards
    int skip;
    int picked;
    int not_taken;
    int j;
    while(size_stack(source)>0){
        //Number of cards to skip from source before getting the card
        skip=rand() % size_stack(source); //e.g. size of 10: x % 10 = [0,9]; 
        for(j=0;j<skip;j++){ //if skip = 0 then no skip, if skip = 9
            not_taken = remove_from_stack(source);
            add_to_stack(tmp,not_taken);
        }
        picked = remove_from_stack(source);
        if(size_queue(hand_a) <= size_queue(hand_b)){           
            enqueue(hand_a,picked);
        }
        else{
            enqueue(hand_b,picked);
        }
        for(j=0;j<skip;j++){
            not_taken = remove_from_stack(tmp);
            add_to_stack(source,not_taken);
        }
    }
}

//PRE: Une stack source et une queue destination sont initialisées. La stack contient au moins un élément.
//POST: Tous les éléments de la stack sont transférés à la queue de destinations.
void add_cards_to_hand(Stack_t source, Queue_t destination){
    int value;
    while(size_stack(source)>0){
        value=remove_from_stack(source);
        enqueue(destination,value);
    }
}

//PRE: Une stack tmp vide et deux queues (hand_a du joueur A et hand_b B) ayant au moins une carte.
//POST: Résolution d'un coup. Retourne:
    // true: si la partie peut continuer
    // false: si la parte est terminée par manque de carte pour un joueur
bool simple_shot(Stack_t tmp,Queue_t hand_a, Queue_t hand_b, Dico* cartes, int counter){
    if(size_queue(hand_a)==0 || size_queue(hand_b)==0) return false;
    int card_a;
    int card_b;
    card_a = dequeue(hand_a);
    add_to_stack(tmp,card_a);
    card_b = dequeue(hand_b);
    add_to_stack(tmp,card_b);
    if (card_a % 13 > card_b % 13){
        printf("Coup %i | Joueur A: %-8s de %-8s | Joueur B: %-8s de %-8s | Joueur A gagne (+ %i cartes) !\n",
            counter, 
            cartes[card_a].nom,cartes[card_a].couleur,
            cartes[card_b].nom,cartes[card_b].couleur,
            size_stack(tmp)
        );
        add_cards_to_hand(tmp,hand_a);
        if(size_queue(hand_b)==0) return false;
    }
    else if (card_a % 13 < card_b % 13){
        printf("Coup %i | Joueur A: %-8s de %-8s | Joueur B: %-8s de %-8s | Joueur B gagne (+ %i cartes) !\n",
            counter, 
            cartes[card_a].nom,cartes[card_a].couleur,
            cartes[card_b].nom,cartes[card_b].couleur,
            size_stack(tmp)
        );
        add_cards_to_hand(tmp,hand_b);
        if(size_queue(hand_a)==0) return false;
    }
    else if (card_a % 13 == card_b % 13){
        printf("Coup %i | Joueur A: %-8s de %-8s | Joueur B: %-8s de %-8s | Bataille !\n",
            counter, 
            cartes[card_a].nom,cartes[card_a].couleur,
            cartes[card_b].nom,cartes[card_b].couleur
        );
        if(size_queue(hand_a)==0 || size_queue(hand_b)==0) return false;
        card_a = dequeue(hand_a);
        add_to_stack(tmp,card_a);
        card_b = dequeue(hand_b);
        add_to_stack(tmp,card_b);
        simple_shot(tmp,hand_a,hand_b,cartes,counter);
    }
    return true;
}

void main(){
    //Initialisation dictionnaire de carte
    Dico* cartes = init_cartes_dico();

    //Init des stacks
    Queue_t hand_a = new_queue();
    Queue_t hand_b = new_queue();
    Stack_t source = new_stack();
    Stack_t tmp = new_stack();

    //Mélanger et distribuer
    distribute(source,tmp,hand_a,hand_b);
    printf("Joueur A\n");
    display_queue(hand_a);
    printf("Joueur B\n");
    display_queue(hand_b);

    printf("%s de %s\n",cartes[51].nom,cartes[51].couleur);

    //La partie continue tant que les deux joueurs ont des cartes
    bool game_not_over=true;
    int counter=0;
    while(game_not_over){
        counter++;
        game_not_over=simple_shot(tmp,hand_a,hand_b,cartes,counter);
        //sleep(1);
    }
    if(size_queue(hand_a)==0 && size_queue(hand_b)==0){
        printf("Partie nulle: les deux joueurs n'ont plus de carte\n");
    }
    else if(size_queue(hand_a)==0){
        printf("Le joueur B gagne la partie\n");
    }
    else if(size_queue(hand_b)==0){
        printf("Le joueur A gagne la partie\n");
    }
    
    // printf("Joueur A\n");
    // display_queue(hand_a);
    // printf("Joueur B\n");
    // display_queue(hand_b);

    free(cartes);
    // destroy_stack(source);
    // destroy_stack(tmp);
    // destroy_queue(hand_a);
    // destroy_queue(hand_b);
}
