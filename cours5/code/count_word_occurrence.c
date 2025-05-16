#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Dict.h"

#define MAX_LINE 5900
#define INITIAL_BUFFER_SIZE 100
#define MAX_CHAR_SIZE 50

char* clean_string(const char* word) {
    //Ponctuation à enlever
    const char* to_remove = "!\"#$%&()*+,./:;<=>?@[\\]^_`{|}~";
    //Ponctuation à remplacer par espace
    const char* to_blank = "-'";
    //Compter la longueur de la nouvelle chaine de caractère
    int length = 0;
    const char* ptr = word;
    while (*ptr != '\0') {
        if (strchr(to_blank, *ptr) != NULL || strchr(to_remove, *ptr) == NULL) {
            length++;
        }
        ptr++;
    }
    // Allouer de la mémoire pour la nouvelle chaîne
    char* new_word = (char*)malloc((length + 1) * sizeof(char));
    if (new_word == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour new_word\n");
        exit(1);
    }
    char* dst = new_word;
    while (*word != '\0') {
        if (strchr(to_blank, *word) != NULL) {
            *dst++ = ' ';
        } else if (strchr(to_remove, *word) == NULL) {
            *dst++ = tolower(*word);
        }
        word++;
    }
    *dst = '\0'; // Terminer la chaîne avec un caractère nul
    return new_word;
}

void get_word_to_dict(Dico_t dico, char* line) {
    char* token = strtok(line, " ");
    //convert_to_lowercase(token);
    bool added;
    int value;
    while (token != NULL) {
        printf("%s\n",token);
        added = add_to_dict(dico, token, 1);
        if (!added) {
            value = search_in_dict(dico, token);
            value++;
            modify_in_dict(dico, token, value); // Incrémente la valeur
        }
        token = strtok(NULL, " ");
        //convert_to_lowercase(token);
    }
}

void read_text_file(const char *filename, Dico_t dico) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    char* line = (char*)malloc(INITIAL_BUFFER_SIZE * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation en mémoire de line\n");
        fclose(file);
        exit(1);
    }
    int count = 0;
    int buffer_size = INITIAL_BUFFER_SIZE;
    int current_position = 0;
    // Lire ligne par ligne jusqu'à arriver à MAX_LINE
    while (count < MAX_LINE) {
        // Lire un morceau de la ligne
        if (fgets(line + current_position, buffer_size - current_position, file) == NULL) {
            break; // Arrêt si erreur
        }
        // Taille actuelle de la string
        size_t length = strlen(line);
        // \n en bout de string ? Oui
        if (length > 0 && line[length - 1] == '\n') {
            printf("Raw:\n%s\n", line);
            char* cleaned_line = clean_string(line);
            if (cleaned_line == NULL) {
                fprintf(stderr, "Erreur lors de la suppression de la ponctuation\n");
                free(line);
                fclose(file);
                exit(1);
            }
            printf("Cleaned:\n%s\n", cleaned_line);
            get_word_to_dict(dico, cleaned_line);
            free(cleaned_line);
            // Libérer la mémoire allouée pour cleaned_line
            count++;
            // Réinitialiser à la valeur par défaut la taille du line buffer + position courante
            current_position = 0;
            buffer_size = INITIAL_BUFFER_SIZE;
            line = (char*)realloc(line, buffer_size * sizeof(char));
            if (line == NULL) {
                fprintf(stderr, "Erreur lors de la réallocation en mémoire de line\n");
                fclose(file);
                exit(1);
            }
        } else {
            // Agrandir line buffer + adapter position tête de lecture
            current_position = length;
            buffer_size *= 2;
            line = (char*)realloc(line, buffer_size * sizeof(char));
            if (line == NULL) {
                fprintf(stderr, "Erreur lors de la réallocation en mémoire de line\n");
                fclose(file);
                exit(1);
            }
        }
    }
    free(line);
    fclose(file);
}

//PRE: Auncune
//POST: Vide le tampon d'entrée rempli par scanf  (necessaire pour utiliser fgets)
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


//PRE: Un dictionnaire initialisé et non-vide & une entrée utilisateur de nom  de max 50 caractères 
//POST: Des fréquences de valeurs retournées dans la console.
void menu(Dico_t dico){
    bool again=true;
    char key[MAX_CHAR_SIZE];
    int freq;
    while(again){
        printf("\nQuel mot souhaitez-vous connaître la fréquence d'apparition dans Nana:\n - utilisez seulement des caractères ASCII minuscules\n - tapez EXIT pour sortir du programme\n");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key,"\n")]='\0';
        if(strcmp("EXIT",key)==0) again=false;
        bool found = exist_in_dict(dico,key);
        if(again && found){
            freq = search_in_dict(dico,key);
            printf("La fréquence du mot `%s` est %i\n",key,freq);
        }
        else if (again){
            printf("Le mot `%s` na pas été trouvé\n",key);
        }
    }
}

int main() {
    Dico_t dico = create_dict();
    if (dico == NULL) {
        fprintf(stderr, "Erreur lors de la création du dictionnaire\n");
        return 1;
    }
    char filename[] = "/home/pam-gaming/dev/unamur/progra2/cours5/fichiers/Nana_cleaned.txt";
    read_text_file(filename, dico);

    menu(dico);

    destroy_dict(dico); // Libérer la mémoire allouée pour le dictionnaire
    return 0;
}
