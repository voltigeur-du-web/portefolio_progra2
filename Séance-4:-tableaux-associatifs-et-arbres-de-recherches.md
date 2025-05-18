
- [1. ADT Dictionnaire / Tableau associatif](#1-adt-dictionnaire--tableau-associatif)
  - [1.1 Opération sur un tableau associatif](#11-opération-sur-un-tableau-associatif)
    - [Exercice](#exercice)
    - [Résolution](#résolution)
    - [Objectifs rencontrés](#objectifs-rencontrés)
  - [1.2 Définition formelle du T.A.](#12-définition-formelle-du-ta)
    - [Exercice](#exercice-1)
    - [Résolution](#résolution-1)
    - [Objectifs rencontrés](#objectifs-rencontrés-1)
  - [1.3 Tests du tableau associatif](#13-tests-du-tableau-associatif)
    - [Exercice](#exercice-2)
    - [Résolution](#résolution-2)
    - [Objectifs rencontrés](#objectifs-rencontrés-2)
- [2. Arbre binaire de recherche](#2-arbre-binaire-de-recherche)
  - [2.1. Implémenter un tableau associatif avec un arbre binaire de recherche](#21-implémenter-un-tableau-associatif-avec-un-arbre-binaire-de-recherche)
    - [Exercice](#exercice-3)
    - [Résolution](#résolution-3)
    - [Objectifs rencontrés](#objectifs-rencontrés-3)
  - [2.2 Complexité](#22-complexité)
    - [Exercice](#exercice-4)
    - [Résolution](#résolution-4)
    - [Objectifs rencontrés](#objectifs-rencontrés-4)
  - [2.3 Déséquilibre](#23-déséquilibre)
    - [Exercice](#exercice-5)
    - [Résolution](#résolution-5)
    - [Objectifs rencontrés](#objectifs-rencontrés-5)
  - [2.4.Rééquilibre et arbre AVL](#24rééquilibre-et-arbre-avl)
    - [Exercice](#exercice-6)
    - [Résolution](#résolution-6)
    - [Objectifs rencontrés](#objectifs-rencontrés-6)
  - [3. Annuaire](#3-annuaire)
    - [Exercice](#exercice-7)
    - [Résolution](#résolution-7)
    - [Objectifs rencontrés](#objectifs-rencontrés-7)
- [Auto-évaluation de la séance](#auto-évaluation-de-la-séance)
    - [Difficulté de l'implémentation et importance des tests unitaires](#difficulté-de-limplémentation-et-importance-des-tests-unitaires)
    - [Difficultés avec les entrées de string avec des whitespaces](#difficultés-avec-les-entrées-de-string-avec-des-whitespaces)
    - [Limitation dans la taille des numéros](#limitation-dans-la-taille-des-numéros)
- [Notes en vrac](#notes-en-vrac)
  - [\[ Prof \] Introductions](#-prof--introductions)
  - [\[ Prof \] Implémentation en arbre binaire de recherche](#-prof--implémentation-en-arbre-binaire-de-recherche)
    - [\[ Recherche \] Notes supplémentaires sur arbre AVL](#-recherche--notes-supplémentaires-sur-arbre-avl)
  - [\[ Perso / Recherche \] Opérateur ternaire en C](#-perso--recherche--opérateur-ternaire-en-c)


## 1. ADT Dictionnaire / Tableau associatif

### 1.1 Opération sur un tableau associatif
#### Exercice

> Définissez en français les 4 opérations qui peuvent être réalisées sur un tableau associatif : ajouter
> un élément (et une clé), rechercher un élément (par sa clé), supprimer un élément (par sa clé),
> modifier un élément (par sa clé). Définissez aussi des conditions qui devront toujours être
> respectées.

#### Résolution

* Créer dictionnaire
  * Pas de condition
  * Crée un T.A. vide (allocation mémoire)
* Détruire dictionnaire (T.A.)
  * Condition: un T.A. est initialisé (vide ou non)
  * Libère la mémoire de tous les éléments inclus dans le T.A. et le T.A. lui-même
* Ajouter(TA,[valeur d'entier,clé - chaîne de caractères])
  * Condition: un T.A. est initialisé (vide ou non) ; la clé n'existe pas dans le T.A.
  * Ajoute et ordonne par clé dans la structure T.A. une paire d'élément défini par un entier et une clé
* Rechercher (TA, clé)
  * Condition: un T.A. est initialisé non vide ; la clé existe dans le T.A.
  * Retourne la valeur de l'entier correspondant à sa clé (si celle-ci existe)
* Supprimer (TA, clé)
  * Condition: un T.A. est initialisé non vide ; la clé existe dans le T.A.
  * Enlève la paire [valeur d'entier,clé - chaîne de caractères] du T.A.
* Modifier (TA, [nouvelle valeur d'entier, clé - chaîne de caractères])
  * Condition: un T.A. est initialisé non vide ; la clé existe dans le T.A.
  * Modifie la valeur associée à une clé

#### Objectifs rencontrés
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières
* 15-Écrire une spécification formelle d’un nouvel ADT

### 1.2 Définition formelle du T.A.
#### Exercice
>À partir des définitions que vous avez données, et en vous inspirant des notations formelles >de la
>file d’attente et de la file de priorité que vous avez reçues lors des deux séances précédente,
>proposez votre définition formelle de l’ADT tableau associatif. Conseil : définissez-le comme un
>ensemble de couples (clé;valeur).

#### Résolution
* D est le dictionnaire à l'entrée de l'opération
* D' est le dictionnaire à la sortie de l'opération
* Object <Kv,V>
  *  V est l'élément à ajouter au dictionnaire
  *  Kv est la clé de l'élément

`create() -> DictType D'`
* **Pre:** True
* **Post:** ∃ D' and |D'|=0

`destroy(DictType D)`
* **Pre:** ∃ D
* **Post:** !∃ D'

`add(DictType D, DictEntryType <Kv,V>) -> DictType D'`
* **Pre:** ∃ D and D : ∀<Kx,X> \ {<Ky,Y> where Ky == Kv}
* **Post:** ∃ D' and D' : ∀<Kx,X> , ∃<Ky,Y> where Ky == Kv and Y==V

`research(DictType D, KeyType Kv) -> ValueType V`
* **Pre:** ∃ D and |D|>0 and D : ∀<Kx,X> , ∃<Ky,Y> where Ky == Kv
* **Post:** ∃ V : ∃<Ky,Y> ∈ D' where Ky == Kv

`delete(DictType D, KeyType Kv) -> DictType D'`
*** Pre:** ∃ D and |D|>0 and D : ∀<Kx,X> , ∃<Ky,Y> where Ky == Kv
*** Post:** ∃ D' and D' : ∀<Kx,X> \ {<Ky,Y> where Ky == Kv}

`modify(DictType D, DictEntryType <Kv,V>) -> DictType D'`
* **Pre**: ∃ D and |D|>0 and D : ∀<Kx,X>, ∃<Ky,Y> where Ky == Kv
* **Post:** ∃ D' and |D'|>0 and D' : ∀<Kx,X> , ∃<Ky,Y> where Ky == Kv and Y==V

#### Objectifs rencontrés
* 15-Écrire une spécification formelle d’un nouvel ADT

### 1.3 Tests du tableau associatif 
#### Exercice
>Écrivez un fichier .h qui reprend les fonctions que vous avez définies précédemment. Écrivez 
également un fichier C dans lequel vous définissez une fonction de test, qui teste différentes 
utilisations des opérations définies précédemment pour vérifier que votre implémentation future 
fonctionne correctement.

#### Résolution
Voir [header](cours4/code/Dict.h)
Voir [tests](cours4/code/tests_Dict_arbre-binaire-simple.c)

#### Objectifs rencontrés
* 3-Comprendre la différence entre les fichiers .c et les fichier d’entête .h et être capables, lors de l’écriture d’un programme, de jongler entre les deux
* 11-Étre capable d’écrire une suite de tests simples pour tester l’implémentation d’un ADT.

## 2. Arbre binaire de recherche

### 2.1. Implémenter un tableau associatif avec un arbre binaire de recherche
#### Exercice
> Définissez la structure arbre binaire de recherche telle que présentée ci-dessus, définissez une
> structure dictionnaire qui contient un pointeur vers la racine de l’arbre binaire de recherche, puis
> implémentez les 4 opérations du tableau associatif (ainsi qu’une fonction pour créer un nouveau
> tableau associatif et une fonction pour supprimer le tableau associatif et libérer la mémoire allouée).

#### Résolution
Voir [Dict_arbre-binaire-simple.c](cours4/code/Dict_arbre-binaire-simple.c)

Notez qu'il existe des fonction auxiliaires communes avec les fonction d'équilibrage d'arbre présent dans [utils_Dict.c](cours4/code/utils_Dict.c)

Compilation et exécution des tests (tous les tests passent)
````
gcc -o tests_Dict_arbre-binaire-simple.out tests_Dict_arbre-binaire-simple.c Dict_arbre-binaire-simple.c utils_Dict.c && ./tests_Dict_arbre-binaire-simple.out
````

#### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

### 2.2 Complexité
#### Exercice
> Idéalement, combien d’opérations dans le pire des cas devrait-ont faire pour chacune des opérations
> sur un tableau associatif implémenté au moyen d’un arbre binaire, en fonction du nombre de nœuds
> dans l’arbre (n) ? Imaginez que vous arbre binaire est complet et parfaitement équilibré.
#### Résolution
Pour un arbre équilibré, il faut une complexité ~ logarithme 2 de n+1 pour effectuer une recherche. Par exemple, un arbre complet et équilibré comprenant 15 éléments a 4 niveau dans lesquels chercher. 
#### Objectifs rencontrés
* 16-Comprendre et employer un arbre binaire de recherche équilibré

### 2.3 Déséquilibre
#### Exercice
> Représentez, sur un dessin, la suite d’opérations suivantes : nouvel arbre, insérer(‘g’, 4),
> insérer(‘f’,5), insérer (‘e’, 8), insérer (‘d’, 10), insérer(‘b’,11), insérer(‘a’,15). Que remarquez-vous ? Est-ce que l’arbre créé est toujours aussi efficace ?
> 
#### Résolution
```
          (‘g’, 4)
          /
        (‘f’, 5)
        /
      (‘e’, 8)
      /
    (‘d’, 10)
    /
  (‘b’,11)
  /
(‘a’,15)
```
Non car ici à chaque insertion s'ajoute à la branche gauche. Au final, l'arbre a 6 niveaux pour ses 6 éléments. La complexité est `O(n)` au lien de `O(log(n))`.

#### Objectifs rencontrés
* 16-Comprendre et employer un arbre binaire de recherche équilibré

### 2.4.Rééquilibre et arbre AVL
#### Exercice
>Pour maintenir un équilibre sur un arbre binaire, une manière consiste à faire en sorte qu’il n’y ait 
pas une différence de hauteur1 de plus de 2 entre les deux enfants d’un nœud. On appelle ça un arbre
AVL. Quand c’est le cas, il y a une rotation gauche ou droite (si la différence est positive ou 
négative) qui doit s’effectuer pour rétablir l’équilibre :
Ça implique que chaque nœud contient un champ indiquant sa hauteur et qu’à chaque opération 
d’ajout, de suppression et de rotation, on recalcule la hauteur de certains nœuds.
Modifiez votre arbre binaire de recherche pour garantir qu’il soit toujours équilibré.
3.Annuaire
Écrivez un programme qui vous permet soit d’encoder une nouvelle personne (nom et numéro de 
téléphone), soit de trouver un numéro à partir d’un nom, soit de supprimer quelqu’un, soit de 
modifier le numéro à partir d’un nom donné. Faites usage d’un tableau associatif comme défini 
précédemment.
1 Nombre de nœuds sur le plus long chemin entre un nœud et une feuille (extrémité) de l’arbre.
Ça implique que chaque nœud contient un champ indiquant sa hauteur et qu’à chaque opération 
d’ajout, de suppression et de rotation, on recalcule la hauteur de certains nœuds.
Modifiez votre arbre binaire de recherche pour garantir qu’il soit toujours équilibré.

#### Résolution
Voir fonction ``balance_tree`` dans [utils_Dict_balance.c](cours4/code/utils_Dict_balance.c)

Compilation et exécution des tests (notamment sur les fonctions auxiliaires d'équilibrage)
````
gcc -o tests_Dict_balance.out tests_Dict_balance.c Dict_arbre-binaire-simple.c utils_Dict_balance.c utils_Dict.c && ./tests_Dict_balance.out
````

#### Objectifs rencontrés
* 11-Être capable d’écrire une suite de tests simples pour tester l’implémentation d’un ADT.
* 16-Comprendre et employer un arbre binaire de recherche équilibré



### 3. Annuaire
#### Exercice
>Écrivez un programme qui vous permet soit d’encoder une nouvelle personne (nom et numéro de 
téléphone), soit de trouver un numéro à partir d’un nom, soit de supprimer quelqu’un, soit de 
modifier le numéro à partir d’un nom donné. Faites usage d’un tableau associatif comme défini 
précédemment.

#### Résolution
Voir [annuaire.c](cours4/code/annuaire.c)

Compilation et exécution des tests (notamment sur les fonctions auxiliaires d'équilibrage)
````
gcc -o annuaire.out annuaire.c Dict_arbre-binaire-simple.c utils_Dict_balance.c utils_Dict.c && ./annuaire.out
````

#### Objectifs rencontrés
* 17-Utiliser l’ADT "tableau associatif" pour résoudre des problèmes concrets en C

## Auto-évaluation de la séance

#### Difficulté de l'implémentation et importance des tests unitaires
La fonction `balance_tree` se base sur un fonction récursive `balance_node` qui parcours l'arbre de la racine aux feuilles et met à jour les hauteurs à chaque rotation de noeuds. 

Ma première approche était de partir des feuilles et de remonter vers la racine. Pour cela, j'utilisais une file de priorité où la priorité était la hauteur du noeud et la valeur était le pointeur du noeud (Voir [implémentation](cours4/code/pq_tasbinaire_pointeur.c)). En effet, une PQ était attachée à tree->order. Une deuxième PQ temporaire servait à récupérer temporairement les noeuds déjà triés. Lors de l'ajout ou du retrait d'un élément de l'arbre, la PQ tree->order devait également se mettre à jour.

Vu la complexité de l'implementation, j'ai attaché une importance aux tests où l'implémentation de la PQ était testé [ici](cours4/code/tests_priority_queue_pointeur.c) et l'implémentation de l'arbre avec correction de l'équilibre est testée [ici](cours4/code/tests_Dict_balance.c).

Cependant, dans cette approche, j'ai été confronté à des problèmes de segmentation fault. Au lieu de partir des feuilles, l'utilisation d'une fonction récursive en partant de la racine m'a permis d'obtenir l'effet attendu.

La complexité réside dans l'implémentation de la donnée abstraite Dictionnaire. Ici, le code de `annuaire.c` permet d'effectuer des entrées de chaîne de caractère et d'entier par la console.

#### Difficultés avec les entrées de string avec des whitespaces

Dans ce cas, l'utilisation de la fonction scanf n'est pas adaptée. Dès lors, j'utilise la fonction `fgets(key, sizeof(key), stdin)` de la library `string.h`. Cependant, celle-ci prend également le charactère de retour de ligne `\n` dans la chaine de caractère. Il faut donc enlever ce caractère par `key[strcspn(key,"\n")]='\0'` où `strcspn` retourne le nombre de caractère du string `key` sauf cceux mentionné dans le 2 argument `\n`.

####  Limitation dans la taille des numéros

Vu que le dictionnaire a été implémenté en se basant sur des entiers, on est limité avec des numéro de téléphone allant de 0 à (2^31)-1. Pour étendre cette limite, il faut utiliser des types `long long int` dans la structure de l'annuaire et de l'implémentation du dictionaire par arbre de recherche binaire.

## Notes en vrac

### [ Prof ] Introductions 

Ensemble de couples clé-valeur. Chaque clé a exactement une valeur.

Conditions:
* Une clé doit être unique

Opérations:
* Créer() -> -
* Ajouter un couple clé-valeur
* Rechercher (clé) -> valeur
* supprimer (clé) -> -
* modifier (clé, nouvelle valeur)

Header:
* add(Dict, key, value) -> Dict U (key, value)
  * Vérifier que la clé n'existe psa déjà
  * Sinon ancien dictionnaire est retourné

Décision arbitraire:
* type clé = string
* type valeur = int

On utilise `const`pour éviter de modifier le char `*` key

### [ Prof ] Implémentation en arbre binaire de recherche
* Racine
  * Noeuds
    * Feuilles

Chaque noeud de l'arbre contient un couple clé - valeur
* L'enfant de gauche a sa clé qui est  plus petit ou égal à la clé du parent (ordre lexicographique)
* L'enfant de droite a sa clé qui est plus grand ou égal à clé de l'enfant (ordre lexicographique)

Si une branche de l'arbre est plus remplie alors l'arbre est déséquilibré. On considère un déséquilibre lorsque la hauteur d'un arbre entre deux branches "siblings" dépasse 2. 

La hauteur d'une branche étant le nombre de noeud jusqu'au branche.

Voir [implémentation](cours4/deprecate/Dict_balance.c)

#### [ Recherche ] Notes supplémentaires sur arbre AVL
Un arbre AVL est un type d'arbre binaire de recherche auto-équilibré. Il a été nommé d'après ses inventeurs, Georgy Adelson-Velsky et Evgenii Landis, qui l'ont décrit pour la première fois en 1962. La particularité d'un arbre AVL est qu'il maintient automatiquement sa hauteur équilibrée, ce qui garantit que les opérations de recherche, d'insertion et de suppression s'effectuent en temps logarithmique 
O(log n), où n est le nombre de nœuds dans l'arbre.

**Propriétés d'un Arbre AVL**
Propriété de l'arbre binaire de recherche : Pour chaque nœud, toutes les clés dans le sous-arbre gauche sont inférieures à la clé du nœud, et toutes les clés dans le sous-arbre droit sont supérieures à la clé du nœud.
Propriété d'équilibre : Pour chaque nœud, la différence de hauteur entre ses sous-arbres gauche et droit (appelée facteur d'équilibre) est au plus 1. En d'autres termes, pour chaque nœud, la hauteur du sous-arbre gauche et la hauteur du sous-arbre droit diffèrent d'au plus 1.

**Facteur d'Équilibre**
Le facteur d'équilibre d'un nœud est défini comme la différence entre la hauteur de son sous-arbre gauche et la hauteur de son sous-arbre droit :

`Facteur d’équilibre  = Hauteur(sous-arbre gauche) − Hauteur(sous-arbre droit)`

Pour un arbre AVL, le facteur d'équilibre de chaque nœud doit être -1, 0 ou 1.

**Rotations**
Pour maintenir l'équilibre de l'arbre après une insertion ou une suppression, des rotations sont effectuées. Les rotations sont des opérations locales qui réorganisent les nœuds pour rétablir l'équilibre. Il existe quatre types de rotations :

Rotation simple à gauche (LL Rotation)
Rotation simple à droite (RR Rotation)
Rotation double à gauche (LR Rotation)
Rotation double à droite (RL Rotation)

### [ Perso / Recherche ] Opérateur ternaire en C
L'expression return node ? node->height : 0; est une utilisation de l'opérateur ternaire en C. Cet opérateur permet de faire des choix conditionnels de manière concise. Voici une explication détaillée de cette expression
```
condition ? expression_si_vrai : expression_si_faux;
```
* condition : Une expression booléenne qui est évaluée.
* expression_si_vrai : L'expression qui est évaluée et retournée si condition est vraie.
* expression_si_faux : L'expression qui est évaluée et retournée si condition est fausse.