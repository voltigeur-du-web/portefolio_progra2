#include <unistd.h>
#include <time.h>
#include "pile.h"
#include "queue.h"
#include "priority_queue_struct.h"

#define MAX_FIGHTERS 50
#define MAX_PV 20
#define MAX_SPEED 20
#define MAX_X 5
#define MAX_Y 5

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

struct Node_PQ{
    int priority;
    int id;
};


struct Stats{
    int id;
    char name[50];
    int pv;
    int speed;
    int power;
    int x;
    int y;
} Stats;
typedef struct Stats* Stats_t;

struct PQ {
    Node_PQ_t players;
    int size;
    int capacity;
    int (*leq)(int, int);
};

//PRE: Nom de fichier CSV comprenant les stats de 50 personnages (dans le même dossier courant que le programme C) & 
    // une structure Stats_t est initialisée &
    // La constate MAX_FIGHTERS est identique au nombre de personnages du fichiers CSV 
//POST: Retourne un pointer Stats_t faisant référence à une structure reprenant toutes les stats de fighters compris dans le fichiers CSV
Stats_t readCSV(const char *filename, Stats_t players) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    char line[100];
    int count = 0;
    // Lire la première ligne (en-tête) et l'ignorer
    fgets(line, sizeof(line), file);
    // Lire les lignes suivantes
    while (fgets(line, sizeof(line), file) && count < MAX_FIGHTERS) {
        // Supprimer le caractère de nouvelle ligne
        line[strcspn(line, "\n")] = 0;
        //Lecture id
        char *token = strtok(line, ",");
        if (token != NULL) {
            players[count].id = atoi(token);
        }
        //Lecture nom
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(players[count].name, token, sizeof(players[count].name));
        }
        //Lecture pv
        token = strtok(NULL, ",");
        if (token != NULL) {
            players[count].pv = atoi(token);
        }
        //Lecture speed
        token = strtok(NULL, ",");
        if (token != NULL) {
            players[count].speed = atoi(token);
        }
        //Lecture power
        token = strtok(NULL, ",");
        if (token != NULL) {
            players[count].power = atoi(token);
        }
        count++;
    }
    fclose(file);
    return players;
}

//PRE: -
//POST: Fonction d'ordre pour les fighters (vitesse élevée -> prioritaire)
int geq(int a, int b){
    return b-a;
}

//PRE: -
//POST: Fonction d'ordre pour les fighters (pv bas -> prioritaire)
int leq(int a, int b){
    return a-b;
}

//PRE: Un pointeur d'une structure de l'ensemble des fighters possible avec leur stat, l'utilisateur entre un nombre entre 1 et 50
//POST: Retourne un pointeur d'une structure de l'ensemble des fighters sélectionnés (avec leur stats / position toujours nulles)
void init_fight(Stats_t all_fighters,Stack_t available_fighters, PQ_t picked_fighters, int n_fighters, bool random_pickup){
    //Initialisé des stacks et picked_fighters
    Stack_t tmp = new_stack();

    //Random selection of the fighters
    int skip=0;
    int picked;
    int not_taken;
    int i,j;
    int counter=picked_fighters->size;
    srand(time(NULL));
    if(size_stack(available_fighters)>0){
        for(i=counter;i<counter+n_fighters;i++){
            //Choisir un fighter ID sur ceux présents
            if(random_pickup){
                skip=rand() % size_stack(available_fighters);
            }
            
            //Passer les fighters non sélectionné et les mettre dans une défausse temporaire
            for(j=0;j<skip;j++){ //if skip = 0 then no skip, if skip = 9
                not_taken = remove_from_stack(available_fighters);
                add_to_stack(tmp,not_taken);
            }
            picked = remove_from_stack(available_fighters);
            add_to_pq(picked_fighters,all_fighters[picked].speed,all_fighters[picked].id); 
            //Remettre les fighters non sélectionné dans la pioche
            for(j=0;j<skip;j++){
                not_taken = remove_from_stack(tmp);
                add_to_stack(available_fighters,not_taken);
            }
        }
    }
    else{
        printf("Pas de fighter disponible\n");
    }
    
    destroy_stack(tmp);
}

