#include <stdlib.h>
#include <stdio.h>

int define_size(void) {
    int tailleMessage = 0;
    printf("Veuillez indiquer la taille du message: ");
    scanf("%i", &tailleMessage);
    if (tailleMessage <= 0) {
        printf("La taille du message doit être non-nulle et positive\n");
        exit(1);
    }
    return tailleMessage;
}

int* create_message(int tailleMessage) {
    int i = 1;
    int* message = (int *)malloc(tailleMessage * sizeof(int));
    while (i <= tailleMessage) {
        printf("Nombre %i : ", i);
        scanf("%i", &message[i - 1]);
        i++;
    }
    return message;
}

void display(int message[], int tailleMessage) {
    printf("[");
    for (int i = 0; i < tailleMessage; i++) {
        if (i > 0) {
            printf(",");
        }
        printf("%i", message[i]);
    }
    printf("]\n");
}

int compresser(int message[], int tailleMessage) {
    int previous_val = message[0];
    int current_val = 0;
    int distinct = 1;
    int i = 1;

    // Compter nombre de séries
    if (tailleMessage > 1) {
        while (i < tailleMessage) {
            current_val = message[i];
            if (previous_val != current_val) {
                distinct++;
            }
            previous_val = current_val;
            i++;
        }
    }

    // Malloc tableau compressé
    int* compressed = (int *)malloc(2 * distinct * sizeof(int));

    // Remplir tableau compressé
    int j = 0;
    previous_val = message[0]; 
    int counter = 0;
    for (i = 0; i < tailleMessage; i++) {
        current_val = message[i]; 
        if (i == 0 || previous_val == current_val) {
            counter++;
        } else {
            compressed[j] = counter;
            j++;
            compressed[j] = previous_val;
            j++;
            counter = 1;
        }
        previous_val = message[i];
    }

    // Ajouter la dernière série
    compressed[j] = counter;
    j++;
    compressed[j] = previous_val;

    display(compressed, 2 * distinct);
    free(compressed); // Libérer la mémoire allouée
    return 2 * distinct;
}

int main() {
    int tailleMessage = define_size();
    int* message = create_message(tailleMessage);
    int sizer = compresser(message, tailleMessage);
    free(message); // Libérer la mémoire allouée pour le message
    return 0;
}
