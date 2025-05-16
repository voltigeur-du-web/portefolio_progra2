#include "queue.h"
#include "listes_chainees.h"
#include <string.h>
#define N_BITS 3

//PRE: Un nombre entier non signé entre 0 et 7 inclus
//POST: Une chaine de caractère de 3 bits (+ bit nul) qui est la traduction binaire du nombre entier 
char* convert_uint_to_charbin(unsigned int n) {
    if (n > 7) { // Vérifie si le nombre dépasse 3 bits
        printf("Nombre à plus de 3 bits\n");
        exit(1);
    }

    char* bits = (char*)malloc((N_BITS + 1) * sizeof(char));
    if (bits == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }

    for (int i = 0; i < N_BITS; i++) {
        bits[N_BITS - 1 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    bits[N_BITS] = '\0'; // Termine la chaîne de caractères

    return bits;
}

//PRE: Une chaine de 3 caractères binaires terminée par un (4e) caractère nul
//POST: Un nombre entier non signé entre 0 et 7 inclus qui est la traduction de la chaine de caractères
unsigned int convert_charbin_to_uint(char* binary_string) {
    // Vérifie que la chaîne a exactement 3 caractères
    char k=(char) binary_string[0];
    int size=0;
    unsigned int number = 0;
    while (k != '\0' && size <= N_BITS ){
        //printf("k is: %c \n",k);
        if (k != '0' && k != '1'){
            printf("caractères non binaire apparaissent dans la chaine\n");
            exit(1);
        } 
        else if (k == '1') {
            number |= (1 << (N_BITS - 1 - size)); // Met le bit correspondant à 1
        } 
        size++;
        k=binary_string[size];
    }
    if (size != 3){
        printf("Il n'y a pas 3 caractères binaires\n");    
        exit(1);
    }
    return number;
}

//PRE: Une queue (pointer) initialisée
//POST: Montre la traduction des valeurs entières de la queue en binaire sur 3 bits.
void display_queue_binary(Queue_t uint){  
    Queue_t copy = copy_queue(uint);
    printf("Size of queue: %i\n",size_queue(copy));
    char* bin_txt;
    while(size_queue(copy)>0){
        int val=dequeue(copy);
        bin_txt=convert_uint_to_charbin((unsigned int)val);
        printf("%s\n",bin_txt);
    }
    destroy_queue(copy);
}

//PRE: 
    //iv, suite de chiffres binaires initialisee (!=NULL) et de taille 3
    //plaintext, suite de chiffres binaires initialisee (!=NULL) de taille multiple de 3
//POST: renvoie une suite de chiffres binaires dont la taille vaut taille(plaintext). Elle correspond au chiffrement de la
//suite de chiffres binaires plaintext avec pour vecteur d’initialisation iv. plaintext et iv n’ont pas ete modifies
Queue_t chiffrer(Queue_t iv, Queue_t plaintext){
    Queue_t message_chiffre = new_queue();
    Queue_t plaintext2 = copy_queue(plaintext);
    Queue_t iv2 = copy_queue(iv);
    int prev_cb = dequeue(iv2);
    int counter=0;
    int m;
    while(size_queue(plaintext2)>0){
        m = dequeue(plaintext2);
        prev_cb = prev_cb ^ m;
        //printf("%s est transformé en %s\n",convert_uint_to_charbin(m), convert_uint_to_charbin(prev_cb));
        enqueue(message_chiffre,prev_cb);
        if(prev_cb>7){
            printf("Erreur: code bloc a une valeur excédent bin:111 (dec:7)\n");
            exit(1);
        }
    }
    destroy_queue(iv2);
    destroy_queue(plaintext2);
    return message_chiffre;
}

int main() {
    //Initiate vectors
    Queue_t iv = new_queue();
    Queue_t plaintext = new_queue();
    
    int message_size=0;
    char block[4];
    while(message_size<1){
        printf("Veuillez définir le nombre de block de 3 bits dans le message: ");
        scanf("%i",&message_size);
    }

    printf("Veuillez définir le vecteur d'initialisation (3 bits): ");
    scanf("%s",block);
    enqueue(iv,convert_charbin_to_uint(block));

    int counter=1;
    while(counter<=message_size){
        printf("Bits du bloc %i: ",counter);
        scanf("%s",block);
        enqueue(plaintext,convert_charbin_to_uint(block));
        counter++;
    }

    //Chiffrement du message
    Queue_t msg_chiffre = chiffrer(iv, plaintext);

    //Display valeurs
    printf("Vecteur d'initialisation\n");
    display_queue_binary(iv);
    printf("Message en decimal\n");
    display_queue_binary(plaintext);
    printf("Message chiffré en binaire\n");
    display_queue_binary(msg_chiffre);

    //Free memory
    destroy_queue(iv);
    destroy_queue(plaintext);
}