void init_fighters_map(int fighters_map[MAX_X+2][MAX_Y+2]){
    //Créer une bordure le long de la carte
    int y;
    for(y=0;y<MAX_Y+2;y++){
        fighters_map[0][y]=999;
        fighters_map[MAX_X+1][y]=999;
    }
    int x;
    for (x=0; x<MAX_X+2; x++) {
        fighters_map[x][0]=999;
        fighters_map[x][MAX_Y + 1]=999;
    }
    //Initialiser les emplacements libre
    for(x=1;x<=MAX_X;x++){
        for(y=1;y<=MAX_Y;y++){
            fighters_map[x][y]=-1;
        }
    }
}
//PRE: n_fighters est un entier représentant le nombre de fighters && picked_fighters est un pointeur d'une structure de l'ensemble des fighters sélectionnés (avec leur stats / position toujours nulles)
//POST: Retourne un pointeur d'une structure de l'ensemble des fighters sélectionnés avec leur stats et positions
    // Tous les fighters ont des positions différentes.
void place_fighters(PQ_t picked_fighters, Stats_t all_fighters,  int n_fighters_to_place, int fighters_map[MAX_X+2][MAX_Y+2]){
    srand(time(NULL));
    int try_x;
    int try_y;
    int i;
    int j;
    int same_position;
    int n_present_fighters=0;
    for(i=picked_fighters->size-1;i>=picked_fighters->size-n_fighters_to_place;i--){
        int id=picked_fighters->players[i].id;
        //S'assurer qu'aucun joueur ne soit à la même position
        do{
            same_position=0;
            try_x=(rand() % MAX_X)+1;
            try_y=(rand() % MAX_Y)+1;
            if(fighters_map[try_x][try_y]>0) same_position++;
        } while(same_position>0);
        all_fighters[id].x=try_x;
        all_fighters[id].y=try_y;
        fighters_map[try_x][try_y]=id;
    }
}

void display_fighter_stats(struct Stats fighter){    
    printf("Nom: %24s | PV: %2i | Speed: %2i | Power: %2i | X: %2i | Y: %2i\n",
        fighter.name,
        fighter.pv,
        fighter.speed,
        fighter.power,
        fighter.x,
        fighter.y);
}
//PRE
//POST
void display_fighters(PQ_t picked_fighters, Stats_t all_fighters){    
    for(int i=0;i<picked_fighters->size;i++){
        int id=picked_fighters->players[i].id;
    printf("Nom: %24s | PV: %2i | Speed: %2i | Power: %2i | X: %2i | Y: %2i\n",
        all_fighters[id].name,
        all_fighters[id].pv,
        all_fighters[id].speed,
        all_fighters[id].power,
        all_fighters[id].x,
        all_fighters[id].y);
    }
}

void move_fighters(PQ_t picked_fighters, Stats_t all_fighters, int fighters_map[MAX_X+2][MAX_Y+2]){
    if(!is_pq_empty(picked_fighters)){
        int i,j,k;
        int diff_x,diff_y;
        int n_free_pos;
        int n_move_pov;
        int counter;
        for(i=0;i<picked_fighters->size;i++){
            int id=picked_fighters->players[i].id;
            n_free_pos=0;
            for(j=-1;j<=1;j++){
                for(k=-1;k<=1;k++){
                    if(!(j==0 & k==0) && (fighters_map[all_fighters[id].x+j][all_fighters[id].y+k]<0)){
                        n_free_pos++;
                    } 
                }   
            }
            //Move if any free spot (else no move)
            if(n_free_pos>0){
                n_move_pov = rand() % n_free_pos;
                counter=0;
                for(j=-1;j<=1 && counter<=n_move_pov;j++){
                    for(k=-1;k<=1 && counter<=n_move_pov;k++){
                        if(!(j==0 & k==0) && (fighters_map[all_fighters[id].x+j][all_fighters[id].y+k]<0)){
                            diff_x=j;
                            diff_y=k;
                            counter++;
                        }
                    }
                }
                fighters_map[all_fighters[id].x+diff_x][all_fighters[id].y+diff_y]=id;
                fighters_map[all_fighters[id].x][all_fighters[id].y]=-1;
                all_fighters[id].x=all_fighters[id].x+diff_x;
                all_fighters[id].y=all_fighters[id].y+diff_y;
            }
        }
    }
}

