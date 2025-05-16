/*
Auteur: Cédric Libert
Description: définition d'un coffre fort, qu'on peut déverrouiller à l'aide d'un mot de passe, de taille fixe
auquel on peut ajouter des éléments ou les retirer.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE_PASSWORD 100

struct Coffre {
  int nb_elements; //nombre d'éléments contenus dans le coffre
  int taille; //taille du coffre
  int* elements; //éléments contenus dans le coffre
  bool locked; //indique si le coffre est verrouilé ou non
  char* password;//mot de passe pour déverouiller le coffre
};
typedef struct Coffre* Coffre_t;

//PRE: /
//POST: initialise un coffre de taille taille (ou 0 si taille<0)
//ayant comme mot de passe les 100 premiers caractères de password (maximum)
//et étant verrouillé
Coffre_t new_coffre(int taille, const char* password){
  Coffre_t coffre = malloc(sizeof(*coffre));
  if(taille<0){
    taille=0;
  }
  coffre->elements = malloc(taille*sizeof(int));
  coffre->taille = taille;
  coffre->nb_elements = 0;
  coffre->locked = true;
  coffre->password = malloc(MAX_SIZE_PASSWORD*sizeof(char));
  if(strlen(password)>MAX_SIZE_PASSWORD){
    strncpy(coffre->password,password,MAX_SIZE_PASSWORD);
  }
  else{
    strncpy(coffre->password,password,strlen(password));
  }
  return coffre;
}
//PRE: coffre est initialisé, password aussi
//POST: si le password correspond au mot de passe de verouillage du coffre
//le coffre est déverrouillé. Renvoie le statut de verrouillage du coffre.
bool unlock(Coffre_t coffre,char* password){
  if(strcmp(coffre->password,password)==0){
    coffre->locked = false;
  }
  return coffre->locked;
}
//PRE: coffre est initialisé
//POST: verrouille le coffre
void lock(Coffre_t coffre){
  coffre->locked = true;
}


void decaler_tab(int* tab, int taille, int decalage){
  if(decalage>0){
    int i;
    for(i=0;i+decalage<taille;i++){
      tab[i]=tab[i+decalage];
    }
  }
}

//PRE: coffre est initialisé
//POST: si 0<=nb<=coffre->nb_elements et si le coffre est déverrouillé,
// renvoie les nb premiers éléments qui ont été mis dans coffre, dans l'ordre où ils y ont été mis,
//      et les enlèves du coffre
//      si nb> coffre->nb_elements, renvoie tous les éléments du coffre, dans l'ordre où ils y ont été mis,
//      et les enlève du coffre
//      si nb<0 ou si le coffre est verrouillé, ne modifie rien et renvoie NULL 
int* get_elements(Coffre_t coffre,int nb){
  int* elements = NULL;
  if(nb<0 || coffre->locked){
    nb = 0;
  } 
  else {
      if(nb>coffre->nb_elements){
        nb = coffre->nb_elements;
      }
      elements=malloc(nb*sizeof(*elements));
      int i;
      for(i=0;i<coffre->taille; i++){ 
        if(i<nb){
          elements[i]=coffre->elements[i]; //COPIE
        }
      }
      decaler_tab(coffre->elements,coffre->taille,nb);//DECALAGE
      coffre->nb_elements-=nb;
  }
  return elements;
}


//PRE: coffre initialisé
//POST: si le coffre est verrouilé ou déjà plein, renvoie false et ne modifie rien
//      sinon, ajoute element dans le coffre et renvoie true
bool insert_element(Coffre_t coffre, int element){
  if(coffre->locked||coffre->nb_elements==coffre->taille){
    return false;
  }
  else{
    coffre->elements[coffre->nb_elements]=element;
    coffre->nb_elements++;
    return true;
  }
}
//PRE: coffre initialisé
//POST: si le coffre n'est pas verrouillé, affiche son contenu et renvoie true. Sinon, affiche "coffre verrouillé" et renvoie false.
bool print_elements(Coffre_t coffre){
  if(!coffre->locked){
    int i;
    printf("[ ");
    for(i=0;i<coffre->nb_elements;i++){
      printf("%i ",coffre->elements[i]);
    }
    printf("]\n");
  }
  else{
    printf("Coffre verrouillé.\n");
  }
  return !coffre->locked;
}
void destroy_coffre(Coffre_t coffre){
  free(coffre->elements);
  free(coffre);
}


int main(int argc, char **argv){
  Coffre_t c = new_coffre(4,"ekilnha93!");
  print_elements(c); //"coffre verrouillé"
  unlock(c,"coucou");
  print_elements(c); //"coffre verrouillé"
  unlock(c,"ekilnha93!");
  print_elements(c);//"[ ]"
  insert_element(c,3);
  print_elements(c); //"[ 3 ]"
  lock(c);
  print_elements(c); //"Coffre verrouillé"
  int* elem1 =  get_elements(c,1);
  printf("%p\n",elem1); //"NULL"
  unlock(c,"ekilnha93!");
  elem1 =  get_elements(c,1);
  printf("%i\n",elem1[0]); // "3"
  print_elements(c);//"[ ]"
  insert_element(c,4);
  insert_element(c,8);
  insert_element(c,2);
  insert_element(c,9);
  insert_element(c,10);
  print_elements(c);//"[ 4 8 2 9 ]"
  int* elem2 =  get_elements(c,2);
  printf("%i %i\n",elem2[0],elem2[1]); // "4 8"
  print_elements(c);//"[ 2 9 ]"
  destroy_coffre(c);
  free(elem1);
  free(elem2);
  return EXIT_SUCCESS;
}
