/*

Auteur: Cédric Libert
Description: embryon d'exemple pour la lecture de fichiers

*/

#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE 1000

int main(int argc, char **argv){
	FILE* nana; 									//Déclaration de la variable qui contient le descripteur de fichier (fd)
	nana = fopen("nana.txt","r"); //Ouverture du fichier en mode lecture "r", récupération du fd
	if(nana!=NULL){               //Vérification que l'ouverture s'est bien passée
	  char ligne[1000];           //Ce tableau de 1000 cases pourra contenir à chaque fois au max les MAX_LINE premiers caractères de la ligne lue)
		while(fgets(ligne,MAX_LINE,nana)){ //Lecture d'une ligne. S'arrête si ça indique la fin du fichier ou si ça se passe mal.
			printf("%s",ligne);
		}
		fclose(nana);								//Fermeture du fichier
	}
  return EXIT_SUCCESS;
}