int shoot_round(PQ_t picked_fighters, Stats_t all_fighters, int fighters_map[MAX_X+2][MAX_Y+2],Stack_t graveyard){
    //Déclaration et initialisations
    Stack_t shooters_id = new_stack();
    Stack_t woundeds_id = new_stack();
    Stack_t to_skip = new_stack();
    int id_wounded;
    int id_shooter;
    int id_skip;
    
    if(is_pq_empty(picked_fighters)){
        printf("Tous les fighters sont morts\n");
        return 0;
    }
    else if(picked_fighters->size==1){
        printf("Il reste un seul fighter: %s \n",all_fighters[peek_pq(picked_fighters).id].name);
        return 0;
    }

    //Selectionner les tireurs les plus rapides
    int shooting_speed = peek_pq(picked_fighters).priority;
    while(!is_pq_empty(picked_fighters) && peek_pq(picked_fighters).priority==shooting_speed){
        add_to_stack(shooters_id,peek_pq(picked_fighters).id);
        all_fighters[peek_pq(picked_fighters).id].speed=shooting_speed;
        serve_pq(picked_fighters);
    }

    //Ajouter +1 vitesse aux autres tireurs
    if(!is_pq_empty(picked_fighters)){
        for(int i=0;i<picked_fighters->size;i++){
            picked_fighters->players[i].priority++;
            all_fighters[picked_fighters->players[i].id].speed++;
        }
    }

    int n_shooters=size_stack(shooters_id);
    printf("Il y a %i tireurs: \n", n_shooters);

    while(size_stack(shooters_id)>0){
        //Rajouter les tireurs à la PQ_speed
        id_shooter=remove_from_stack(shooters_id);
        add_to_pq(picked_fighters,all_fighters[id_shooter].speed,id_shooter);
    
        //Résolution des tirs sur les PV
        int shoot_chance=rand()%2;
        int try_x=all_fighters[id_shooter].x;
        int try_y=all_fighters[id_shooter].y;
        if(shoot_chance==0){
            while(try_x==all_fighters[id_shooter].x && try_y==all_fighters[id_shooter].y){
                try_x=(rand() % MAX_X)+1;
                try_y=(rand() % MAX_Y)+1;
            }
            if(fighters_map[try_x][try_y]>=0 && fighters_map[try_x][try_y]<MAX_FIGHTERS){
                id_wounded=fighters_map[try_x][try_y];
                printf(" -%s tir et touche %s qui perd %i pv \n",all_fighters[id_shooter].name,all_fighters[id_wounded].name,all_fighters[id_shooter].power);
                all_fighters[id_wounded].pv=all_fighters[id_wounded].pv-all_fighters[id_shooter].power;
                //Ajout à la liste des blessés et sortie de la map
                if(all_fighters[id_wounded].pv<=0){
                    add_to_stack(woundeds_id,id_wounded);
                    add_to_stack(graveyard,id_wounded);
                    fighters_map[try_x][try_y]=-1;
                    

                }  
            }
            else printf(" -%s manque son tir\n",all_fighters[id_shooter].name);
        }
        else printf(" -%s n'a pas pu tiré\n",all_fighters[id_shooter].name);
    }

    //Gestion des blessés
    if(size_stack(woundeds_id)>0){
        printf("Les blessés à ce round sont:\n");
    }
    else{
        printf("Pas de blessés à ce round\n");
    }
    while(size_stack(woundeds_id)>0){
        id_wounded=remove_from_stack(woundeds_id);
        display_fighter_stats(all_fighters[id_wounded]);

        //Les blessés sortent de la PQ_speed et sont ajoutés au graveyard
        bool found=false;
        while(!found){
            if(id_wounded==peek_pq(picked_fighters).id) found=true;
            else add_to_stack(to_skip,peek_pq(picked_fighters).id);
            serve_pq(picked_fighters);
        }
        while(size_stack(to_skip)>0){
            id_skip=remove_from_stack(to_skip);
            add_to_pq(picked_fighters,all_fighters[id_skip].speed,id_skip);
        }
    }
    printf("Fighters restants: %i\n",picked_fighters->size);
    display_fighters(picked_fighters,all_fighters);

    destroy_stack(to_skip);
    destroy_stack(woundeds_id);
    destroy_stack(shooters_id);
    
    return 0;
}

