# Séance 6: tables de hachage

- [Séance 6: tables de hachage](#séance-6-tables-de-hachage)
  - [1. Théorie sur la table de hachage](#1-théorie-sur-la-table-de-hachage)
    - [1.1. Insérer un élément dans une table de hachage](#11-insérer-un-élément-dans-une-table-de-hachage)
      - [Exercice](#exercice)
      - [Résolution](#résolution)
      - [Objectifs rencontrés](#objectifs-rencontrés)
    - [1.2. Récupérer un élément dans une table de hachage](#12-récupérer-un-élément-dans-une-table-de-hachage)
      - [Exercice](#exercice-1)
      - [Résolution](#résolution-1)
      - [Objectifs rencontrés](#objectifs-rencontrés-1)
    - [1.3. Importance de la fonction de hachage](#13-importance-de-la-fonction-de-hachage)
      - [Exercice](#exercice-2)
      - [Résolution](#résolution-2)
      - [Objectifs rencontrés](#objectifs-rencontrés-2)
    - [1.4. Complexité des opérations](#14-complexité-des-opérations)
      - [Exercice](#exercice-3)
      - [Résolution](#résolution-3)
      - [Objectifs rencontrés](#objectifs-rencontrés-3)
  - [2. Implémentation d'un tableau associatif](#2-implémentation-dun-tableau-associatif)
    - [2.1. Table de Hachage](#21-table-de-hachage)
      - [Exercice](#exercice-4)
      - [Résolution](#résolution-4)
      - [Objectifs rencontrés](#objectifs-rencontrés-4)
    - [2.2. Tableau associatif](#22-tableau-associatif)
      - [Exercice](#exercice-5)
      - [Résolution](#résolution-5)
      - [Objectifs rencontrés](#objectifs-rencontrés-5)
  - [3. Lecture de fichiers](#3-lecture-de-fichiers)
    - [3.1. Ouvrir et lire un fichiers](#31-ouvrir-et-lire-un-fichiers)
      - [Exercice](#exercice-6)
      - [Résolution](#résolution-6)
      - [Objectifs rencontrés](#objectifs-rencontrés-6)
    - [3.2. Lister les mots d'un texte](#32-lister-les-mots-dun-texte)
      - [Exercice](#exercice-7)
      - [Résolution](#résolution-7)
      - [Objectifs rencontrés](#objectifs-rencontrés-7)
  - [Auto-évaluation de la séance](#auto-évaluation-de-la-séance)
      - [Fonction de hachage avec valeur aléatoire à chaque position](#fonction-de-hachage-avec-valeur-aléatoire-à-chaque-position)
      - [Problème de la taille de ligne](#problème-de-la-taille-de-ligne)
      - [Segmentation fault lors du traitement de Nana.txt](#segmentation-fault-lors-du-traitement-de-nanatxt)
  - [Notes en vrac](#notes-en-vrac)
      - [\[Prof\] Table de hachage](#prof-table-de-hachage)
      - [\[Prof\] Tips sur l'allocation de chaine de caractère](#prof-tips-sur-lallocation-de-chaine-de-caractère)
      - [\[ Recherche \] ``gets`` vs ``fgets``](#-recherche--gets-vs-fgets)
      - [\[ Recherche \] Divers](#-recherche--divers)


## 1. Théorie sur la table de hachage

### 1.1. Insérer un élément dans une table de hachage
#### Exercice
>Dessine et explique l’ajout successif des éléments (clé, valeur) suivants : (luc, 29), (ced, 36), (tom, 35),(io,40),(seb,39). Quel problème se pose ? Comment pourrais-tu le résoudre ? Propose deux solutions : une basée sur le "chainage", et une basée sur "l’adressage ouvert". 
Puis explique le concept de "taux de remplissage".

#### Résolution
**Problème des collisions**
* hachage(luc) = (108 + 117 + 99) % 10 = 324 % 10 = 4
* hachage(ced) = (99 + 101 + 100) % 10 = 300 % 10 = 0
* hachage(tom) = (116 + 111 + 109) % 10 = 336 % 10 = 6
* hachage(io) = (105 + 111) % 10 = 216 % 10 = 6
* hachage(seb) = (115 + 101 + 98) % 10 = 314 % 10 = 4

Lorsqu'on résout le hachage de ces différentes clés, on se rend compte qu'il y a 2 collisions car luc et seb occupent l'index 4 tandis que tom et io occupent tous les 2 l'index 6. Dès lors, on risque de ne pas avoir assez de place pour tous les paires (clé,valeur) à entrer.

**Solution avec chaînage**

Pour éviter le refus d'insertion dans une table de hachage en cas de collision (i.e. deux clé partageant le même index), on peut implémenter une liste simplement chaînée. De ce fait, le premier élément avec l'index serait l'`head` de la liste chaînée tandis que le second serait juste ajoutée à la liste chaînée. 

Le taux de remplissage est la proportion du nombre d'index utilisé sur le nombre total d'index disponible. Avec cette méthode de chaînage, le taux de remplissage n'est pas à garder à vue que la table est peut être étendue pour chaque index. Par contre, la complexité ne sera plus constante mais égale à la taille des chaines.

**Solution avec adressage ouvert**

Contrairement à la solution avec chaînage, l'adressage ouvert permet de stocker les collisions directement dans la table de hachage à une position libre. Pour cette implémentation, le taux de remplissage de la table est à garder à vue car il faut pouvoir étendre la table si un seuil de remplissage pré-défini est dépassé (typiquement 2/3).

Agrandir la table si celle-ci dépasse le taux de remplissage serait assez complexe car il faut:
- Étendre l'allocation de la table en mémoire
- Changer la fonction de hachage
- Réattribuer change entrée de la table actuel dans la nouvelle table 

#### Objectifs rencontrés
* 18-Comprendre le fonctionnement d’une table de hachage 

### 1.2. Récupérer un élément dans une table de hachage
#### Exercice
>Explique comment se passe la récupération d’un élément dans la table de hachage, pour les deux
solutions que tu as proposées à la question précédente.

#### Résolution
**Solution avec chaînage**

Pour récupérer un élément déterminé par sa clé, on utilise la fonction de hachage pour retrouver l'index de la table correspondant. Puis, on parcours la liste chaînée jusqu'à trouver la clé. Si la clé n'est pas trouvée dans la liste, alors elle n'existe pas dans l'entièreté de la table de hachage.

**Solution avec adressage ouvert**

Comme précédemment, on utilise la fonction de hachage pour retrouver l'index de la table correspondant. A partir de cette index, on va parcourir les index suivants à la recherche de la clé jusqu'au premier emplacement libre où emplacement ayant cette clé. Il se peut que l'on doive revenir au début de la table pour continuer la recherche si le dernier index de la table est occupé. Si la table est complète sans contenir la clé, il faut veiller à arrêter la boucle jusqu'à retrouver l'index initial.

#### Objectifs rencontrés
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières
* 18-Comprendre le fonctionnement d’une table de hachage 



### 1.3. Importance de la fonction de hachage
#### Exercice
>Une bonne fonction de hachage est essentielle pour garantir que notre table de hachage soit remplie de la façon la plus efficace possible. Détermine ce qu’est une fonction de hachage uniforme. 
Donne des exemples de deux fonctions de hachage, dont l’une serait moins uniforme que l’autre. 
Explique pourquoi.

#### Résolution
**Fonction basée sur la taille de clé**

Dans le cas ci-dessous, la fonction de hachage tient compte de la taille de la clé. Il y aura donc collision pour tous les mots de même tailles. 

```
int hash(key){
    int count=0;
    while(*key != '\0'){
        count++;
        key++;
    }
    return count % MAX_TABLE_SIZE;
}
```
**Fonction basée sur les caractères composants la clés**

Dans le cas ci-dessous, la fonction de hachage utilise la somme des position ascii des lettres qui compose le mot clé. On peut s'attendre à un dispersement plus uniforme par cette approche pour peu que les clés utilisent des caractères différent. Si un nombre restreint de caractère est utilisé pour des clés de même tailles, alors on peut aussi s'attendre à beaucoup de collisions. 

```
int hash(key){
    int hash=0;
    while(*key != '\0'){
        hash = (hash + (int)*key) ;
        key++;
    }
    return hash % MAX_TABLE_SIZE;
}
```

Finalement,une bonne fonction de hachage ne doit pas être trop influencée par la taille et de la richesse de caractère utilisé.

**Fonction basée sur les caractères composants la clés et un élément aléatoire par rapport à la position de la lettre**

Dans cette fonction, `ABC` et `CBA` ne sont théoriquement pas en collision comme dans les deux fonctions précédentes.

```
int hash(key){
    srand(123);
    int hash=0;
    while(*key != '\0'){
        hash = ((hash + (int)*key)*rand()) % MAX_TABLE_SIZE;
        key++;
    }
    return hash % MAX_TABLE_SIZE;
}
```

#### Objectifs rencontrés
* 18-Comprendre le fonctionnement d’une table de hachage 


### 1.4. Complexité des opérations
#### Exercice
> Évalue la complexité des quatre opérations d’un tableau associatif implémentées au moyen d’une
table de hachage, en supposant que la fonction de hachage soit très efficace (de l’ordre de O(1)) et
qu’elle soit très uniforme (et donc que les éléments sont très bien répartis dans le tableau).

#### Résolution
Dans des conditions idéales (uniformité et faible remplissage), les opérations (add, search, remove) ont un ordre de complexité directement lié à celle de la fonction de hachage soit O(1).

- create_dict= O(1)
- add_to_dict= O(1)
- search_in_dict= O(1)
- remove_from_dict= O(1) 
- 
#### Objectifs rencontrés
* 18-Comprendre le fonctionnement d’une table de hachage 

## 2. Implémentation d'un tableau associatif

### 2.1. Table de Hachage
#### Exercice
>Définissez la structure concrète table de hachage, que vous emploierez pour implémenter l’ADT
tableau associatif. En particulier, définissez une fonction de hachage, une fonction pour créer une
nouvelle table de hachage, pour ajouter des éléments, supprimer des éléments, récupérer des
éléments, une fonction pour agrandir la table si elle est trop remplie (par exemple lorsque le taux de
remplissage est de 2/3) etc.
Déterminez une fonction de hachage efficace et suffisamment uniforme. Justifiez.

#### Résolution
* Voir [implémentation de la hash table](code/Hash_table.c)
* Voir [tests sur la hash table](code/tests_Hash_table.c)

Compilation et exécution des tests (tous les tests passent)
```
gcc -o tests_Hash_table.out tests_Hash_table.c Hash_table.c listes_chainees_dict.c && ./tests_Hash_t
```
Dépend d'une implémentation de la liste chaînée incluant une clé (chaîne de caractère) et une valeur entière
* Voir [implémentation de la listes chainees](code/listes_chainees_dict.c)
* Voir [tests sur la hash table](code/test_list_chainees_dict.c)

Compilation et exécution des tests pour la liste chaînées (tous les tests passent)
```
gcc -o tests_list_chainees_dict.out tests_list_chainees_dict.c listes_chainees_dict.c && ./tests_list_chainees_dict.out
```

#### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 6-Être capable d’implémenter concrètement un ADT donné, de plusieurs manières

### 2.2. Tableau associatif
#### Exercice
>Implémentez maintenant votre tableau associatif au moyen de la structure concrète table de hachage
que vous avez définie précédemment.

#### Résolution
- Voir [implémentation](code/Dict_hash_chaine.c)
- Voir [tests](code/tests_Dict_hash_chaine.c)

Compilation et exécution des tests pour le tableau associatif (tous les tests passent)
```
gcc -o tests_Dict_hash_chaine.out tests_Dict_hash_chaine.c Dict_hash_chaine.c Hash_table.c listes_chainees_dict.c && ./tests_Dict_hash_chaine.out
```

#### Objectifs rencontrés
* 4-Compiler des projets composés de plusieurs fichiers .c et .h
* 19-Implémenter un tableau associatif au moyen d’une table de hachage


## 3. Lecture de fichiers


### 3.1. Ouvrir et lire un fichiers
#### Exercice
>Depuis un programme C, vous pouvez ouvrir des fichier ".txt" au moyen de la fonction "fopen" qui
renvoie une valeur de type FILE. La fonction "gets" permet la lecture du fichier ligne par ligne. La
fonction "fclose" permet de fermer le fichier lorsque tu as terminé la lecture.
Essaie d’ouvrir le fichier nana.txt et d’en afficher les deux premières lignes.
Essaie de stocker en mémoire la totalité du texte.

#### Résolution
Voir [implémentation dans une boucle](code/read_file_print.c)

Compilation et exécution
```
gcc -o read_file_print.out read_file_print.c && ./read_file_print.out
```

#### Objectifs rencontrés
* 20-Manipuler des fichier texte en C

###  3.2. Lister les mots d'un texte
#### Exercice
>Écrivez un programme qui vous permet d’obtenir la liste des mots présents dans un fichier de texte,
avec à chaque fois son nombre d’occurrences de ce mot. Par exemple, une fois le fichier analysé,
l’utilisateur peut entrer un mot et le programme lui indique combien d’occurrence de ce mot il y a
dans le texte. Petits conseils : détermine la liste des séparateurs de mots (espaces, ponctuation) et
pour chaque mot, transforme tout en minuscules. Et utilise un tableau associatif implémenté au
moyen d’une table de hachage !

#### Résolution

Voir [count_word_occurrence.c](code/count_word_occurrence.c)

Compilation & Exécution
```
gcc -o count_word_occurrence.out count_word_occurrence.c Dict_hash_chaine.c Hash_table.c listes_chainees_dict.c && ./count_word_occurrence.out
```

#### Objectifs rencontrés
* 17-Utiliser l’ADT "tableau associatif" pour résoudre des problèmes concrets en C
* 19-Implémenter un tableau associatif au moyen d’une table de hachage
* 20-Manipuler des fichier texte en C

## Auto-évaluation de la séance

#### Fonction de hachage avec valeur aléatoire à chaque position
Comme listée précédemment, j'ai choisi une fonction de hachage qui se base sur la somme des code ASCII des lettres que composent la clé mais qui multiplie cette valeur par un nombre aléatoire distinct pour chaque position. Vu que j'ai été confronté à des segmentation fault lors de la compilation, j'ai déduit qu'il fallait réduire la portée du nombre aléatoire dans une fourchette entre 0 et 1000 pour éviter les overflow. Un modulo selon la capacité de la table de hashage permet de garder un index dans la capacité de la table.
```
int hash(const char* key, int capacity){
    srand(123);
    int hash = 0;
    int randNum;
    while (*key != '\0') {
        randNum = rand()%1000;
        hash = (hash +  ((int)*key)*randNum) % capacity;
        key++;
    }
    return hash ;
}
```
#### Problème de la taille de ligne
En itérant plusieurs fois `fgets(line, buffer_size, file)`, le programme va considérer lire une ligne entière du fichier et l'écraser dans `line`. Dès lors, la taille de la déclaration de `line` influe sur le fait de ne pas manquer de caractère si la ligne est très longue.

Pour utiliser efficacement une allocation dynamique qui agrandit la taille de `line`, il faut y incorporer la position actuel du pointeur de lecture. Voici comment adapter `fgets` pour une ligne de 500 caractères mais un tampon de ligne de 100 caractères multiplié par 2 à chaque essais (jusqu'à ce que``\n`` soit présent dans le tampon de ligne).

```
fgets(line+0, 100-0, file);
fgets(line+100, 200-100, file);
fgets(line+200, 400-200, file);
fgets(line+400, 800-400, file);
```

#### Segmentation fault lors du traitement de Nana.txt 

Mon implémentation du dictionnaire via table de hachage ne supporte pas les caractère hors ASCII. Au lieu de changer mon implémentation en utilisant de nouvelles libraries, j'ai préféré nettoyé le texte `Nana.txt`. Voici la liste de changement:
* Remplacer les caractères avec accents par leur correspondant sans accent en ASCII (ex: `é` devent `e`).
* Eviter les espaces supplémentaires avant une ponctuation (ex: `mot !` devient `mot!`)
* Remplacer les apostrophes "françaises", les tirets de début de phrase, et les points de suspensions par leur correspondances ASCII.

Utiliser l'encodage ISO8859 qui est unibyte aurait pu être une solution mais ma console (UTF-8) ne reconnaissait pas certain caractère à l'affichage. Par soucis de simplicité, j'ai préféré modifier le fichiers texte de bases au lieu de modifier les paramètres de ma console.

## Notes en vrac

#### [Prof] Table de hachage

Une fonction de hachage va prendre de nombreuses clés et les transformer en index. Chaque index va correspondre à une place dans la table de hachage qui a une taille définie à l'avance.

La qualité de la fonction de hachage a un impact sur l'uniformité du positionnement dans la table de hachage. Cependant, vu qu'il y a un nombre limité de place dans la table de hachage, des collisions sont possibles entre plusieurs clés.

On ne peut pas deviner l'input à partir de l'output.

Pour accepter plusieurs éléments ayant le même index dans la table de hachage, une liste chainee peut être réalisée.

#### [Prof] Tips sur l'allocation de chaine de caractère
Utiliser `new_key = strdup(key)` pour allouer de la mémoire à une chaine de caractère qui est égale au nombre de caractère + 1 de key (p+1 our caractère nul)  

#### [ Recherche ] ``gets`` vs ``fgets``
Précedemment, j'ai utilisé la fonction `fgets`. Je me demande quelles sont les différents avec la fonction `gets` recommandée ci-dessous.

* Déclaration:
  * `gets(buffer)`
  * `fgets(buffer,size,source)`
* Sécurité :
fgets est sécurisée car elle limite le nombre de caractères lus, évitant ainsi les dépassements de tampon.
gets est non sécurisée car elle ne limite pas le nombre de caractères lus, ce qui peut entraîner des dépassements de tampon.

* Gestion du caractère de nouvelle ligne :
fgets conserve le caractère de nouvelle ligne (\n) dans la chaîne lue si la ligne est plus courte que n-1 caractères.
gets ne conserve pas le caractère de nouvelle ligne (\n) dans la chaîne lue.

Vu les avantages, je vais préférer utiliser `fgets`


#### [ Recherche ] Divers
**strchr**

La fonction strchr fait partie de la bibliothèque standard C, définie dans le fichier d'en-tête <string.h>. Elle est utilisée pour rechercher la première occurrence d'un caractère spécifique dans une chaîne de caractères.

`strchr(to_remove, *word)` va retourner nul si le caractère `*word` apparaît dans le string `to_remove` sinon la position de la première occurrence est retournée.

**strtok**

La fonction strtok en C est utilisée pour diviser une chaîne de caractères en une série de sous-chaînes (tokens) basées sur un ensemble de délimiteurs spécifiés. Elle est particulièrement utile pour analyser des chaînes de caractères et extraire des mots ou des éléments délimités par des espaces, des virgules, des points-virgules, etc.

Paramètres: 
- char *str : Un pointeur vers la chaîne de caractères à diviser. Lors du premier appel, ce paramètre doit pointer vers la chaîne à analyser. Pour les appels suivants, ce paramètre doit être NULL pour continuer à diviser la chaîne à partir de la position où le dernier appel s'est arrêté.
- const char *delim : Une chaîne contenant les caractères délimiteurs. Chaque caractère de cette chaîne est considéré comme un délimiteur.

Valeur de retour
- Pointeur vers le prochain token : strtok retourne un pointeur vers le prochain token trouvé dans la chaîne.
- NULL : Si aucun autre token n'est trouvé, strtok retourne NULL.

**Encodage**

 Si le fichier est encodé en UTF-8, les fonctions standard de lecture de fichiers fonctionneront correctement pour la plupart des cas, car UTF-8 est rétrocompatible avec ASCII. Cependant, si des caractères multi-octets  apparaissent (comme les caractères accentués ou les caractères non latins), il faut utiliser des bibliothèques spécifiques pour traiter correctement ces caractères.

Nana.txt est encodé en UTF8 tandis que nana_ISO8859.txt est en iso-8859-1 (vérifiable sous linux par: `file -i ../fichiers/nana_ISO8859.txt`).

L'apostrophe dans Nana.txt est une caractère non reconnu par ma configuration. J'ai préalablement remplacer l'apostrophe original par l'apostrophe de mon clavier via un find & replace dans le fichier Nana.txt. 