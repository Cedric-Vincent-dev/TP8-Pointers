**2. PARTIE THEORIQUE — COMPREHENSION PROFONDE DE LA MEMOIRE ET DES POINTEURS**



**2.1. Qu’est‑ce que la mémoire ?**

La mémoire est un espace linéaire composé d’octets, chacun identifié par une adresse unique. Lorsqu’un programme s’exécute, le système d’exploitation lui attribue un espace mémoire dans lequel il peut stocker :

- des variables,
- des structures,
- des objets dynamiques,
- du code exécutable,
- des données globales.

Chaque variable possède trois caractéristiques fondamentales :

- **une valeur** (ex : 42),
- **une adresse** (ex : 0x7ffeefbff4ac),
- **un type** (ex : int).

Le type détermine :

- la taille en mémoire,
- la manière dont la valeur est interprétée,
- les opérations autorisées.

La mémoire est un espace **séquentiel**, mais le programme n’y accède jamais directement : il utilise des **adresses**, manipulées via des pointeurs.

Comprendre la mémoire, c’est comprendre **où** les données sont stockées et **comment** y accéder.



**2.2. Stack et Heap — deux zones essentielles**

Cette section est cruciale : elle conditionne toute la compréhension des pointeurs.

**2.2.1. La Stack (pile)**

La stack est une zone mémoire gérée automatiquement par le compilateur.  
Elle contient :

- les variables locales,
- les paramètres de fonction,
- les adresses de retour,
- les cadres d’activation (stack frames).

Caractéristiques :

- organisation **LIFO** (Last In, First Out),
- allocation et libération **automatiques**,
- très rapide,
- taille limitée,
- adaptée aux données de courte durée de vie.

Exemple :

```cpp
int userAge = 25;  // stocké sur la stack
```

Si une fonction se termine, toutes les variables locales disparaissent.



**2.2.2. La Heap (tas)**

La heap est une zone mémoire gérée manuellement par le programmeur.  
Elle contient :

- les allocations dynamiques,
- les structures créées à l’exécution,
- les objets dont la durée de vie dépasse une fonction.

Caractéristiques :

- allocation **manuelle** (malloc/new),
- libération **manuelle** (free/delete),
- plus lente que la stack,
- grande capacité,
- risque de fuite mémoire.

Exemple :

```cpp
int *pointerToAge = new int(25);  // stocké sur la heap
```



**2.3. Les segments mémoire d’un programme**

Un programme C/C++ est divisé en plusieurs segments mémoire :

**2.3.1. Code segment (text segment)**  
- Contient les instructions machine.  
- Lecture seule.  
- Protégé contre l’écriture.

**2.3.2. Data segment**  
- Contient les variables globales **initialisées**.

**2.3.3. BSS segment**  
- Contient les variables globales **non initialisées**.  
- Initialisées à zéro automatiquement.

**2.3.4. Heap**  
- Allocation dynamique.

**2.3.5. Stack**  
- Variables locales, appels de fonction.

Schéma simplifié :

```
+---------------------------+
|        Code segment       |
+---------------------------+
|        Data segment       |
+---------------------------+
|        BSS segment        |
+---------------------------+
|           Heap            |
|     (grows upward)        |
+---------------------------+
|           Stack           |
|     (grows downward)      |
+---------------------------+
```



**2.4. Définition d’un pointeur**

Un pointeur est une variable qui contient **une adresse mémoire**.  
Il ne contient pas une valeur, mais **l’emplacement où se trouve cette valeur**.

Exemple :

```cpp
int userScore = 50;
int *pointerToUserScore = &userScore;
```

- `userScore` contient **50**
- `pointerToUserScore` contient **l’adresse de userScore**

Le pointeur permet :

- d’accéder à la valeur pointée (`*pointerToUserScore`),
- de modifier cette valeur,
- de manipuler la mémoire directement,
- de travailler avec des tableaux, des structures, des fonctions.

Les pointeurs sont donc **le lien direct entre le langage C/C++ et la mémoire physique**.



**2.5. Les notations `*`, `&`, `$`**

**2.5.1. `&` — adresse**

L’opérateur `&` permet d’obtenir l’adresse d’une variable.

```cpp
int userAge = 30;
int *pointerToUserAge = &userAge;
```



**2.5.2. `*` — déréférencement et déclaration**

Deux rôles :

1. **Déclarer un pointeur**

```cpp
int *pointerToValue;
```

2. **Déréférencer un pointeur**

```cpp
int value = *pointerToValue;
```

Le déréférencement signifie :  
→ accéder à la valeur stockée à l’adresse contenue dans le pointeur.



**2.5.3. `$` — n’existe pas en C/C++**

L’opérateur `$` **n’existe pas** dans le langage C ou C++.  
Ton tuteur veut vérifier que tu le sais.



**2.6. Définition d’une référence**

Une référence est un **alias** d’une variable existante.  
Elle ne possède pas sa propre adresse : elle renvoie toujours vers la variable originale.

Exemple :

```cpp
int userAge = 30;
int &referenceToUserAge = userAge;
```

Différences majeures :

| Pointeur | Référence |
|---------|-----------|
| Peut être nul | Ne peut jamais être nulle |
| Peut changer de cible | Ne peut pas changer de cible |
| Nécessite `*` et `&` | Utilisation transparente |
| Plus bas niveau | Plus haut niveau |



**2.7. Passage de paramètres**

**2.7.1. Par valeur**

La fonction reçoit **une copie** de la variable.

```cpp
void incrementValue(int number) {
    number = number + 1;
}
```



**2.7.2. Par pointeur**

La fonction reçoit **l’adresse** de la variable.

```cpp
void incrementValue(int *pointerToNumber) {
    *pointerToNumber = *pointerToNumber + 1;
}
```



**2.7.3. Par référence**

La fonction reçoit un **alias** de la variable.

```cpp
void incrementValue(int &referenceToNumber) {
    referenceToNumber = referenceToNumber + 1;
}
```



**2.8. Dangers des pointeurs — Undefined Behavior (UB)**

Ton tuteur veut une liste complète.  
Voici les principaux cas :

**2.8.1. Déréférencement d’un pointeur nul**

```c
int *pointerToValue = NULL;
int result = *pointerToValue;  // UB
```



**2.8.2. Pointeur non initialisé**

```c
int *pointerToValue;
int result = *pointerToValue;  // UB
```



**2.8.3. Use‑after‑free**

```c
int *pointerToValue = malloc(sizeof(int));
free(pointerToValue);
*pointerToValue = 10;  // UB
```



**2.8.4. Double free**

```c
free(pointerToValue);
free(pointerToValue);  // UB
```



**2.8.5. Buffer overflow**

```c
int numbers[3] = {1, 2, 3};
numbers[5] = 10;  // UB
```



**2.8.6. Pointer arithmetic hors limites**

```c
int numbers[3];
int *pointerToNumbers = numbers;
pointerToNumbers = pointerToNumbers + 10;  // UB
```



**2.9. Arithmétique des pointeurs**

L’arithmétique des pointeurs dépend du type pointé.

**2.9.1. Addition**

```c
pointerToNumbers + 1;  // avance de sizeof(type)
```

**2.9.2. Soustraction**

```c
pointerToNumbers - 1;
```

**2.9.3. Soustraction de deux pointeurs**

```c
int difference = pointerEnd - pointerStart;
```

**2.9.4. Comparaison**

```c
if (pointerA < pointerB) { ... }
```

**2.9.5. Parcours de tableau**

```c
int *pointerToNumbers = numbers;
for (int index = 0; index < 5; index++) {
    printf("%d\n", *(pointerToNumbers + index));
}