int get_mean_pv(PQ_t picked_fighters, Stats_t all_fighters){
    if(is_pq_empty(picked_fighters)) return 1; 
    int sum_pv=0;
    for(int i=0;i<picked_fighters->size;i++){
       sum_pv=sum_pv+all_fighters[picked_fighters->players[i].id].pv;
    }
    if(sum_pv/picked_fighters->size==0) return 1;
    else return sum_pv/picked_fighters->size;
}

void add_new_fighter(Stats_t all_fighters, Stack_t available_fighters, PQ_t picked_fighters, int n_fighters_to_add, int fighters_map[MAX_X+2][MAX_Y+2], bool random_pickup){
    //add fighter 1 every 20 round
    int do_add_fighters = rand() % 20;
    if(size_stack(available_fighters)>0 && do_add_fighters==0){   
        int mean_pv=get_mean_pv(picked_fighters,all_fighters);
        init_fight(all_fighters,available_fighters,picked_fighters, n_fighters_to_add, random_pickup);
        if(random_pickup) printf("Un nouveau fighter apparait !\n");
        else printf("Un fighter blessé réapparait dans le jeu !\n");
        picked_fighters->players[picked_fighters->size-1].priority=mean_pv;
        all_fighters[picked_fighters->players[picked_fighters->size-1].id].pv=mean_pv;
        place_fighters(picked_fighters, all_fighters, n_fighters_to_add, fighters_map);
        display_fighter_stats(all_fighters[picked_fighters->players[picked_fighters->size-1].id]);
    }
}

int main(){
    //Déclaration objets pour tous les fighters possibles
    Stats_t all_fighters = malloc(MAX_FIGHTERS*sizeof(Stats));
    all_fighters = readCSV("fighters_tir.csv", all_fighters);
    int fighters_map[MAX_X+2][MAX_Y+2];
    init_fighters_map(fighters_map);
    Stack_t available_fighters = new_stack();
    Stack_t graveyard = new_stack();
    int i;
    for(i=0;i<MAX_FIGHTERS;i++){
        add_to_stack(available_fighters,i);
    }

    //Selection du nombre de fighters par l'utilisateur
    int n_fighters=0;
    while(n_fighters<=0 || n_fighters>MAX_FIGHTERS){
        printf("Combien de fighters vont combattre dans la partie:");
        scanf("%i",&n_fighters);
    }

    //Sélection des fighters et placements
    PQ_t picked_fighters = create_pq(geq, MAX_FIGHTERS);
    init_fight(all_fighters,available_fighters,picked_fighters, n_fighters, true);
    place_fighters(picked_fighters,all_fighters,n_fighters, fighters_map);

    //Début combat et présentation des fighters
    printf("Mesdames et Messieurs, voici les fighters \n");
    display_fighters(picked_fighters,all_fighters);
    printf("Fight !!! \n\n");
    sleep(3);

    //Combat (fight, move, add_new_fighter)
    int n_fighters_to_add=1;
    i=1;
    while(!is_pq_empty(picked_fighters) && picked_fighters->size>1){
        //clear_console();
        printf("Round %i \n",i);
        shoot_round(picked_fighters,all_fighters,fighters_map,graveyard);
        move_fighters(picked_fighters, all_fighters, fighters_map);
        add_new_fighter(all_fighters,available_fighters,picked_fighters, n_fighters_to_add, fighters_map,true);
        if(size_stack(graveyard)>0) {
            add_new_fighter(all_fighters,graveyard,picked_fighters, n_fighters_to_add, fighters_map,false);
        }
        sleep(1);
        printf("\n");
        i++;
        if(picked_fighters->size==1) printf("Le gagnant du combat est %s \n",all_fighters[peek_pq(picked_fighters).id].name);
        else if(picked_fighters->size==0) printf("Tous les combatants sont blessés et hors de combat\n");
    }

    //Résultats
    printf("Classement du combat\n");
    int rank=0;
    while(!is_pq_empty(picked_fighters)){
        rank++;
        printf("#%i: %s\n",rank,all_fighters[peek_pq(picked_fighters).id].name);
        serve_pq(picked_fighters);
    }
    while(size_stack(graveyard)>0){
        rank++;
        printf("#%i: %s\n",rank,all_fighters[remove_from_stack(graveyard)].name);
    }

    free(all_fighters);
    destroy_stack(available_fighters);
    destroy_stack(graveyard);
    destroy_pq(picked_fighters);
}