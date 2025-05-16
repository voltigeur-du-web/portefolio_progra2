#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 3
#define INITIAL_BUFFER_SIZE 100

void read_text_file(const char *filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    char* line = malloc(INITIAL_BUFFER_SIZE*sizeof(char));
    if (line == NULL) {
        fprintf(stderr,"Erreur lors de l'allocation en mémoire de line\n");
        exit(1);
    }
    int count = 0;
    int buffer_size=INITIAL_BUFFER_SIZE;
    int current_position = 0;
    // Lire ligne par ligne jusqu'à arriver à MAX_LINE
    while (count < MAX_LINE) {
        // Lire un morceau de la ligne
        if (fgets(line + current_position, buffer_size - current_position, file) == NULL) {
            break; // Arrêt si erreur
        }
        //taille actuel de la string
        size_t length = strlen(line);
        // \n en bout de string ? Oui
        if (length > 0 && line[length - 1] == '\n') {
            printf("%s\n", line); 
            count++;
            //Réinitialiser au valeur par défaut la taille du line buffer + position courante
            current_position = 0; 
            buffer_size = INITIAL_BUFFER_SIZE; 
            line = realloc(line, buffer_size * sizeof(char)); 
        } 
        //Non
        else {
            // Agrandir line buffer + adapter position tête de lecture
            current_position = length;
            buffer_size *= 2;
            line = realloc(line, buffer_size * sizeof(char));
        }
    }
    free(line);
    fclose(file);
}

int main(){
    char filename[]="/home/pam-gaming/dev/unamur/progra2/cours5/fichiers/Nana.txt";
    read_text_file(filename);
    return 0;
}