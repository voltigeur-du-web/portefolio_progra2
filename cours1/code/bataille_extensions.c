/*
Auteur: Pierre-André Marchand
Description: Permet de jouer à un jeu de bataille complexe (jusqu'à la 5e extension)
*/

#include <string.h>
#include <stdbool.h>
#include "pile.h"
#include "queue.h"
#include <time.h>

typedef enum card_color {
    pique = 0,
    trefle = 1,
    carreau = 2,
    coeur = 3
}card_color;

typedef struct Dico{
    int id;
    int force;
    char couleur[10];
    card_color couleur_id;
    char nom[10];
} Dico;


//PRE: Structure Dico définie ayant pour alias Dico
//POST: Retourne un pointeur vers structure Dico représente les 52 cartes possibles. 
    //Chaque carte porte un id (0:51), une force (0:12), une couleur (coeur, carreau, trèfle, pique), une couleur_id (0:3)
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
            carte[i].couleur_id=pique;  
        }
        else if(i<13*2){
            strcpy(carte[i].couleur, "trefle");  
            carte[i].couleur_id=trefle;  
        }
        else if(i<13*3){
            strcpy(carte[i].couleur, "carreau");  
            carte[i].couleur_id=carreau;  
        }
        else{
            strcpy(carte[i].couleur, "coeur");  
            carte[i].couleur_id=coeur;  
        }
    }
    return carte;
}

//PRE: Une queue hand_a et hand_b sont initialisées. Un booleen start est passé à la fonction pour déteriner si c'est un début de partie.
    //Si start == true, alors les queues font référence à des pointeurs distinct
    //Si start == false, alors les deux queues réfèrent le même pointeur
//POST: 
    //Si start == true (début de partie), alors chaque queue (hand_a du joueur A et hand_b B) contient 26 nombres entiers (range 0:51) réparti aléatoirement 
    //Si start == false (mélanger une main en cours de partie), alors la queue hand (pour un des deux joueurs) est remélangée de façon aléatoire
void distribute(Queue_t hand_a,Queue_t hand_b,bool start){
    srand(time(NULL));
    Stack_t buffer = new_stack();
    Stack_t source = new_stack();
    if (start){
        int i;
        for(i=0;i<52;i++){
            add_to_stack(source,i);
        }
    }
    else{
        int value;
        while(size_queue(hand_a)>0){
            value = dequeue(hand_a);
            add_to_stack(source,value);
        }
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
            add_to_stack(buffer,not_taken);
        }
        picked = remove_from_stack(source);
        if(size_queue(hand_a) <= size_queue(hand_b)){           
            enqueue(hand_a,picked);
        }
        else{
            enqueue(hand_b,picked);
        }
        for(j=0;j<skip;j++){
            not_taken = remove_from_stack(buffer);
            add_to_stack(source,not_taken);
        }
    }
    destroy_stack(buffer);
    destroy_stack(source);
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

//PRE: Un pointeur vers une structure queue "hand" représentant le tas de carte d'un joueur 
    //et un pointeur vers une structure Dico pour donner un nom / couleur aux cartes 
//POST: Retourne un entier qui représente la carte sélectionnée (interaction via la console) entre 2 cartes piochées
    // Si seulement une carte dans "hand", alors celle-ci est sélectionnée
    // En utilisant le code 999, la main du joueur est mélangée
int multi_card(Queue_t hand,Dico* cartes){
    int card;
    int select=0;
    int card1; 
    int card2;
    if (size_queue(hand) > 1){
        card1=dequeue(hand);
        card2=dequeue(hand);
        while(select !=1 && select !=2){
                printf("Veuillez choisir entre ces deux cartes: (1) %s de %s, (2) %s de %s: ",
                    cartes[card1].nom,cartes[card1].couleur,
                    cartes[card2].nom,cartes[card2].couleur);
                scanf("%i",&select);
            
            if(select == 1){
                return card1;
            }
            else if(select == 2){
                return card2;
            }
            else if(select == 999){
                bool start=false;
                enqueue(hand,card1);
                enqueue(hand,card2);
                distribute(hand,hand,start);
                card1=dequeue(hand);
                card2=dequeue(hand);
            }   
        }
    }
    else if(size_queue(hand) == 1){
        return dequeue(hand);
    }
}


