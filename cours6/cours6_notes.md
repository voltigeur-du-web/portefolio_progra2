# Cours 6

## Introduction

Complexité de façon théorique vs façon empirirque

1ere question: est-ce que l'algorythme se réduit

## 1. Tri à gobelet
### Exercice
>Inventé par Benoit Vleminckx, le tri par gobelet consiste, tant que le tableau n’est pas trié, à en 
permuter deux éléments sélectionnés au hasard.
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau 
et sa taille et qui renvoie le nombre de permutations qui ont été effectuées.
>- Détermine si cet algorithme se termine dans tous les cas.
>- Détermine l’évolution du nombre de permutations nécessaires pour trier ce tableau par rapport à la 
taille du tableau fourni en entrée.
>- Que conclure sur l’efficacité de cet algorithme ?

### Résolution
voir [implémentation](code/tri_gobelets.c)

Compilation et exécution du test de performance (NB: Dans la fonction [main](code/test_tri.c),bien mettre en commentaire les lignes avec les fonctions `sort` avec des tailles de tableau > 10).
```
gcc -o test_tri.out test_tri.c tri_gobelets.c && ./test_tri.out 
```

Le tri à gobelet peut ne pas se terminer pour des tableaux de grandes tailles. On voit déjà que le temps d'exécution moyen est de 36 secondes pour des tableau de taille 13.

Pour chaque élément ajoutés dans un tableau de taille restreinte (<=10), on voit une croissance de manière exponentielle du nombre de permutations.

Taille du tableau   | N. permutation moyen  | Temps exécution moyen |
|:----------        |---:                   |------------:          |
| 4                 | 40.2                  | 0.003 ms     |
| 5                 | 107.6                 | 0.004 ms     |
| 6                 | 708.6                 | 0.016 ms     |
| 7                 | 9430.2                | 0.18 ms     |
| 2                 | 26000.0               | 0.50 ms     |
| 9                 | 343138.6              | 6.3 ms     |
| 10                | 4667033.0             | 82.9 ms     |

C'est un algorithme inefficace qui nous servira de baseline.

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 2. Complexité d'un algorithme
### Exercice
>L’étude de la complexité d’un algorithme consiste à mesurer le temps (sous la forme d’un nombre 
d’opérations) que met un algorithme pour se terminer, en fonction de la taille du problème qu’il doit 
traiter. Quand on étudie la complexité, on cherche généralement à définir le comportement 
asymptotique de l’algorithme sur le pire des cas possible. Par exemple, si je fais une recherche 
simple dans un tableau de taille "n", élément par élément jusqu’à trouver celui que je cherche, dans 
le pire des cas je parcourrai les "n" éléments pour trouver celui que je cherche. On dit que la 
complexité est de O(n). Ça signifie que si la taille du tableau est de 10, il me faudra au pire 10 
opérations pour trouver ce que je cherche. Si la taille est de 50 il me faudra au pire 50 opérations 
pour le trouver.
Pour un algorithme de complexité O(n²), par exemple, si  la taille du problème est de 10, il me 
faudra au pire 100 opérations pour le résoudre. Si la taille du problème est de 50, il me faudra au 
pire 2500 opérations. L’augmentation n’est plus linéaire, mais quadratique !
Trouve des algorithmes simples qui correspondent aux classes de complexités usuelles suivantes : 
O(1), O(log(n)), O(n), O(n log(n)), O(n²), O(2n)

