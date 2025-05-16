/*

Auteur: Cédric Libert
Description:

*/

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(int argc, char **argv){
  Queue_t q = new_queue();
  printf("Taille:%i\n",size(q));
  enqueue(q,3);
  printf("Taille:%i\n",size(q));
  enqueue(q,5);
  printf("Taille:%i\n",size(q));
  enqueue(q,1);
  printf("Taille:%i\n",size(q));
  int a = dequeue(q);
  printf("Élement enlevé:%i\n",a);
  int b = dequeue(q);
  printf("Élement enlevé:%i\n",b);
  printf("Taille:%i\n",size(q));
  enqueue(q,6);
  int c = dequeue(q);
  printf("Élement enlevé:%i\n",c);
  return EXIT_SUCCESS;
}
