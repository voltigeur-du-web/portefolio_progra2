# Cours 6

## Introduction

Complexité de façon théorique vs façon empirirque

1ere question: est-ce que l'algorythme se réduit

## 1. Tri à gobelet

On permute deux chiffre aux hasard.

[voir tri_gobelet.c](code/tri_gobelets.c)

Pas efficace.

* Tableau de 5: 153
* Tableau de 5: 44
* Tableau de 6: 2986
* Tableau de 7: 13997
* Tableau de 8: 13997
* Tableau de 9: 137934
* Tableau de 10: 5*10⁶

Ici complexité exponentiel.

## 2. Complexité

Trouver le nombre d'as dans un paquets de `n` cartes --> complexité d'ordre `O(n)`. On parle ici de complexité linéaire (comprend aussi des complexité d'ordre `O(2n)`).

Pour récupérer un élément dans un table de hashage bien équilibrée, ole processus est réalisé dans un temps constant --> `O(1)`

Dans le cas d'un arbre de tri binaire, on parle de complexité logarithmique --> `O(log n)` plus performant que `O(n)`.

Les meilleurs algorithme de tri font `O(n * log n)`.

Un tri à bulle est une complexité quadratique: `O(n²)`.

Les algorithme de recherche de chemin (GPS de livreur) ont un complexité exponentiel: `O(2^n)`

La complexité du tri gobelet peut avoir une complexité infinie.


## 3. Tri à bulles

Complexité de `O(n²)` 

## 4. Tri par sélection

Nombre de répétition pour trouver le minimum: n + (n-1) + (n-2) + (n-3) + ... = (n(n-1))/2

Complexité de `O(n²)` 

## 5. Tri par insertion

En utilisant un tableau et tri par insertion, on obtient `(1/6)*n*(n+1)*(2n+1)`.

Complexité de `O(n³)`.

## 6. Quick Sort

1. Choisir un pivot (ex. 1 er nombre par défaut)
2. On va placer à gauche les nombres plus petit que le pivot
3. On va placer à droite les nombre plus grand que le pivot
4. On va prendre un autre pivot et on recommence
5. On s'arrete lorsqu'il y a un nombre d'un coté d'un pivot

C'est un algorithme récurssif



## 8. Tri par tas

On utilise un tas binaire pour faire un tri. On sera en complexité `O(log n)`