//PRE: Une stack tmp vide, deux queues (hand_a du joueur A et hand_b B) ayant au moins une carte,
    //Un pointeur vers une structure Dico pour donner un nom / couleur aux cartes,
    //Un entier "counter" pour compter le nombre de coup précédemment joué,
    //Un pointeur vers un entier déjà initialisé pour définir le vainqueur précédent (1) joueur A (2) joueur B
    //Un pointeur vers un entier déjà initialisé représentant le nombre de points du joueur A dans la partie
    //Un pointeur vers un entier déjà initialisé représentant le nombre de points du joueur B dans la partie
    //Une structure card_color "atout_a" qui défini l'atout choisi par le joueur A en début de partie
    //Une structure card_color "atout_b" qui défini l'atout choisi par le joueur B en début de partie
//POST: Résolution d'un coup. 
    // Modifie "previous_winner" selon le gagnant du coup
    // Modifie "points_player_a" si le joueur A a joué un atout (-1 si perdu; +1 si gagné)
    // Modifie "points_player_b" si le joueur B a joué un atout (-1 si perdu; +1 si gagné)
    // Modifie "hand_a" ou "hand_b" (gain de cartes si le coup est gagné; perte de cartes si le coup est perdu)
    // Retourne:
        // true: si la partie peut continuer
        // false: si la parte est terminée par manque de carte pour un joueur
bool simple_shot(Stack_t tmp,Queue_t hand_a, Queue_t hand_b, Dico* cartes, 
    int counter, int* previous_winner, int* points_player_a, int* points_player_b, 
    card_color atout_a, card_color atout_b){
    //Arret si plus de carte
    if(size_queue(hand_a)==0 || size_queue(hand_b)==0) return false;
    //init
    int card_a;
    int card_b;
    char result[30];

    //Bonus pour une couleur au hasard à chaque tirage
    card_color bonus = rand() % 4;
    char bonus_char[10]="aucun";
    switch(bonus){
        case pique:
            strcpy(bonus_char, "pique");
            break;
        case trefle:
            strcpy(bonus_char, "trefle");
            break;
        case carreau:
            strcpy(bonus_char, "carreau");
            break;
        case coeur:
            strcpy(bonus_char, "coeur");
            break;
    }
    printf("Coup %i: Il y a un bonus de +1 sur la couleur %s \n",counter,bonus_char);

    //Choix entre deux cartes
    if(*previous_winner==1){
        printf("Au tour du joueur A...\n");
        card_a = multi_card(hand_a, cartes);
        add_to_stack(tmp,card_a);
        printf("Au tour du joueur B...\n");
        card_b = multi_card(hand_b, cartes);
        add_to_stack(tmp,card_b);

    }
    else{
        printf("Au tour du joueur B...\n");
        card_b = multi_card(hand_b, cartes);
        add_to_stack(tmp,card_b);
        printf("Au tour du joueur A...\n");
        card_a = multi_card(hand_a, cartes);
        add_to_stack(tmp,card_a);
    }

    //Bonus si une carte est dans la couleur bonus
    int score_a = card_a % 13;
    if (cartes[card_a].couleur_id == bonus) score_a++;
    int score_b = card_b % 13;
    if (cartes[card_b].couleur_id == bonus) score_b++;

    //Joueur A gagne
    if (score_a > score_b){
        snprintf(result, sizeof(result), "Joueur A gagne (+ %i cartes) !", size_stack(tmp));
        add_cards_to_hand(tmp,hand_a);
        *previous_winner=2;
        if (atout_a == cartes[card_a].couleur_id) (*points_player_a)++;
        if (atout_b == cartes[card_b].couleur_id) (*points_player_b)--;
        printf("Coup %i | Bonus: %-8s | Joueur A(%i): %-8s de %-8s | Joueur B(%i): %-8s de %-8s | %s\n",
            counter,bonus_char, 
            (*points_player_a),cartes[card_a].nom,cartes[card_a].couleur,
            (*points_player_b),cartes[card_b].nom,cartes[card_b].couleur,
            result);
        if(size_queue(hand_b)==0) return false;
    }
    //Joueur B gagne
    else if (score_a < score_b){
        snprintf(result, sizeof(result), "Joueur B gagne (+ %i cartes) !", size_stack(tmp));
        add_cards_to_hand(tmp,hand_b);
        *previous_winner=1;
        if (atout_a == cartes[card_a].couleur_id) (*points_player_a)--;
        if (atout_b == cartes[card_b].couleur_id) (*points_player_b)++;
        printf("Coup %i | Bonus: %-8s | Joueur A(%i): %-8s de %-8s | Joueur B(%i): %-8s de %-8s | %s\n",
            counter,bonus_char, 
            (*points_player_a),cartes[card_a].nom,cartes[card_a].couleur,
            (*points_player_b),cartes[card_b].nom,cartes[card_b].couleur,
            result);
        if(size_queue(hand_a)==0) return false;
    }
    //Bataille
    else if (score_a == score_b){
        snprintf(result, sizeof(result), "Bataille !");
        printf("Coup %i | Bonus: %-8s | Joueur A(%i): %-8s de %-8s | Joueur B(%i): %-8s de %-8s | %s\n",
            counter,bonus_char, 
            (*points_player_a),cartes[card_a].nom,cartes[card_a].couleur,
            (*points_player_b),cartes[card_b].nom,cartes[card_b].couleur,
            result);
        if(size_queue(hand_a)==0 || size_queue(hand_b)==0) return false;
        card_a = dequeue(hand_a);
        add_to_stack(tmp,card_a);
        card_b = dequeue(hand_b);
        add_to_stack(tmp,card_b);
        simple_shot(tmp,hand_a,hand_b,cartes,counter,
            previous_winner,
            points_player_a,points_player_b, 
            atout_a, atout_b);
    }
    return true;
}