### Résolution
Trouver le nombre d'as dans un paquets de `n` cartes --> complexité d'ordre `O(n)`. On parle ici de complexité linéaire (comprend aussi des complexité d'ordre `O(2n)`).

Pour récupérer un élément dans un table de hachage bien équilibrée, le processus est réalisé dans un temps constant --> `O(1)`

Dans le cas d'un arbre de tri binaire, on parle de complexité logarithmique --> `O(log n)` plus performant que `O(n)`.

Les meilleurs algorithme de tri (Quick Sort) ont une complexité de `O(n * log n)`.

Un tri à bulle a une complexité quadratique: `O(n²)`.

Les algorithme de recherche de chemin (GPS de livreur) ont un complexité exponentiel: `O(2^n)`

La complexité du tri gobelet peut être caractérisé d'une complexité infinie.

### Objectifs rencontrés
* 22-Caractériser la complexité de différents algorithmes de tri

## 3. Tri à bulles
### Exercice
>Le tri par bulle consiste à parcourir deux à deux les éléments d’un tableau et à inverser ces éléments 
s’ils ne sont pas dans le bon ordre, jusqu’à arriver au dernier élément. Puis à recommencer, jusqu’à 
l’avant-dernier élément et ainsi de suite jusqu’à ce que le tableau soit trié.
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau 
et sa taille et qui renvoie le nombre de comparaisons qui ont été effectuées 
>- Détermine si cet algorithme se termine dans tous les cas
>- Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/tri_bulles.c)
  - Dépendance: [utils.c](code/utils.c)

Compilation et exécution
```
gcc -o test_tri.out test_tri.c tri_bulles.c utils.c && ./test_tri.out
```

Cet algorithme se termine théoriquement dans tous les cas.

La complexité de celui-ci est d'ordre quadratique: `O(n²)`. En effet, voici le nombre de fois que les éléments passent dans une boucle:
```
(n-1) + (n-2) + ... + 1 = (n-1)*n/2 (ou n-1 fois la moyenne n/2)
```

**Résultats:**

|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|6.00|0.000200 ms|
|5|10.00|0.000000 ms|
|6|15.00|0.000400 ms|
|7|21.00|0.001000 ms|
|8|28.00|0.001000 ms|
|9|36.00|0.000400 ms|
|10|45.00|0.000800 ms|
|11|55.00|0.000600 ms|
|12|66.00|0.000800 ms|
|13|78.00|0.000800 ms|
|14|91.00|0.000800 ms|
|15|105.00|0.001200 ms|
|16|120.00|0.001400 ms|
|32|496.00|0.002800 ms|
|64|2016.00|0.008000 ms|
|128|8128.00|0.027000 ms|
|256|32640.00|0.089400 ms|
|512|130816.00|0.322600 ms|

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 4. Tri par sélection
### Exercice
>Ce tri consiste à trouver le plus petit éléments du tableau et à le mettre au début, puis à trouver le 
deuxième plus petit et à le mettre en deuxième position etc, jusqu’à la fin.
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau 
et sa taille et qui renvoie le nombre de comparaisons qui ont été effectuées 
>- Détermine si cet algorithme se termine dans tous les cas
>- Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/tri_selection.c)
  - Dépendance: [utils.c](code/utils.c)

Compilation et exécution
```
gcc -o test_tri.out test_tri.c tri_selection.c utils.c && ./test_tri.out
```
Cet algorithme se termine théoriquement dans tous les cas.

Comme pour le tri à bulle, la complexité du tri par sélection est d'ordre quadratique: `O(n²)`. En effet, voici le nombre de fois que les éléments passent dans une boucle:
```
(n-1) + (n-2) + ... + 1 = (n-1)*n/2 (ou n-1 fois la moyenne n/2)
```

**Résultats:**

|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|6.00|0.000200 ms|
|5|10.00|0.000600 ms|
|6|15.00|0.001000 ms|
|7|21.00|0.000200 ms|
|8|28.00|0.001000 ms|
|9|36.00|0.001000 ms|
|10|45.00|0.001000 ms|
|11|55.00|0.001000 ms|
|12|66.00|0.008800 ms|
|13|78.00|0.000600 ms|
|14|91.00|0.000600 ms|
|15|105.00|0.000800 ms|
|16|120.00|0.000800 ms|
|32|496.00|0.001200 ms|
|64|2016.00|0.004200 ms|
|128|8128.00|0.012200 ms|
|256|32640.00|0.044400 ms|
|512|130816.00|0.153600 ms|

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 5. Tri par insertion
### Exercice
>Ce tri consiste à trier les deux premiers éléments, puis à insérer le 3e pour que les trois premier 
soient triés, puis à faire pareil pour les suivants jusqu’à la fin.
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau 
et sa taille et qui renvoie le nombre de comparaisons qui ont été effectuées 
>- Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/tri_insertion.c)

