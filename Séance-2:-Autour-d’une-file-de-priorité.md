
- [1. File de priorité](#1-file-de-priorité)
  - [1.1. ADT File de priorité](#11-adt-file-de-priorité)
    - [Exercice](#exercice)
    - [Résolution](#résolution)
    - [Objectifs rencontrés](#objectifs-rencontrés)
  - [1.2. Passer une fonction en argument](#12-passer-une-fonction-en-argument)
    - [Exercice](#exercice-1)
    - [Résolution](#résolution-1)
    - [Objectifs rencontrés](#objectifs-rencontrés-1)
  - [1.3. Testez votre file de priorité](#13-testez-votre-file-de-priorité)
    - [Exercice](#exercice-2)
    - [Résolution](#résolution-2)
    - [Objectifs rencontrés](#objectifs-rencontrés-2)
  - [1.4. Implémenter votre file de priorité avec un type déjà vu](#14-implémenter-votre-file-de-priorité-avec-un-type-déjà-vu)
    - [Exercice](#exercice-3)
    - [Résolution](#résolution-3)
    - [Objectifs rencontrés](#objectifs-rencontrés-3)
  - [1.5. Implémenter une file de priorité avec heap / tas binaire](#15-implémenter-une-file-de-priorité-avec-heap--tas-binaire)
    - [Exercice](#exercice-4)
    - [Résolution](#résolution-4)
    - [Objectifs rencontrés](#objectifs-rencontrés-4)
- [2 Programme de suggestion de livre](#2-programme-de-suggestion-de-livre)
    - [Exercice](#exercice-5)
    - [Résolution](#résolution-5)
    - [Objectifs rencontrés](#objectifs-rencontrés-5)
- [Auto-Evaluation de la séance](#auto-evaluation-de-la-séance)
  - [1. Comment agrandir et rétrécir un tableau avec une allocation dynamique de mémoire ?](#1-comment-agrandir-et-rétrécir-un-tableau-avec-une-allocation-dynamique-de-mémoire-)
  - [2. Comment enlever le premier élément d'un tableau ?](#2-comment-enlever-le-premier-élément-dun-tableau-)
  - [3. Comment ajouter un élément à la dernière position d'un tas binaire étant donné qu'on se fait une représentation sous forme d'arbre ?](#3-comment-ajouter-un-élément-à-la-dernière-position-dun-tas-binaire-étant-donné-quon-se-fait-une-représentation-sous-forme-darbre-)
  - [4. Comment entrer des titres de film comprenant des blancs par interaction avec la console ?](#4-comment-entrer-des-titres-de-film-comprenant-des-blancs-par-interaction-avec-la-console-)
- [Notes en vracs](#notes-en-vracs)
  - [\[ Prof \] Exemple de chaine circulaire doublement chainée](#-prof--exemple-de-chaine-circulaire-doublement-chainée)
  - [Comprendre la priority queue](#comprendre-la-priority-queue)
  - [\[ Prof \] Notion de Complexité](#-prof--notion-de-complexité)
  - [\[ Prof \] Tas binaire](#-prof--tas-binaire)



Les objectifs de cette séance, et du travail individuel à fournir d’ici la séance suivante, sont :
* 8-Être capable de comprendre un ADT fourni dans une notation formelle
* 9-Créer et manipuler des fonctions qui prennent en argument d’autres fonctions
* 10-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières
* 11-Étre capable d’écrire une suite de tests simples pour tester l’implémentation d’un ADT.
* 12-Utiliser l’ADT "file de priorité" pour résoudre des problèmes concrets en C

## 1. File de priorité

### 1.1. ADT File de priorité

#### Exercice
>Dans un article de 1990 1, l’informaticienne Nell Dale, définit
l’ADT "File de Priorité".
Fournissez un fichier entête (.h) correspondant à cet ADT.
Notez que dans cet ADT, il n’y a pas de return mais des variables de sorties passées en argument.
N’employez pas ce type de variable de sortie.
Basez-vous sur PQ.h et complétez-le.
Ajoutez à la notation formelle une opération "peek", qui renvoie l’élément avec la plus haute
priorité mais ne modifie pas la file de priorité. Ajoutez-la ensuite à votre fichier entête.

#### Résolution
[Voir priority_queue.h](cours2/code/priority_queue.h)

#### Objectifs rencontrés
* 5-Comprendre le principe d’un type abstrait de données 
* 8-Être capable de comprendre un ADT fourni dans une notation formelle

### 1.2. Passer une fonction en argument

#### Exercice
>Dans PQ.h, vous remarquez que la fonction create a un argument étrange. Il s’agit d’une fonction passée en argument qui permettra de définir une relation d’ordre dans notre file de priorité, en disant, pour deux éléments donnés, si le premier est plus petit que le deuxième. Ça permet de définir un ordre.
Pour comprendre le fonctionnement du passage de fonction en argument, complétez le programme
C printmap.c qui comportera les fonctions suivantes :
>- Une fonction doubler, qui prend en argument un entier et renvoie cet entier multiplié par deux.
>- Une fonction inc, qui prend en argument un entier et renvoie cet entier incrémenté de 1.
>- Une fonction printmap qui ne renvoie rien, qui prend en argument un tableau d’entiers, sa taille et une fonction qui prend en argument un entier et renvoie un entier et qui modifie le tableau passé en argument en appliquant à chacun de ses éléments la fonction passée en argument, et l’affiche.

#### Résolution
[Voir printmap.c](cours2/code/printmap.c)

Compilation et exécution:
```
gcc -o printmap.out printmap.c  && ./printmap.out
```

#### Objectifs rencontrés
* 9-Créer et manipuler des fonctions qui prennent en argument d’autres fonctions

### 1.3. Testez votre file de priorité

#### Exercice
>Déterminer une série de tests que devront passer votre file de priorité, sous la forme d’une fonction
de test qui crée une file de priorité, lui applique une série d’opération et fait un certain nombre de
vérifications. Veillez à ce que vos tests soient le plus complet possible (testez toutes les fonctions,
testez des cas standards et des cas particuliers, etc.). Cette fonction, idéalement, affiche, test par test,
s’il est réussi ou pas. Ça vous permettra, lorsque la file de priorité sera implémentée, de la tester

#### Résolution

[Voir test.c](cours2/code/test.c)

#### Objectifs rencontrés
* 11-Étre capable d’écrire une suite de tests simples pour tester l’implémentation d’un ADT.


### 1.4. Implémenter votre file de priorité avec un type déjà vu

#### Exercice
>Implémentez PQ au moyen d’un type que vous avez déjà employé ou défini précédemment :
tableau, liste chainée, file, pile. Trouvez ensuite quelqu’un qui l’a implémenté au moyen d’un autre
type de données et évaluez, fonction par fonction, la différence de complexité temporelle et spatiale.
#### Résolution
Avec tableau: [voir pq_tableau.c](cours2/code/pq_tableau.c)

Compilation et exécution des tests (Tous les tests passent):
```
gcc -o test.out test.c pq_tableau.c  && ./test.out
```
Un tri à bulle est utilisé pour ordonner le tableau après chaque ajout. La complexité est d'ordre `O(n²)` à chaque ajout et d'ordre `O(1)` à chaque fois que le nombre le plus prioritaire est retourné.
Par rapport à la complexité spatiale, l'espace mémoire croit de façon linéaire par rapport à la taille de la file de priorité donc une complexité `O(n)`.
La complexité peut être réduite à `O(n)` car dans cette implémentation, je n'utilise pas la propriété que le tableau est déjà ordonné avant l'ajout.  

#### Objectifs rencontrés
* 9-Créer et manipuler des fonctions qui prennent en argument d’autres fonctions
* 10-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières


### 1.5. Implémenter une file de priorité avec heap / tas binaire

#### Exercice
>Un tas binaire (heap) est une manière intéressante d’implémenter une file de priorité comme d’un
arbre binaire presque complet ordonné (chaque nœud parent est plus grand ou égal à son nœud
enfant), au moyen par exemple d’un tableau (dont le premier élément vaut la racine, puis les deux
éléments suivant le niveau 1 de l’arbre, puis les 4 éléments suivants le niveau 2 et ainsi de suite).
Implémentez la file de priorité définie précédemment comme un tas binaire. N’hésitez pas à
consulter la vidéo suivante qui explique visuellement comment ajouter et retirer des éléments :
File de priorité et tas binaire , François Schwarzentruber
Compare l’efficacité de cette façon d’implémenter la file de priorité avec ton implémentation
précédente. Que constates-tu ?

#### Résolution
[Voir pq_tasbinaire.c](cours2/code/pq_tasbinaire.c)

Compilation et exécution des tests (Tous les tests passent):
```
gcc -o test.out test.c pq_tasbinaire.c  && ./test.out
```

Avec la file de priorité implémentée par un tas binaire, la complexité de l'algorithme est réduite pour garder ordonnée les différents éléments lors d'un ajout. En effet, la complexité est `O(log n)` au lieu de `O(n²)` par rapport à un tableau qu'il faut ordonner complètement après chaque ajout. Par contre, il faut également ordonner avec une complexité `O(log n)` lorsqu'une valeur est retirée alors que le précédent algorithme à une complexité `O(1)` dans cette situation car le tableau reste ordonné. 
Par rapport à la complexité spatiale, l'espace mémoire croit de façon linéaire par rapport à la taille de la file de priorité donc une complexité `O(n)`.

#### Objectifs rencontrés
* 9-Créer et manipuler des fonctions qui prennent en argument d’autres fonctions
* 10-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

## 2 Programme de suggestion de livre

#### Exercice
>Écris un programme C qui permette à un utilisateur, une fois lancé, d’encoder des livres (titre,
année, nombre de pages), de demander une suggestion (livre le plus récent qui contient le moins de
pages) et de quitter le programme. Implémentez ça au moyen d’une file de priorité.
Bonus : trouvez un moyen pour que les livres qui sont dans la bibliothèque depuis un certain temps
acquièrent de la priorité au fur et à mesure du temps. Peut-être en ajoutant une valeur de priorité à
chaque livre basée sur l’année et le nombre de pages, et qui est modifiée à chaque fois qu’un
nouveau livre est ajouté pour le rendre de plus en plus prioritaire.

#### Résolution
[Voir bibliotheque.c](cours2/code/bibliotheque.c)

```
gcc -o bibliotheque.out bibliotheque.c pq_tasbinaire.c  && ./bibliotheque.out
```

#### Objectifs rencontrés
* 12-Utiliser l’ADT "file de priorité" pour résoudre des problèmes concrets en C

## Auto-Evaluation de la séance
Quatres difficultés significatives ont été rencontrés lors des implémentations.
1. Comment agrandir et rétrécir un tableau avec une allocation dynamique de mémoire ? 
2. Comment enlever le premier élément d'un tableau ?
3. Comment ajouter un élément à la dernière position d'un tas binaire étant donné qu'on se fait une représentation sous forme d'arbre ?
4. Comment entrer des titres de film comprenant des blancs par interaction avec la console ?

### 1. Comment agrandir et rétrécir un tableau avec une allocation dynamique de mémoire ?
Dans ce cas-ci, j'ai décidé d'avoir une taille standard de tableau de 100 entiers. Cette limite est implémentée via le champ `cap` (pour capacité) de la fille de priorité. Lors de l'addition, je prévois un `realloc` vers une nouvelle structure augmentée de 100 entiers (`cap`+100) si la taille du tableau (nombre d'éléments "actifs") dépasse la capacité de celui-ci.
Lors d'un `serve`, si la taille du tableau franchit la limite inférieur (multiple de 100), alors il y a une reallocation en mémoire et l'offset (voir 2.) est remis à 0. 

### 2. Comment enlever le premier élément d'un tableau ?
Lors d'un ``serve``, le premier élément du tableau est enlevé. Pour ne pas changer de tableau à chaque fois que cette opération est répétée (et gardé une complexité constante), j'ai décidé d'ajouter un champ `offset` afin de déterminer le début de la partie "active" du tableau. Dès lors, lors d'un ``serve``, la taille du tableau (i.e. nombres d'éléments actifs) est réduite de 1 et l'offset est incrémenté de 1. Le dernier élément reste inchangé. Lors d'un agrandissement ou rétrécissement du tableau l'``offset`` est remis à 0. 

### 3. Comment ajouter un élément à la dernière position d'un tas binaire étant donné qu'on se fait une représentation sous forme d'arbre ?
Suite à la lecture de la vidéo, je visualisais le tas binaire comme un arbre composé de noeuds indépendamment alloué dans la mémoire et ayant chacun un parent et deux enfants. Dès lors, je ne comprenais comment retrouver le dernier emplacement "libre" de la structure qui est utile pour les manipulations de la structure. J'ai imaginé utilisé le nombre entier indiquant taille du tableau décomposé en bits et chaque bit indiquerait s'il faut aller à gauche si 0 ou à droite si 1 : soit assez difficile à mettre en place. Puis, en parcourant plus ample documentation, j'ai lu qu'un tas binaire pouvait être implémenté sous forme d'un tableau dans lequel on peut retrouver l'index du parent et de l'enfant grâce à une équation mathématique (``left = 2*parent+1; right = 2*parent+2; parent = (child-1)/2;``). Le dernier emplacement libre étant celui à l'index représentant l'ancienne taille du tableau (tableau avec 5 éléments + 1 élément --> dernier élément placé à l'index 5).

### 4. Comment entrer des titres de film comprenant des blancs par interaction avec la console ?
Dans l'exercice de la bibliothèque, j'ai été confrontés à de nombreuses erreurs de segmentation dans le cas où les titres de film comprenait des espaces blancs. En effet, ``scanf`` ne supporte pas les espaces et j'ai utilisé la fonction `fgets`. Cependant, la fonction `fgets` n'est pas suffisante pour entrer des titres avec des blancs. 
Il faut également remplacé le dernier retour de ligne par un caractère nul `\0`.
Puis, il faut également nettoyé le tampon d'entrée console après sa première utilisation sinon un caractère de retour de ligne peut corrompre la chaîne de caractère.

## Notes en vracs

### [ Prof ] Exemple de chaine circulaire doublement chainée
[Voir code](cours2/liste%20chainee%20double.c) 

* `->` est synonyme de `(*tete).taille`

Lors de la première itération, on crée deux éléments distincts.

1. Head: ayant pour champ: first and last
2. node: ayant pour champ: next and prev

### Comprendre la priority queue

Une priority queue est une structure de données où chaque élément a une priorité associée, et les éléments sont servis en fonction de leur priorité. L'élément avec la plus haute priorité est toujours retiré en premier. 

Ex: tache prioritaire qui doit être processée par CPU

Voici comment comprendre ses spécifications :

Insertion (Insert) :
* Description : Ajoute un nouvel élément avec une priorité donnée à la file.

Suppression (Delete ou Remove) :
* Description : Retire l'élément avec la plus haute priorité.

Consultation (Peek ou Top) :
* Description : Permet de voir l'élément avec la plus haute priorité sans le retirer.

Taille (Size) :
* Description : Renvoie le nombre d'éléments dans la file.

Est vide (IsEmpty) :
* Description : Vérifie si la file est vide.

**Explication des paramètres**

* int (*leq)(int, int) : Il s'agit d'un pointeur vers une fonction de comparaison. Cette fonction prend deux entiers en entrée et retourne un entier. Elle est utilisée pour définir la relation d'ordre entre les éléments de la file de priorité. Typiquement, cette fonction retourne :
  * Un nombre négatif si le premier élément a une priorité inférieure au second.
  * Zéro si les deux éléments ont la même priorité.
  * Un nombre positif si le premier élément a une priorité supérieure au second.

**Retour de la fonction**

* PQ_t : La fonction retourne un pointeur vers une structure PQ (file de priorité). Ce pointeur représente la file de priorité initialisée.
  
**Préconditions et Postconditions**

* Préconditions : Aucune précondition spécifique n'est requise pour appeler cette fonction.
* Postconditions : La fonction initialise une file de priorité vide avec la relation d'ordre spécifiée par la fonction de comparaison leq.

### [ Prof ] Notion de Complexité

Complexité est un tradeoff entre différente fonction
ex: 
* complexité pour implémentation avec tableau non trié: O(n) car il faut parcourir le tableau pour trouver l'élément le plus prioritaire
* Si tableau trié alors moins de complexité mais l'ajout d'un élément nécessite de faire un sorting

### [ Prof ] Tas binaire

Arbre où chaque parent a 2 enfants. La valeur (priorité) des parents est plus élevée que celles des enfants. 