void main(){
    //Initialisation dictionnaire de carte
    Dico* cartes = init_cartes_dico();
    int continuer_int=1;
    while(continuer_int==1){

        //Init des stacks
        Queue_t hand_a = new_queue();
        Queue_t hand_b = new_queue();
        Stack_t tmp = new_stack();

        //Choix des couleurs atouts
        card_color atout_a;
        printf("Joueur A, veuillez choisir votre couleur d'atout entre (0) pique, (1) trèfle, (2) carreau, (3) coeur: ");
        scanf("%u",&atout_a);

        card_color atout_b;
        printf("Joueur B, veuillez choisir votre couleur d'atout entre (0) pique, (1) trèfle, (2) carreau, (3) coeur: ");
        scanf("%u",&atout_b);

        //Mélanger et distribuer
        bool start = true;
        distribute(hand_a,hand_b,start);

        //La partie continue tant que les deux joueurs ont des cartes
        bool game_not_over=true;
        int counter=0;
        int previous_winner=1;
        int points_player_a=0;
        int points_player_b=0;
        while(game_not_over){
            counter++;
            game_not_over=simple_shot(tmp,hand_a,hand_b,cartes,counter,
                &previous_winner,&points_player_a,&points_player_b, 
                atout_a, atout_b);
        }
        
        //Fin de la partie: résultats
        if(points_player_a==points_player_b){
            printf("Partie nulle: les deux joueurs ont le même nombre de points\n");
        }
        else if(points_player_a < points_player_b){
            printf("Le joueur B gagne la partie\n");
        }
        else if(points_player_a > points_player_b){
            printf("Le joueur A gagne la partie\n");
        }

        // Clean objects
        destroy_stack(tmp);
        destroy_queue(hand_a);
        destroy_queue(hand_b);

        //Recommencer
        printf("Souhaitez-vous faire une nouvelle partie (oui:1 / non:0) ");
        scanf("%i",&continuer_int);
    }
    free(cartes);
}