Compilation et exécution
```
gcc -o test_tri.out test_tri.c tri_insertion.c && ./test_tri.out
```
Cet algorithme se termine théoriquement dans tous les cas.

Comme le tri à bulle, la complexité du tri par insertion est d'ordre quadratique: `O(n²)`. En effet, voici le nombre de fois que les éléments passent dans une boucle:
```
1 + 2 + 3 + ... + (n-1) = (n-1)*n/2 (ou n-1 fois la moyenne n/2)
```

**Résultats:**

|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|3.60|0.000200 ms|
|5|5.40|0.000400 ms|
|6|8.00|0.000600 ms|
|7|10.60|0.000400 ms|
|8|13.40|0.000000 ms|
|9|22.60|0.000000 ms|
|10|25.60|0.000200 ms|
|11|28.00|0.001000 ms|
|12|28.40|0.000200 ms|
|13|35.80|0.000200 ms|
|14|41.80|0.001000 ms|
|15|50.00|0.001000 ms|
|16|54.80|0.000800 ms|
|32|272.60|0.001400 ms|
|64|1045.60|0.002400 ms|
|128|4022.80|0.007200 ms|
|256|16631.80|0.026000 ms|
|512|64324.80|0.095200 ms|

Cependant, les résultats empiriques semblent meilleurs que les deux algorithmes précédents. En effet, l'algorithme ici recule de la position de l'élément insérer jusqu'à trouver sa place. Vu que le tableau de base peut avoir des brides d'éléments triés, on gagne quelques comparaisons. Le tri à bulle et le tri par sélection implémenter ici peuvent être améliorer en ne continuant pas l'algorithme si le tableau est déjà trié.

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 6. Quick Sort
### Exercice
>Ce tri récursif consiste, si le tableau a une taille de 1, à renvoyer le tableau. Sinon, choisir un 
élément "p" qui sera le pivot. Placer tous les éléments du tableau plus petit que "p" à gauche de "p" 
et tous les éléments plus grands à droite. Puis réappliquer l’algorithme sur le sous-tableau à gauche 
de "p" et puis sur le sous-tableau à droite de "p".
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau, 
l’indice du premier élément du sous-tableau à trier, et l’indice du dernier élément du sous-tableau à 
trier, et qui renvoie le nombre de comparaisons qui ont été effectuées 
>- Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/quick_sort.c)
  - Dépendance: [utils.c](code/utils.c)

Compilation et exécution
```
gcc -o test_tri.out test_tri.c quick_sort.c utils.c && ./test_tri.out
```
Cet algorithme se termine théoriquement dans tous les cas. Voici sont fonctionnement à l'aide d'une fonction récursive:

1. Choisir un pivot (ex. 1 er nombre par défaut)
2. On va placer à gauche les nombres plus petit que le pivot
3. On va placer à droite les nombre plus grand que le pivot
4. On va prendre un autre pivot et on recommence
5. On s’arrête lorsqu'il y a plus qu'un nombre d'un coté d'un pivot

Cette algorithme a une complexité de `O(n * log(n))` en moyenne mais sa complexité peut s'élever à `O(n²)` dans le pire des cas.

**Résultats:**

|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|6.40|0.000400 ms|
|5|8.20|0.000200 ms|
|6|11.60|0.000000 ms|
|7|13.60|0.001000 ms|
|8|20.80|0.001000 ms|
|9|29.40|0.000800 ms|
|10|25.00|0.000800 ms|
|11|36.20|0.000800 ms|
|12|37.80|0.000600 ms|
|13|39.80|0.000800 ms|
|14|49.20|0.001000 ms|
|15|53.60|0.000800 ms|
|16|55.60|0.001200 ms|
|32|151.40|0.001800 ms|
|64|424.60|0.003800 ms|
|128|939.00|0.009800 ms|
|256|2354.00|0.029200 ms|
|512|5566.40|0.091200 ms|

