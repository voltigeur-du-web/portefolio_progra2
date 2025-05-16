/*
Auteur: Pierre-Adrien Marchand
Description:
Date: 2025-02-15
*/

#include <stdlib.h>
#include <stdio.h>

//PRE: un entier x
//POST: un entier x multiplié par 2
int doubler(int x){
  return x*2;
} 

//PRE: un entier x
//POST: un entier x + 1
int inc(int x){
  return x+1;
}

void printmap(int* tab, int taille, int (*f)(int)){
  int i;
  for(i=0;i<taille;i++){
    printf("%d ",f(tab[i]));
  }
  printf("\n");
}

int main(int argc, char **argv){
  int tab[] = {1,2,3,4};
  printf("Doubler 1, 2, 3, 4:\n");
  printmap(tab,4,&doubler); //affiche: 2 4 6 8
  printf("Incrémenter 1, 2, 3, 4 de +1:\n");
  printmap(tab,4,&inc); //affiche: 3 5 7 9
  return EXIT_SUCCESS;
}
