# Séance 1: Autour d’une file d’attente (Queue)
- [Séance 1: Autour d’une file d’attente (Queue)](#séance-1-autour-dune-file-dattente-queue)
  - [1. Type Queue](#1-type-queue)
    - [1.1 Concret ou abstrait](#11-concret-ou-abstrait)
      - [Exercice](#exercice)
      - [Résolution](#résolution)
      - [Objectifs rencontrés](#objectifs-rencontrés)
    - [1.2 Utilisation de la Queue](#12-utilisation-de-la-queue)
      - [Exercice](#exercice-1)
      - [Résolution](#résolution-1)
      - [Objectifs rencontrés](#objectifs-rencontrés-1)
    - [1.3 Définition d'une queue](#13-définition-dune-queue)
      - [Exercice](#exercice-2)
      - [Résolution](#résolution-2)
      - [Objectifs rencontrés](#objectifs-rencontrés-2)
  - [2. Implémentation d'une queue](#2-implémentation-dune-queue)
    - [2.1 Coffre fort](#21-coffre-fort)
      - [Exercice](#exercice-3)
      - [Résolution](#résolution-3)
      - [Objectifs rencontrés](#objectifs-rencontrés-3)
    - [2.2 Liste chainée simple](#22-liste-chainée-simple)
      - [Exercice](#exercice-4)
      - [Résolution](#résolution-4)
      - [Objectifs rencontrés](#objectifs-rencontrés-4)
    - [2.3 Tests de la queue](#23-tests-de-la-queue)
      - [Exercice](#exercice-5)
      - [Résolution](#résolution-5)
      - [Objectifs rencontrés](#objectifs-rencontrés-5)
    - [2.4 Implémentation de la queue](#24-implémentation-de-la-queue)
      - [Exercice](#exercice-6)
      - [Résolution](#résolution-6)
      - [Objectifs rencontrés](#objectifs-rencontrés-6)
  - [3. La pile (stack)](#3-la-pile-stack)
    - [3.1 C'est quoi une pile ?](#31-cest-quoi-une-pile-)
      - [Exercice](#exercice-7)
      - [Résolution](#résolution-7)
      - [Objectifs rencontrés](#objectifs-rencontrés-7)
    - [3.2 Fichier d'en-tête d'une pile](#32-fichier-den-tête-dune-pile)
      - [Exercice](#exercice-8)
      - [Résolution](#résolution-8)
      - [Objectifs rencontrés](#objectifs-rencontrés-8)
    - [3.3 Implémentation d'une pile](#33-implémentation-dune-pile)
      - [Exercice](#exercice-9)
      - [Résolution](#résolution-9)
      - [Objectifs rencontrés](#objectifs-rencontrés-9)
  - [4. Exercices supplémentaires](#4-exercices-supplémentaires)
    - [4.1 Exercice de compression de données](#41-exercice-de-compression-de-données)
      - [Résolution](#résolution-10)
      - [Objectifs rencontrés](#objectifs-rencontrés-10)
    - [4.2 Chiffrement de données](#42-chiffrement-de-données)
      - [Résolution](#résolution-11)
      - [Objectifs rencontrés](#objectifs-rencontrés-11)
    - [4.3 Calculatrice](#43-calculatrice)
      - [Résolution](#résolution-12)
      - [Objectifs rencontrés](#objectifs-rencontrés-12)
    - [4.4 Bataille](#44-bataille)
      - [Résolution](#résolution-13)
      - [Objectifs rencontrés](#objectifs-rencontrés-13)
  - [Auto-Evaluation de la séance](#auto-evaluation-de-la-séance)
  - [Notes en vracs](#notes-en-vracs)

## 1. Type Queue

### 1.1 Concret ou abstrait
#### Exercice
> Jetez un œil sur le fichier queue.h reproduit ici. S’agit-il d’un type de donnée abstrait ou concret ?
Justifiez vos réponses en vous basant sur les définitions de ces types de données.

#### Résolution
* Qu'est ce qu'un élément abstrait ?
  * Element pour lequel des opérations et des propriétés peuvent être définies mais en ne précisant pas l'implémentation 
    * Ex: Concept d'une machine à jus de fruit est définie; on y place des orange murs entières et on obtient un jus sous forme liquide. On ne définit pas comment la machine est crée. 
  * Similarité avec une spécification dans la réalisation d'un projet informatique
* La queue est une donnée abstraite car on définit des concepts que l'on veut faire avec celle-ci sans avoir d'implémentation

#### Objectifs rencontrés
* 5-Comprendre le principe d’un type abstrait de données 

### 1.2 Utilisation de la Queue
#### Exercice
> Sans connaître l’implémentation de la Queue, pouvez-vous prédire ce qui va être affiché lors de
l’exécution du programme "manipulation_queue.c" ? Si oui, indiquez ce qui va être affiché.
Est-ce que plusieurs implémentations concrètes correctes de la Queue sont possibles ? Cela va-t-il
influencer l’expérience de l’utilisateur du programme "manipulation_queue.c" ? Si oui, en quoi ?
Sinon, pourquoi ?

#### Résolution
* [queue.h](fichiers/queue.h) donne quelques opérations et propriétés de la queue sans proposer d'implémentation concrète. Le header est à compléter pour avoir une utilisation valide de ``manipulation_queue.c``.
* Plusieurs implémentations concrètes sont possibles mais l'expérience utilisateur reste semblable car les opérations et propriétés qui sont réellement utiles à l'utilisateur reste semblable entre plusieurs implémentations pour la même donnée abstraite

#### Objectifs rencontrés
* 3-Comprendre la différence entre les fichiers .c et les fichier d’entête .h et être capables, lors de
l’écriture d’un programme, de jongler entre les deux


### 1.3 Définition d'une queue
#### Exercice
> Identifiez les éléments clés qui permettent de définir une Queue (en particulier : les opérations et
propriétés d’une Queue).

#### Résolution

* Opérations:
  * Création et allocation en mémoire de la queue
  * Ajout d'un élément entier à la queue
  * Retrait de l'élément le plus anciennement ajouté à la queue
  * Destruction de la queue en mémoire
* Propriétés:
  * Une queue possède une structure
  * Une queue renseigne un pointeur qui permet de contenir plusieurs éléments
  * Une queue possède une taille (nombre d'éléments restants dans la structure)

#### Objectifs rencontrés
* 5-Comprendre le principe d’un type abstrait de données (abstract data type, ADT)



## 2. Implémentation d'une queue

### 2.1 Coffre fort
#### Exercice
> Examinez le code "coffre_fort.c" qui vous est fourni et utilisez-le pour clarifier les éléments
suivants :
-Comment est définie concrètement une structure en C ? En particulier, comment la nommer,
comment créer un type synonyme (ou alias), comment définir des champs ?
-Comment créer, en C, un tableau dont on ne connaît pas la taille avant l’exécution du programme ?
-À quoi sert "malloc" ? Comment l’employer ? Que prend-il comme argument ? Que renvoie-t-il ?
-À quoi sert "free" ? Pourquoi l’employer ? Que prend-il en argument ?

#### Résolution

**Comment est définie une structure et alias en C?** 

Exemple pour une date:
```
// Structures des données
typedef struct Date{
    int jour;
    int mois;
    int annee;
} Date;
```
**Comment créer un tableau en C dont on ne connaît pas la taille avant l'exécution.**

```
int main(){
    int size = 32;
    int* mytab = malloc(size*sizeof(int));
    //Some code
    free(mytab);
    mytab=NULL;
    return 1;
}
```

* Déclaration d'un tableau via pointeur et allocation de la mémoire du tas via fonction `malloc`
* Ne pas oublier de libérer la mémoire en fin de programme avec `free(mytab)`
* Bonne pratique: Indiquer explicitement que le pointeur n'est plus utilisé

#### Objectifs rencontrés
* 1-Se remettre à flot avec les concepts de base du C vus au précédent quadrimestre : types,
variables, expressions arithmétiques, conditions, boucles, chaines de caractères, fonctions,
structures, pointeurs
* 2-Comprendre et savoir utiliser l’allocation dynamique de mémoire en C (malloc) et la libération
de la mémoire allouée (free) 

### 2.2 Liste chainée simple
#### Exercice
>La liste simplement chainée est un type de donné concret dynamique (dont la taille n’est pas fixée à
l’avance).
Déterminez ce qu’est concrètement une liste simplement chainée et proposez-en une
implémentation en C.
Suggestion : définissez deux structures. Une pour la liste "en elle-même" et une pour les nœuds de
la liste, qui s’enchainent dont le dernier pointe vers NULL.
Proposez ensuite une implémentation d’une liste doublement chainée et d’une liste doublement
chainée circulaire.

#### Résolution

Une liste chaînée simple est constituée de noeuds où chaque noeud contient une donnée et un pointeur vers le noeud suivant.

[Voir blog](https://blog.alphorm.com/listes-chainees-en-c-concepts-et-applications#:~:text=Une%20liste%20cha%C3%AEn%C3%A9e%20simple%20est%20une%20structure%20de%20donn%C3%A9es%20o%C3%B9,une%20gestion%20dynamique%20des%20%C3%A9l%C3%A9ments.) pour plus d'explications.

La chaîne est une sorte de structure récursive où un noeud fait référence à un noeud via son pointeur. 

```
typedef struct chaine_s{
    char *nom;
    char *prenom;
    int age;
    int* next;
    struct chaine_s *next;
} chaine_s;
```
Voir [listes_chainees.c](code/listes_chainees.c) et [listes_chainees.h](code/listes_chainees.h)

#### Objectifs rencontrés
* 1-Se remettre à flot avec les concepts de base du C vus au précédent quadrimestre : types,
variables, expressions arithmétiques, conditions, boucles, chaines de caractères, fonctions,
structures, pointeurs
* 2-Comprendre et savoir utiliser l’allocation dynamique de mémoire en C (malloc) et la libération
de la mémoire allouée (free)
* 3-Comprendre la différence entre les fichiers .c et les fichier d’entête .h et être capables, lors de
l’écriture d’un programme, de jongler entre les deux
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 5-Comprendre le principe d’un type abstrait de données (abstract data type, ADT)
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

### 2.3 Tests de la queue
#### Exercice
> Écrivez une fonction qui vous permettra de tester la Queue que vous allez implémenter à l’étape
suivante. Dans cette fonction, vous veillerez à tester chacune des 5 fonctions définie dans le fichier
d’entête. N’hésitez pas à vous répartir le travail, pour que chacun et chacune se concentre sur une
ou deux fonction et prévoie de la tester à fond. Veillez à ce que cette fonction indique à chaque
fois quelque chose du type:

#### Résolution

* Voir [queue_tests.c](code/queue_tests.c).

Tous les tests passent pour [queue_tableau.c](code/queue_tableau.c) en compilant:
```
gcc -o queue_tests.out queue_tests.c queue_tableau.c && ./queue_tests.out
```

Tous les tests passent pour [queue_chaine.c](code/queue_chaine.c) en compilant:
```
gcc -o queue_tests.out queue_tests.c queue_chaine.c listes_chainees.c && ./queue_tests.out
```

#### Objectifs rencontrés

* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

### 2.4 Implémentation de la queue
#### Exercice
>Proposez deux manières d’implémenter la Queue, au moyen d’une structure statique (par exemple,
un tableau) et au moyen d’une structure dynamique (par exemple, une liste chainée simple,
doublement chainée, chainée circulaire, etc.).
Déterminez les avantages et inconvénients de chacune de ces deux implémentations.

#### Résolution

**Implémentation avec un tableau**

[Voir queue_tableau.c](code/queue_tableau.c)

Compilation avec tests: 
```
gcc -o queue_tests.out queue_tests.c queue_tableau.c && ./queue_tests.out
```

**Implémentation avec une chaine double**

[Voir queue_chaine.c](code/queue_chaine.c)

Se base sur une liste doublement chainée:
* Création d'un en-tête: `listes_chainees.h` avec toutes les fonctions pour manipuler et display des listes
* Inclusion de `listes_chainees.h` dans `listes_chainees.c` et `queue_chaine.c`
* Compilation avec tests:
```
gcc -o queue_tests.out queue_tests.c queue_chaine.c listes_chainees.c && ./queue_tests.out
```

**Avantages et inconvénients**

L'implémentation avec une chaîne double nécessite d'abord de définir et implémenter ce concept. Par la suite, l'implémentation de la queue est plus aisé vu que la liste chaînée est faite pour être agrandie ou réduite sans définir une taille au préalable.

Par contre, avec une implémentation via un tableau, pas besoin de générer un nouveau concept mais il faut gérer la capacité du tableau. L'agrandissement ou le rétrécissement du tableau est assez complexe et error prone. Il faut de nouveaux champs ``capacité`` et ``offset`` qui permettent de savoir ce qui a été enlevé ou l'ajustement à apporter vis à vis de la capacité en "mémoire" du tableau. 

#### Objectifs rencontrés

* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières



## 3. La pile (stack)

### 3.1 C'est quoi une pile ?
#### Exercice
> Stack est un ADT. Déterminez les opérations et propriétés qui permettent de le définir.

#### Résolution

Comme une queue c'est une donnée abstraite qui peut:
*  s'agrandir de façon dynamique en y ajout des éléments un par un
*  se rétrécir en enlevant des éléments un par un
*  être initialisée (mais vide)
*  être détruite

La principale différence, c'est l'ordre de sortie. Au lieu d'être le premier arrivé, le premier enlevé, la pile se caractérise comme le dernier arrivé, le premier enlevé.

#### Objectifs rencontrés

* 5-Comprendre le principe d’un type abstrait de données (abstract data type, ADT)


### 3.2 Fichier d'en-tête d'une pile
#### Exercice
>À partir de la définition que vous avez donnée d’une pile, déterminez un fichier d’entête (.h) qui
contient la signature des fonctions qui permettent de définir cet ADT. Pour chacune de ces
fonctions, indiquez bien ses préconditions et postconditions.

#### Résolution

[Voir pile.h](code/pile.h)

#### Objectifs rencontrés

* 3-Comprendre la différence entre les fichiers .c et les fichier d’entête .h et être capables, lors de l’écriture d’un programme, de jongler entre les deux
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières


### 3.3 Implémentation d'une pile
#### Exercice
>Implémentez la pile définie précédemment dans un fichier .c de deux façons différentes : au moyen
de tableaux et au moyen de listes chainées (simplement, ou doublement, ou circulaire).

#### Résolution

**Implémentation avec un tableau**

[Voir pile_tableau.c](code/pile_tableau.c)

Compilation avec fichier tests:

```
gcc -o pile_tests.out pile_tests.c pile_tableau.c && ./pile_tests.out
```

**Implémentation avec une chaine double**

[Voir pile_chaine.c](code/pile_chaine.c)

```
gcc -o pile_tests.out pile_tests.c pile_chaine.c listes_chainees.c && ./pile_tests.out
```

#### Objectifs rencontrés

* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

## 4. Exercices supplémentaires
### 4.1 Exercice de compression de données
[#### Exercice](fichiers/01_compression_données.pdf)
>La compression de données (sans pertes) est une méthode qui consiste à diminuer la taille des données
tout en nous permettant de les récupérer au complet. Par exemple, si vous avez plusieurs boites en
carton de taille variable, une façon de les "compresser" pourrait être de les mettre les unes dans
les autres. Un autre moyen pourrait être de les plier. Ces deux méthodes de rangement de boites sont
différentes, mais permettent toutes les deux de gagner de la place tout en nous permettant de récupérer
les boites initiales quand on le souhaite.
Pour ce travail, nous n’allons pas compresser des boites, mais des messages. À partir de maintenant,
nous considérons qu’un message est un tableau d’entiers. La méthode de compression utilisée ici est
le codage par répétitions.
Le codage par répétitions consiste à remplacer toute séquence de nombres identiques par le nombre
d’occurrences du nombre suivi du nombre lui-même. Ainsi, par exemple, le message
{1,1,1,0,0,3,3,3,3,3,3} sera compressé en {3,1,2,0,6,3}. En effet, dans le message original, on
remarque qu’il y a d’abord 3 fois le nombre 1, puis 2 fois le nombre 0, puis 6 fois le nombre trois.
Vous remarquez que sur cet exemple, la version compressée prend moins de place que la version non-
compressée. À votre avis, est-ce toujours le cas ?

>On vous demande d’écrire un programme C permettant de compresser n’importe quel tableau de
nombres.
Le programme contiendra une méthode main, où l’utilisateur est invité à entrer un tableau d’entiers.
Pour ce faire, il entre d’abord la taille du tableau, puis chacun des entiers un par un. Le programme
affichera par exemple :
>- Veuillez indiquer la taille du tableau à compresser: 10
>- Nombre 1: 2 
>- Nombre 2: 2 
>- Nombre 3: 2 
>- Nombre 4: 1
>- Nombre 5: 10
>- Nombre 6: 10
>- Nombre 7: 10
>- Nombre 8: 10
>- Nombre 9: 0
>- Nombre 10: 0
>- Tableau compressé: [3,2,1,1,4,10,2,0]

#### Résolution

[Voir compression_tableau.c](code/compression_tableau.c)

Compilation et exécution:
```
gcc -o compression_tableau.out compression_tableau.c && ./compression_tableau.out
```

#### Objectifs rencontrés

* 1-Se remettre à flot avec les concepts de base du C vus au précédent quadrimestre : types,
variables, expressions arithmétiques, conditions, boucles, chaines de caractères, fonctions,
structures, pointeurs

### 4.2 Chiffrement de données
[#### Exercice](fichiers/02_chiffrement_donnees_utf8.pdf)
>La cryptographie consiste généralement à prendre un texte (appelé texte clair) et à lui appliquer un
algorithme de chiffrement avec des paramètres bien choisis. L’exécution de cet algorithme produit un
texte qui semble ne plus avoir aucune signification (appelé texte chiffré). Le seul moyen de retrouver
le texte clair est d’appliquer un algorithme de déchiffrement sur le texte chiffré.
Nous considérons pour le reste de ce projet que nos textes sont des suites de chiffres binaires (0 ou 1),
que le nombre de chiffres est un multiple de 3 et qu’un bloc est une séquence de 3 chiffres consécutifs
dans le texte. Ainsi, un texte pourrait être : 100001111000110. Dans ce texte, le premier bloc est 100,
le second est 001, le troisième 111 etc.
Nous allons implémenter dans le cadre de ce projet une technique de chiffrement utilisée de nos jours :
le chiffrement par enchainement de blocs ou Cipher Bloc Chaining (CBC). Cette technique consiste à :
— combiner le bloc courant au bloc précédent
— chiffrer le nouveau bloc combiné au moyen d’une fonction de chiffrement prédéfinie
— combiner le bloc ainsi chiffré avec le bloc suivant et recommencer
Bien entendu il faut, pour que cette méthode fonctionne, fournir à l’algorithme un bloc supplémentaire
à combiner avec le premier bloc du texte clair. Ce bloc est appelé vecteur d’initialisation ou initialization
vector (IV).
Pour ce TP, nous combinerons les blocs en leur appliquant l’opération XOR (« ou exclusif »). Le XOR
entre deux nombre binaires est le résultat du XOR de chacun de leurs bits : 100 XOR 010 = 110.
La fonction de chiffrement sera, quant à elle, simpliste : elle consistera juste à inverser chaque bit du
bloc : chiffrement(100) = 011.

>On vous demande d’écrire un programme C permettant de chiffrer n’importe quelle suite de chiffres
binaires dont le nombre de chiffres est un multiple de trois. Pour représenter cette suite de chiffres
binaires, utilisez des files (Queue).
Le programme contiendra une méthode main, où l’utilisateur est invité à entrer une chaine de nombres
binaires et un vecteur d’initialisation, ainsi qu’une fonction de chiffrement. La fonction de chiffrement
à implémenter correspond à la signature et aux spécifications suivantes :

````
/*
PRE: iv, suite de chiffres binaires initialisee (!=NULL) et de taille 3
 plaintext, suite de chiffres binaires initialisee (!=NULL) de taille multiple de 3
POST: renvoie une suite de chiffres binaires dont la taille vaut
 taille(plaintext). Elle correspond au chiffrement de la
 suite de chiffres binaires plaintext avec pour vecteur d’initialisation
 iv.
 plaintext et iv n’ont pas ete modifies
*/
Queue_t chiffrer(Queue_t iv, Queue_t plaintext);

````
#### Résolution

[Voir chiffrement.c](code/chiffrement.c)

Compilation et exécution:
```
gcc -o chiffrement.out chiffrement.c queue_chaine.c listes_chainees.c  && ./chiffrement.out
```

#### Objectifs rencontrés

* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C

### 4.3 Calculatrice
[#### Exercice](fichiers/03_calculatrice.pdf)
>Réalisez un programme C qui implémente une calculatrice simple qui fonctionne de cette façon :
>- L’utilisateur entre des nombres
>- L’utilisateur entre un opérateur qui va s’appliquer aux derniers nombres (en fonction de l’opé-
rateur) et replacer le résultat sur la pile.
Le programme ne s’arrête jamais donc l’utilisateur peut soit rentrer un nombre soit un opérateur à
chaque fois. Voici la liste des opérateurs à supporter :
>- Les 4 opérateurs standard : +, -, *, /
>- Un opérateur spécial pour quitter le programme et afficher le résultat qui est le dernier nombre
à avoir été mis sur la pile (=)
>- ++ et ** qui permettent de faire la somme et le produit de tous les nombres sur la pile
Veillez à employer la pile (Stack) que vous avez implémentée lors de la séance 1.

#### Résolution

[Voir calculatrice.c](code/calculatrice.c)

Compilation et exécution:
```
gcc -o calculatrice.out calculatrice.c queue_chaine.c pile_chaine.c listes_chainees.c  && ./calculatrice.out
```

Pour se faire, j'ai eu besoin de:
1. Détecter si une chaine de caractère est composée uniquement d'entier besoin d'utilisé
2. Utiliser la fonction atoi() afin de transformer une chaine de caractère incluant seulement des digits en entier
3. Me rappeler qu'un string est terminé par un caractère nul `\0`
4. Utiliser un switch pour organiser mes différentes opérations

#### Objectifs rencontrés

* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C


### 4.4 Bataille
[#### Exercice](fichiers/04_bataille.pdf)

>Voici la description du jeu de "Bataille Complexe" qu’il vous est demandé de réaliser. Il doit s’agir d’un
programme C avec lequel on interagit en ligne de commande. D’abord, nous décrivons le jeu de base ;
ensuite, nous exposons les différentes extensions/modes de jeu qui doivent venir le complexifier.

>**Jeu de base**: 
Le jeu se base sur le principe d’une Bataille :
>- On commence par mélanger le paquet de cartes.
>- Le paquet est distribué équitablement entre les deux joueurs.
>- Chaque joueur tire la première carte de son paquet.
>- C’est le joueur avec la carte la plus haute1 qui remporte la manche. Il récupère les cartes qui ont
été retournées ce tour-ci et les place sous son paquet de cartes.
>- Dans le cas où les cartes tirées sont égales, les joueurs retournent à nouveau une carte, et le duel se
fait entre les deux nouvelles cartes tirées. Jusqu’à ce qu’il y ait un gagnant pour cette manche... ou
que la partie se termine, voir point suivant.
>- Le jeu se poursuit de cette manière jusqu’à ce qu’un joueur n’ait plus de cartes ; il est alors perdant
de la partie, à moins qu’au même moment, l’autre joueur n’ait plus de cartes non plus, auquel cas
la partie se solde en une égalité.
Dans le jeu de base, il n’y a pas besoin d’interagir avec la console : les deux joueurs font leurs actions
automatiquement. Autrement dit, lorsque l’on exécute votre programme, une partie complète doit se
dérouler immédiatement et le résultat de chaque manche doit clairement être affiché à l’écran. On doit
donc pouvoir retracer chaque coup effectué en lisant la console, et savoir quel joueur (joueur 1 ou joueur 2) a remporté la partie.

>**Extensions**
La Bataille, c’est chouette, mais ça manque de stratégie... et puis, regarder des ordinateurs jouer l’un
contre l’autre, c’est un peu limité, non ? Pimentons tout cela ! Voici quelques extensions/améliorations
du jeu qui permettront de le rendre plus intéressant.
>1. Permettez que l’on puisse relancer une partie dès qu’une partie est finie, pour ne pas devoir relancer
le programme.
>2. Sélectionnez au hasard une couleur dominante à chaque carte tirée. Cette couleur donne un bonus
de 1 point à toute carte de cette même couleur.
>3. Ajoutez un mode de jeu "multicartes" dans lequel les joueurs ne tirent pas une, mais deux (si
possible) cartes, et choisissent laquelle des deux jouer. Il ne s’agit donc plus d’un jeu automatique
entre ordinateurs : il faut que les joueurs interagissent avec la console car ils doivent choisir une des
deux cartes. La carte qu’ils ne choisissent pas est défaussée. Pour le choix des cartes, on commence
par le joueur ayant perdu la dernière manche ou, à défaut, par le joueur 1.
>4. Ajoutez un mode de jeu "atouts" qui peut être sélectionné au début d’une partie, et qui fonctionne
comme suit :
• chaque joueur, au départ, choisit une "couleur" (pique/trèfle/carreau/cœur) ;
• lorsqu’un joueur remporte une manche avec une carte de sa couleur, il gagne un point ;
1 L’as est considéré comme la plus forte de toutes !
2
• lorsqu’un joueur perd une manche alors qu’il avait joué une carte de sa couleur, il perd un
point ;
• en fin de partie, le joueur n’est plus le premier à avoir écoulé son tas de cartes... mais celui qui
a le plus de points !
>5. Ajoutez un cheat code au mode "multicartes" : lorsqu’un joueur doit choisir une carte, il peut entrer
un code secret qui lui permet de mélanger son paquet de cartes et d’en tirer deux nouvelles.
>6. À chaque nouvelle partie, demandez à l’utilisateur combien de joueurs vont s’affronter. Clarifiez vous-
mêmes les règles pour la Bataille à plus de deux joueurs (comment répartir les cartes ? combien de
joueurs maximum ?), et documentez vos choix dans votre rapport.
>7. D’autres idées d’amélioration ? Allez-y !
Les extensions peuvent être implémentées de différentes manières, évidemment, et avec quelques nuances
de fonctionnement. Dans le rapport, détaillez vos choix et expliquez comment vous avez levé les
ambiguïtés éventuelles de l’énoncé.

#### Résolution

* [Voir jeu de base](code/bataille_base.c)
  * Compilation et exécution:
```
gcc -o bataille_base.out bataille_base.c queue_chaine.c pile_chaine.c listes_chainees.c  && ./bataille_base.out
```


* [Voir jeu avec extension](code/bataille_extensions.c)
  * Compilation et exécution:
```
gcc -o bataille_extensions.out bataille_extensions.c queue_chaine.c pile_chaine.c listes_chainees.c  && ./bataille_extensions.out
```

#### Objectifs rencontrés

* 7-Utiliser les ADT "file d’attente" et "pile" pour résoudre des problèmes concrets en C

## Auto-Evaluation de la séance

Tout d'abord, j'ai eu des difficultés à comprendre comment utiliser les structures et leurs alias à travers les headers.h et les implémentations.c. Au fil des des scéances et des exemples de codes rencontrés, j'ai choisi de:
* Déclarer une ``struct`` vide dans le header
* Déclarer un alias, comme par exemple `List_t`, comme pointeur de la structure vide déclaré précédemment dans le header.
* Comme l'implémentation doit comporter plus de détails, c'est dans celle-ci que sont déclarer les structures ``struct`` (sans alias) dans les différents fichiers d'implémentation.

Ensuite, les premiers essais d'allocations en mémoire `malloc` se sont soldés par des erreurs de segmentation car c'est le pointeur que je mettais dans le `sizeof` et non pas la structure en tant que telle. Ayant compris cela, les allocations en mémoire suivantes se sont mieux passés.  

Finalement, les exercices supplémentes ont permis de répondre à un problème avec nos connaissances nouvellement apprises. C'est une partie de cette séance que j'apprécie car cela permet de répondre à un problème concret tandis que l'approche théorique me semblait moins compréhensible de prime abord. Par contre, au bout du 4e exercice supplémentaire, j'ai trouvé l'exercice sur la bataille (trop) long à implémenter (projet à part entière) et je n'ai pas implémenté toutes les extensions car je pense avoir bien atteint les objectifs de la séance.

*A propos de la bataille:*
* Les règles de la bataille n'étaient pas clairement stipulées dans l'énoncé. Par défaut, je les ai définies comme tel:
  1. Un coup commence
  2. Les joueurs retournent chacun une carte.  Celles-ci sont identiques. Il y a "bataille".
  3. Les joueurs posent chacun une carte face cachée. Celles-ci n'interviennent pas pour désigner le vainqueur du coup.
  4. Les joueurs retournent, de nouveau, chacun une carte. Celui avec la carte la plus grande remporte toutes les cartes posées dans ce coup. 
  5. S'il y a de nouveau bataille, on boucle entre les points 3-4 jusqu'à une résolution ou au moins, un joueur n'a plus de carte.
  6. Le coup se termine
* J'ai d'abord éprouvé quelques difficultés pour réutiliser les implémentations précédentes des queues et des piles. Pour résoudre cela, il m'a fallu convertir la valeur des cartes et leur couleur en une seule valeur entière et effectuer une conversion/traduction on the fly à l'aide d'une structure dédiée ou une position de 0-51 correspond à une valeur de carte (propriétés: id,force, couleur, nom de la carte).
* Enfin, le mécanisme de distribution de cartes pseudo-aléatoire n'était pas une implémentation évidente. 
  * Pour se faire, j'ai utiliser 4 piles:
    * Source
    * Défausse
    * Joueur A
    * Joueur B
  *  Au début, la source contient les 52 cartes (id entier de 0-51). Pour donner une carte à un jour, la fonction ``rand() % size(source)`` retourne un entier de 0 à la taille de la stack. Ce nombre va être utiliser pour placer ce nombre de carte dans la défausse. Ensuite, la carte suivante va à un des deux joueurs. Avant le tirage du joueur suivant, toutes les cartes défaussées retournes dans la source. On recommence jusqu'à ce que la source soit équitablement partagée entre les 2 joueurs.
*  Avec mon mécanisme de tirage de cartes, j'ai vite constaté que la partie ne se résolvait jamais. Il m'a fallu utiliser `srand(time(NULL))` pour avoir un nouveau seed entre chacune partie. Mon seed par défaut donnait une partie "trop" équilibrée mais d'autres seed permettait de voir un joueur s'imposer.

## Notes en vracs

**Manipulation des bits**
* Opérateur `&` pour un AND au niveau du bit (>< `&&` au niveau du nombre entier)
* Opérateur `|` pour un OR au niveau du bit (>< `||` au niveau du nombre entier)
* Opérateur `>>` signifie un shift right logical au niveau des bits du nombre (`1000` devient `100`)
* Opérateur `<<` signifie un shift left logical au niveau des bits du nombre (`111` devient `1110`)
* Masque binaire: `0b111` est une représentation binaire du nombre 7 (LSB: `111`). Utilisation du masque binaire pour se concentrer sur les 3 LSB `n & 0b111 `
* unsigned int et int ont le même pattern de bits si on reste sur les entiers positifs < 2^32-1
* `((n >> i) & 1) ? '1' : '0'` Pour décrire un if-then-else avec des valeurs charactères (utilisé `'` et non `"`)
* `a ^ b` pour faire un XOR entre les bits de int a et int b