On constate une nette diminution du nombre de permutations avec cette algorithme par rapport à un bubble sort. Soit près de 24 fois moins de permutations pour un tableau avec 512 éléments. Cela est dans le même ordre de grandeur que le rapport complexité bubble sort (approx. ``n²/2``) et quick sort (approx. ``n * log(n)``):
```
0.5 * n / log(n) = 256 / 9 = 28.4
```

Cependant, dans cette analyse empirique, je n'ai pas comptabilisé les boucles réalisées dans la fonction `swap_shift_right` dû à l'implémentation en forme de tableau. Sinon, le nombre de permutations est proche de 70000.

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 7. Tri fusion
### Exercice
>Ce tri récursif se base sur le fait que fusionner deux tableaux déjà triés est très peu complexe. Si le 
tableau a une taille de 1, il le renvoie. S’il a une taille plus grande que 1, il le coupe en deux, les trie 
séparément, puis fusionne les deux sous-tableaux triés.
>- Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau, 
l’indice du premier élément du sous-tableau à trier, et l’indice du dernier élément du sous-tableau à 
trier, et qui renvoie le nombre de comparaisons qui ont été effectuées 
>- Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/tri_fusion.c)
  - Dépendances: 
    - [queue_chaine.c](code/queue_chaine.c)
    - [listes_chainees.c](code/listes_chainees.c)

Compilation et exécution
```
gcc -o test_tri.out test_tri.c tri_fusion.c queue_chaine.c listes_chainees.c && ./test_tri.out
```
Cet algorithme se termine théoriquement dans tous les cas.

Comme pour le quick sort, sa complexité est de `O(n log n)` mais celle-ci ne dépend par du tri existant dans le tableau.  

**Résultats:**
|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|16.00|0.001600 ms|
|5|24.00|0.001400 ms|
|6|31.80|0.002000 ms|
|7|40.00|0.001800 ms|
|8|47.60|0.002200 ms|
|9|57.60|0.002400 ms|
|10|67.40|0.002800 ms|
|11|77.60|0.003400 ms|
|12|87.40|0.003600 ms|
|13|97.20|0.004000 ms|
|14|107.00|0.004200 ms|
|15|117.80|0.004600 ms|
|16|127.20|0.004600 ms|
|32|315.20|0.015000 ms|
|64|752.00|0.029000 ms|
|128|1735.40|0.077600 ms|
|256|3913.20|0.236400 ms|
|512|8685.60|0.759800 ms|

On reste dans le même ordre de grandeur que le quick sort. Cependant, je n'ai pas comptabilisé ``2 x n`` transvasements du tableau vers une file et vice-versa qui sont propres à mon implémentation.

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## 8. Tri par tas
### Exercice
>Il s’agit d’un tri qui emploie une file de priorité implémentée au moyen d’un tas binaire (binary 
heap). Il consiste simplement à créer une nouvelle file de priorité de puis à y ajouter un à un les 
éléments du tableau à trier. Par définition, les éléments seront ainsi accessible de façon ordonnée 
depuis la file de priorité et peuvent être remis dans le tableau dans l’ordre.
> -Implémente cet algorithme de tri sous la forme d’une fonction qui prend en arguments un tableau 
et sa taille et qui renvoie le nombre de comparaisons qui ont été effectuées 
> -Détermine la complexité algorithmique de cet algorithme
>- Évalue expérimentalement sa complexité moyenne (en nombre de comparaisons effectuées)

### Résolution
- Voir [implémentation](code/tri_pq.c)
  - Dépendance: [pq_tasbinaire.c](code/pq_tasbinaire.c) modifié pour incorporer le ``counter`` de manipulation de données

Compilation et exécution
```
gcc -o test_tri.out test_tri.c tri_pq.c pq_tasbinaire.c && ./test_tri.out
```
Cet algorithme se termine théoriquement dans tous les cas.
Comme pour le tri-fusion, sa complexité théorique est de `O(n log n)`.

