/*

Auteur: 
Description:

*/

#include <stdlib.h>
#include <stdio.h>

//À compléter

int main(int argc, char **argv){
  int tab[] = {1,2,3,4};
  printmap(tab,4,&doubler); //affiche: 2 4 6 8
  printmap(tab,4,&inc); //affiche: 3 5 7 9
  return EXIT_SUCCESS;
}
