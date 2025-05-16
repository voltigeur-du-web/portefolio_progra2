#include "pile.h"
#include <string.h>
#include <stdbool.h>
#define MAX_STRING 100

//PRE: Une chaine de caractère
//POST: Un entier naturel qui est la longueur de la chaine de caractère
int taille_str(char* str){
    int i=0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

//PRE: Deux chaines de caractères
//POST: Retourne un booleen:
    // true si les deux chaines de caractères sont identiques
    // false sinon
bool strings_equal(char* str1, char* str2){
    bool strings_are_equal=false;
    if(taille_str(str1)!=taille_str(str2)){
        return strings_are_equal;
    }

    strings_are_equal=true;
    for(int i=0;i<taille_str(str1) && strings_are_equal;i++){
        strings_are_equal=str1[i]==str2[i];
    }
    return strings_are_equal;
}

//PRE: Un stack pointer (struct Stack_t) et un string contenant soit un nombre entier, soit un opérateur (+, -, *, /, =, ++, **)
//POST: 
    // Si un des opérateurs suivant (+, -, *, /) est entré, le résultat entier de l'opération (+, -, *, /) des deux derniers entiers est ajouté à la pile
    // Si l'opérateur entré est '=', alors le programme s'arrète et le résultat en haut de la pile est retourné
    // Si l'opérateur '**' est entré, alors le produit entier de tous les éléments de la pile est retourné
    // Si l'opérateur '++' est entré, alors la somme entière de tous les éléments de la pile est retourné

void calculate(Stack_t stack, char* opcmd) {
    int b, a, op;
    int len_operator=0;
    char operator;
    while(opcmd[len_operator] != '\0'){
        len_operator++;
    }
    if(len_operator==1){
        operator = opcmd[0];
    }
    else if(len_operator==2){
        char* prod_char="**";
        char* sum_char="++";
        if(strings_equal(opcmd,prod_char)){
            operator='p';
        }
        else if(strings_equal(opcmd,sum_char)){
            operator='s';
        }
        else{
            fprintf(stderr, "Opérateur non supporté\n");
            exit(1);
        }
    }
    else{
        fprintf(stderr, "Opérateur non supporté\n");
        exit(1);
    }
    switch (operator) {
        case '+':
            b = remove_from_stack(stack);
            a = remove_from_stack(stack);
            op = a + b;
            break;
        case '-':
            b = remove_from_stack(stack);
            a = remove_from_stack(stack);
            op = a - b;
            break;
        case '*':
            b = remove_from_stack(stack);
            a = remove_from_stack(stack);
            op = a * b;
            break;
        case '/':
            b = remove_from_stack(stack);
            if (b == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            a = remove_from_stack(stack);
            op = a / b;
            break;
        case '=':
            printf("Résultat: %d\n", remove_from_stack(stack));
            destroy_stack(stack);
            exit(0);
        case 's':
            int sum=0;
            while(size_stack(stack)>0){
                a=remove_from_stack(stack);
                sum+=a;
            }
            printf("Résultat: %d\n", sum);
            destroy_stack(stack);
            exit(0);
        case 'p':
            int product=1;
            while(size_stack(stack)>0){
                a=remove_from_stack(stack);
                product*=a;
            }
            printf("Résultat: %d\n", product);
            destroy_stack(stack);
            exit(0);
        default:
            fprintf(stderr, "Opérateur non supporté\n");
            destroy_stack(stack);
            exit(1);
    }
    add_to_stack(stack, a);
    add_to_stack(stack, b);
    add_to_stack(stack, op);
}

//PRE: Une chaine de caractere
//POST: Détermine true/false si ce string est composé uniquement de digits.
bool is_digit_string(char* str) {
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

//PRE: Un stack pointer (struct Stack_t) est entré et la pile correspondante est initialisée.
//POST: Si un entier est entré, alors ce nombre est ajouté à la pile. 
    // Sinon, un calcul se fait sur la pile avec l'opérateur (un string) entré par l'utilisateur.
void enter_opcmd(Stack_t stack){
    char opcmd[MAX_STRING];
    printf("Entrez un nombre ou un opérateur (+, -, *, /, =, ++, **): ");
    scanf("%s",opcmd);
    if(is_digit_string(opcmd)){
        add_to_stack(stack,atoi(opcmd));
    }
    else{
        calculate(stack, opcmd);
    }
}

int main() {
    Stack_t stack = new_stack();
    char input[100];

    while (true) {
        enter_opcmd(stack);
    }

    destroy_stack(stack);
    return 0;
}