**Résultats:**

|Taille du tableau|N. permutations moyen|Temps exécution moyen|
|:----------------|--------------------:|--------------------:|
|4|9.40|0.001400 ms|
|5|13.80|0.000800 ms|
|6|18.00|0.000600 ms|
|7|22.20|0.001000 ms|
|8|29.20|0.001000 ms|
|9|35.60|0.001000 ms|
|10|41.80|0.001200 ms|
|11|48.00|0.001200 ms|
|12|54.00|0.001400 ms|
|13|61.00|0.001200 ms|
|14|67.40|0.001400 ms|
|15|73.20|0.001400 ms|
|16|83.40|0.002200 ms|
|32|217.40|0.003400 ms|
|64|553.60|0.007400 ms|
|128|1346.60|0.017000 ms|
|256|3187.00|0.036800 ms|
|512|7382.20|0.081400 ms|

On voit de façon empirique que cette algorithme est dans la même classe d'efficacité que les algorithmes quick sort et tri-fusion.

On constate également que le bubble sort, tri par insertion et tri par sélection, sont une classe d'algorithme moins efficace par rapport à ceux mentionnés précédemment. 

### Objectifs rencontrés
* 21-Implémenter différents algorithmes de tri en C
* 22-Caractériser la complexité de différents algorithmes de tri

## Auto-évaluation de la séance
### Problème des grands nombres
Dans le cas du tri à gobelets, le nombre de permutations pouvaient être trop élevées pour être afficher grâce à des entiers. J'ai choisi d'utiliser des "big int" non signés (`unsigned long long int`) pour pouvoir compter les larges nombres de permutations.

### Garder le même fichier de test
Pour garder le même fichier de test, j'ai choisi de créer la fonction de tri universelle (voir [tri.h](code/tri.h)) comme `sort(int* tab, int size);`. De cette façon, je peux garder le même fichier de test (voir [test_tri.c](code/test_tri.c)) qui génère le nombre de permutation par jeu de données. L'output dans la console a juste besoin d'être copier-coller pour être directement intégré comme tableau dans mon fichier markdown.

Par ailleurs, j'ai placer des fonctions utiles comme `swap` à travers plusieurs algorithme de tri dans le fichier [utils.c](code/utils.c) qui peut être compilé avec le fichier ``.c`` comprenant l'algorithme de tri et [test_tri.c](code/test_tri.c) avec les données de tests.

### Tri-fusion grâce au file
Pour ne pas à devoir gérer les index pour le placement des éléments dans les nouvelle tables avec le tri-fusion, j'ai choisi d'utiliser un ADT vu précédemment : la file (queue).
De cette façon là, on est dans une implémentation familière.

### Debugage de mon implémentation du tas binaire
Utiliser les différentes données de tests appliqué au tri pas tas m'ont permis de déceler des problèmes de segmentation causée par des conditions manquantes dans la fonction `order_lineage_down` de [pq_tasbinaire.c](code/pq_tasbinaire.c). J'en ai profité pour ajouter ces données à mes tests dans la deuxième séance.

### Quick-Sort : le prix de l'élégance
L'algorithme qui a été le plus élégant (et efficace) à implémenter est le quick sort. L'implémentation a été rendue possible par 3 petites fonctions:
* `swap_shift_right`: Permet de placer de décaler tous les nombres du pivot jusqu'à l'index d'un nombre qui a été déplacé avant le pivot car plus petit.
* `quick_sort` est une fonction récursive qui permet de définir le pivot, de placer les nombres à leur bonne place (plus petit avant le pivot et plus grand après celui-ci). Ensuite, de plus petits tableau issus de la division à l'endroit du pivot sont également trié en faisant un nouvel appel à cette fonction récursivement.
* `sort` permet d'initialiser le compteur de permutation, de garder une structure commune à toutes les fonctions de tris et à effectuer le premier appel à `quick_sort`