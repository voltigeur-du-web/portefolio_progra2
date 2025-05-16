# Séance 3: Utilisation de listes chaînées, files d'attente, piles, files de priorité
- [Séance 3: Utilisation de listes chaînées, files d'attente, piles, files de priorité](#séance-3-utilisation-de-listes-chaînées-files-dattente-piles-files-de-priorité)
  - [1. Des fighters](#1-des-fighters)
    - [Exercice](#exercice)
    - [Résolution](#résolution)
    - [Objectifs rencontrés](#objectifs-rencontrés)
  - [2. Les tirs](#2-les-tirs)
    - [Exercice](#exercice-1)
    - [Résolution](#résolution-1)
    - [Objectifs rencontrés](#objectifs-rencontrés-1)
  - [3. Résurrection et fin du jeu](#3-résurrection-et-fin-du-jeu)
    - [Exercice](#exercice-2)
    - [Résolution](#résolution-2)
    - [Objectifs rencontrés](#objectifs-rencontrés-2)
  - [Auto-Evaluation de la séance](#auto-evaluation-de-la-séance)
    - [Comment générer des fighters ?](#comment-générer-des-fighters-)
    - [Comment positionner et déplacer les fighters dans un espace ?](#comment-positionner-et-déplacer-les-fighters-dans-un-espace-)
    - [Dans le combat de base, comment gérer les fighters K.O. ?](#dans-le-combat-de-base-comment-gérer-les-fighters-ko-)
    - [Dans le combat de base, comment ajouter des fighters en cours de partie ?](#dans-le-combat-de-base-comment-ajouter-des-fighters-en-cours-de-partie-)
    - [Dans le combat par tir, comment gérer les tireurs et les blessés ?](#dans-le-combat-par-tir-comment-gérer-les-tireurs-et-les-blessés-)
    - [Comment gérer les résurrections et le classement finale ?](#comment-gérer-les-résurrections-et-le-classement-finale-)
    - [Erreur non déterministe](#erreur-non-déterministe)
  - [Notes en vrac](#notes-en-vrac)
    - [\[ Prof \] .h vs .c](#-prof--h-vs-c)
    - [Type générique pour réutiliser une fonction copy\_stats](#type-générique-pour-réutiliser-une-fonction-copy_stats)


## 1. Des fighters
### Exercice
>1.Créez une liste pouvant contenir des Fighter avec les propriétés suivantes:
>* Un nom;
>* Un nombre de points de vie (nombre entier tel que 0<PV<MAX_PV).
>* Une position (coordonnées telles que 0<=x<MAX_X et 0<=y<MAX_Y, avec MAX_X et
MAX_Y des constantes que vous définissez).
>* Une vitesse (entier tel que 0<vitesse<MAX_VITESSE)
>2. Créez un tableau contenant des noms de fighters. À chaque démarrage du programme,
l’utilisateur choisira combien de fighters sont créés et les noms sont choisis aléatoirement dans ce
tableau. Toutes les autres caractéristiques sont aussi définies aléatoirement. Veillez juste à ce qu’il
n’y ait pas deux fighters à la même position.
>3. Créez une fonction pour afficher la liste des fighters et leurs caractéristiques.
>4. Créez une boucle dans votre programme principal (tant qu'il existe encore des fighters). A
chaque passage:
>* diminuez la vie de chaque fighter de 1 point;
>* si un fighter n'a plus de points de vie, affichez son nom et supprimez le de la liste;
>* déplacez les fighters survivants vers une position contigüe, aléatoirement (mais pas deux sur la
même)
>* affichez la liste;
>5. Ajoutez une fonction aléatoire qui sera appelée dans la boucle principale.
Cette fonction doit ajouter un fighter (de façon aléatoire, pas forcément à chaque tour), qui a la
moyenne des PV des fighters encore là.
>6. Ajoutez dans la boucle principale un appel à la fonction "sleep" pour permettre à l'utilisateur
de prendre le temps de lire ce qui est affiché en console.

### Résolution
[Voir fighters_base.c](code/fighters_base.c)

Compilation et exécution
```
gcc -o fighters_base.out fighters_base.c pq_tasbinaire_struct.c pile_chaine.c queue_chaine.c listes_chainees.c && ./fighters_base.out
```

### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C
* 12-Utiliser les ADT "file de priorité" pour résoudre des problèmes concrets en C
* 13-Utiliser la génération de nombres pseudo-aléatoires en C
* 14-Mener à bien un petit projet composé de plusieurs fichiers .c et .h

## 2. Les tirs
### Exercice
>1. Créez une nouvelle structure tir. Chaque tir aura pour caractéristique une vitesse (qui
détermine sa priorité), une puissance et une cible (coordonnées).
>2. À chaque tour, chaque fighter a une chance sur 2 de faire un tir vers une cible aléatoire.
>3. (Remplace le point 4 de l’exercice précédent) À chaque tour, le tirs avec la plus grande vitesse
sera effectué (ainsi que tous les autres tirs qui ont la même vitesse), et le fighter qui sera à cette
position perd des PV en fonction de la puissance du tir. À chaque tir effectué, tous les tirs gagnent
un point de vitesse.

### Résolution
[Voir fighters_tir.c](code/fighters_tir.c)

Compilation et exécution
```
gcc -o fighters_tir.out fighters_tir.c pq_tasbinaire_struct.c pile_chaine.c queue_chaine.c listes_chainees.c && ./fighters_tir.out
```

### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C
* 12-Utiliser les ADT "file de priorité" pour résoudre des problèmes concrets en C
* 13-Utiliser la génération de nombres pseudo-aléatoires en C
* 14-Mener à bien un petit projet composé de plusieurs fichiers .c et .h

## 3. Résurrection et fin du jeu
### Exercice
>À chaque tour, faites en sorte qu’il y ait une certaine probabilité que le dernier fighter mort soit
remis dans la partie avec la moyenne des points de vie des autres. Puis l’avant dernier etc.
À la fin du jeu, quand il n’en reste qu’un, il a gagné et le programme affiche les fighters un à un :
celui qui a gagné, puis le dernier mort, l’avant-dernier mort etc.

### Résolution
[Voir fighters_tir.c](code/fighters_tir.c)

Compilation et exécution
```
gcc -o fighters_tir.out fighters_tir.c pq_tasbinaire_struct.c pile_chaine.c queue_chaine.c listes_chainees.c && ./fighters_tir.out
```

### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C
* 12-Utiliser les ADT "file de priorité" pour résoudre des problèmes concrets en C
* 13-Utiliser la génération de nombres pseudo-aléatoires en C
* 14-Mener à bien un petit projet composé de plusieurs fichiers .c et .h

## Auto-Evaluation de la séance

### Comment générer des fighters ?
Je pars d'une liste de 50 fighters ayant des propriétés de combat (point de vie, vitesse, puissance ) qui est sous forme de ficher CSV. Celui-ci est chargée en mémoire dans un tableau de 50 structures `Stats_t` à chaque début de partie. Les index de ce tableau sont ajouter à une pile `available_fighters` qui renseigne les combatants disponibles pour un tirage (initial ou de retour dans la partie).

Grâce à un nombre aléatoire `skip` qui s'étend de 0 à la taille stack `available_fighters` moins un, on choisi un combattant en passant `skip` fois les fighters qui le précède dans la stack. Pour la sélection du fighter suivant, ces fighters défaussés sont remis dans la stack `available_fighters`.

Lorsqu'un fighter est sélectionné, il est placé dans une file de priorité `picked_fighters` qui est ordonnée selon le nombre de PV restants.

### Comment positionner et déplacer les fighters dans un espace ?
Une carte de l'arène carrée de taille (`MAX_X` +2) x (`MAX_Y` + 2) est générée sous forme d'un tableau à deux dimensions. Cette carte renseigne le nombre de fighters dans chaque case. Par convention, les cases de la bordure de la carte (zone inaccessible de l'arène) sont égale à 1 tandis que les cases de l'intérieur sont égales à 0 en l'absence de fighters.

A chaque positionnement ou déplacement, on interrogera cette carte pour voir si la case où souhaite déplacé un fighter est libre (valeur == 0). 

Lors d'un déplacement, si toutes les cases autour du fighter sont prises (valeurs > 0) alors il reste à sa position. Sinon, il choisit une des cases libres adjacentes au hasard.

### Dans le combat de base, comment gérer les fighters K.O. ?
Dans cette situation, chaque fighters présent dans la file de priorité `picked_fighters` voit ses points de vie diminués de 1 à chaque tour.

A la fin du tour, j'utilise la fonction `peek_queue` pour vérifier quels sont les PV du fighter le plus faible. Ensuite, j'utilise la fonction `serve_pq` pour enlever les fighters ayant atteints 0 PV. Dès lors, il reste uniquement les fighters encore en mesure de combattre dans la file de priorité `picked_fighters`.

### Dans le combat de base, comment ajouter des fighters en cours de partie ?
La même fonction que pour l'initialisation du combat `init_fight` est réutilisée en indiquant cette fois un nombre de fighter à ajouter égale à 1. Ceux-ci sont pris de la stack `available_fighters` et rajouter à la file de priorité `picked_fighters`. Cependant, leur PV sont modifier en se basant sur la moyenne des PV de tous les fighters restants (fonction `get_mean_pv`). 

Le choix d'ajouter ou non un nouveau combattant est déterminé par une valeur aléatoire modulo 5. Il y a donc une chance sur 5 de voir un nouveau combattant revenir dans un tour.

### Dans le combat par tir, comment gérer les tireurs et les blessés ?
Cette fois la file de priorité `picked_fighters` se base sur la vitesse des fighters et une fonction d'ordre inversée par rapport à l'implémentation de base (`geq` au lieu de `leq`). Les plus hautes vitesses sont prioritaires.

Lors d'un tour:
1. Les tireurs les plus rapide sont enlevés de `picked_fighters` et placés dans une pile `shooters_id`
2. Les autres fighters de `picked_fighters` voient leur vitesse augmenté de 1.
3. Ensuite, à tour de rôle, on évalue si les tireurs peuvent tirer (50 % de chance par `rand() % 2`).
4. Un tireur pouvant tirer va choisir au hasard un endroit où tirer sur la carte (sauf sa propre position) à l'aide de deux nombres aléatoires sur l'axe x `(rand() % MAX_X)+1`et l'axe y `(rand() % MAX_Y)+1`.
5. Au contraire de la version de base, le tableau à deux dimensions ``fighters_map`` renseigne l'id des combattant présent dans un case. Si un combattant est présent dans une case alors son identifiant est ajouté à la pile `woundeds_id`
6. Les PV d'un joueur touché sont ajustés dans la structure `all_fighters` en y soustrayant la puissance du tireur.
7. Si les PV d'un fighter blessé ont atteint 0, alors il est également ajouté à la pile `graveyard`.

### Comment gérer les résurrections et le classement finale ?
Pour la résurrection, la fonction `add_new_fighter` utilisée pour l'apparition de nouveau fighter est adaptée. En effet, le paramètre `Stack_t available_fighters` référence la pile `graveyard`.

Par rapport à la version de base, j'ai diminué à une chance sur 20 l'apparition d'un nouveau fighter ou une résurrection car les parties sont plus longues et les fighters ont moins de chance d'être blessés.

Pour le classement finale, j'arrête la boucle qui enclenche un nouveau round lorsqu'il reste 1 joueur ou moins. Dès lors, le classement utilise l'ordre "LIFO" de la pile `graveyard`.


### Erreur non déterministe 
Dans les implémentations de base ou par tir perdurent des erreurs de segmentation qui surviennent seulement à certaine partie. Après de nombreuses corrections, leur fréquence a été nettement réduite mais des erreurs perdures dans de rares conditions.

## Notes en vrac

### [ Prof ] .h vs .c

Dans .h:
* Nom de la structure
* Alias
* En tête des fonctions

Dans .c:
* Definition de la structure
* Implémentation des fonctions
* Fonction auxilliaires

Dans un .c, on peut inclure un .h

Pour cet exercice;
* queue.h
* queue.c
* liste_chainee.h
* liste_chaine.c
* stack.h
* stack.c

Si la liste_chainee est utilisée dans queue.c et stack.c, alors il faut faire un `#include "list_chainee.h" ` dans les autres fichiers .c . Lors de la compilation, il faut compiler tous les .c à la fois dans un seul fichier exécutable. Les `makefile` permettent de résoudre les problèmes de dépendances.


### Type générique pour réutiliser une fonction copy_stats
En C, ce n'est pas possible d'avoir une structure générique pour copier nimporte quel structure en utilisant des types "standards". Il faut utiliser des pointeurs de types vides et size_t qui est un type défini dans les header standard (stdio).

Par conséquent, pour utiliser une fonction générique dans plusieurs types de structures il faut faire:
Voir [fonction copy_stats](code/pq_tasbinaire_struct.c).

```
void copy_stats(void *dest, const void *src, size_t size) {
    memcpy(dest, src, size);
}
```