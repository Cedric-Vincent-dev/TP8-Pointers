**2. PARTIE THEORIQUE — COMPREHENSION PROFONDE DE LA MEMOIRE ET DES POINTEURS**




**2.1. Qu’est‑ce que la mémoire ?**

Explication détaillée

La mémoire est un espace linéaire composé d’octets, chacun identifié par une **adresse unique**.  
Lorsqu’un programme s’exécute, le système d’exploitation lui attribue un espace mémoire dans lequel il peut :

- stocker des variables locales et globales,  
- créer des structures,  
- allouer dynamiquement des objets,  
- exécuter du code,  
- gérer des données temporaires.  

Chaque variable possède trois caractéristiques fondamentales :

- **une valeur** (exemple : 42),  
- **une adresse** (exemple : 0x7ffeefbff4ac),  
- **un type** (exemple : `int`).  

Le **type** détermine :  
- la taille en mémoire,  
- la manière dont la valeur est interprétée,  
- les opérations autorisées.  

Comprendre la mémoire, c’est comprendre **où** les données sont stockées et **comment** y accéder.



Exemple concret en **C**

```c
#include <stdio.h>

int main(void) {
    // Déclaration d'une variable entière
    int userNumber = 42;

    // Affichage de la valeur
    printf("Value of userNumber: %d\n", userNumber);

    // Affichage de l'adresse mémoire
    printf("Address of userNumber: %p\n", (void*)&userNumber);

    return 0;
}
```

Explications
- `userNumber` contient la valeur **42**.  
- `&userNumber` donne l’adresse mémoire où cette valeur est stockée.  
- `%p` est le format utilisé pour afficher une adresse en C.  
- `(void*)&userNumber` est une conversion explicite pour respecter les standards modernes (C23).



Résultat attendu (exemple de sortie)

```
Value of userNumber: 42
Address of userNumber: 0x7ffee3bff4ac
```

*(l’adresse varie selon l’exécution, mais elle montre bien que la variable est stockée quelque part en mémoire)*



Points pédagogiques à retenir
- La mémoire est une suite d’octets numérotés.  
- Chaque variable occupe un espace défini par son type.  
- On peut accéder à la valeur **ou** à l’adresse.  
- Le langage C donne un accès direct à ces adresses via les pointeurs.




**2.2. Stack et Heap**

Explication détaillée

La mémoire d’un programme est divisée en plusieurs zones. Les deux plus importantes pour un développeur sont :

**La Stack (pile)**  
- Zone mémoire gérée automatiquement par le compilateur.  
- Contient les variables locales, les paramètres de fonction et les adresses de retour.  
- Fonctionne selon le principe **LIFO** (*Last In, First Out*).  
- Très rapide, mais limitée en taille.  
- Les variables disparaissent automatiquement à la fin de la fonction.  
- Risque : **stack overflow** si trop de données sont stockées.



**La Heap (tas)**  
- Zone mémoire gérée manuellement par le programmeur.  
- Contient les allocations dynamiques.  
- Plus lente que la stack, mais beaucoup plus grande.  
- Allocation et libération doivent être faites explicitement (`malloc/free` en C, `new/delete` en C++).  
- Risques : fuite mémoire, fragmentation, **use-after-free**.



Exemple en **C — Stack vs Heap**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Exemple de variable locale (stack)
    int stackNumber = 10;
    printf("Stack value: %d\n", stackNumber);
    printf("Stack address: %p\n", (void*)&stackNumber);

    // Exemple d'allocation dynamique (heap)
    int *heapNumber = malloc(sizeof(int));
    if (heapNumber == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *heapNumber = 20;
    printf("Heap value: %d\n", *heapNumber);
    printf("Heap address: %p\n", (void*)heapNumber);

    // Libération de la mémoire
    free(heapNumber);

    return 0;
}
```

Explications
- `stackNumber` est stocké sur la **stack**.  
- `heapNumber` est une adresse vers une zone mémoire allouée sur la **heap**.  
- On doit libérer la mémoire avec `free()` pour éviter une fuite.  



Exemple en **C++ — Stack vs Heap**

```cpp
#include <iostream>

int main() {
    // Exemple de variable locale (stack)
    int stackNumber{10};
    std::cout << "Stack value: " << stackNumber << '\n';
    std::cout << "Stack address: " << &stackNumber << '\n';

    // Exemple d'allocation dynamique (heap)
    int *heapNumber{new int(20)};
    std::cout << "Heap value: " << *heapNumber << '\n';
    std::cout << "Heap address: " << heapNumber << '\n';

    // Libération de la mémoire
    delete heapNumber;

    return 0;
}
```

Explications
- `stackNumber` est une variable locale, gérée automatiquement.  
- `heapNumber` est une allocation dynamique sur la heap.  
- En C++, on utilise `new` et `delete`.  
- Si on oublie `delete`, on crée une **fuite mémoire**.



Résultat attendu (exemple de sortie)

```
Stack value: 10
Stack address: 0x7ffee3bff4ac
Heap value: 20
Heap address: 0x600003e0
```

*(les adresses varient selon l’exécution, mais on voit bien que stack et heap sont distinctes)*



Points pédagogiques à retenir
- La **stack** est rapide mais limitée, et gérée automatiquement.  
- La **heap** est grande mais lente, et doit être gérée manuellement.  
- Les pointeurs sont indispensables pour accéder à la heap.  
- Bien comprendre cette distinction est essentiel pour éviter les erreurs mémoire.  






**2.3. Les segments mémoire d’un programme**

**Explication détaillée**

Lorsqu’un programme est exécuté, son espace mémoire est divisé en plusieurs segments distincts.  
Chaque segment a un rôle précis :

1. **Code segment (text segment)**  
   - Contient les instructions machine du programme.  
   - Lecture seule (on ne peut pas modifier le code en cours d’exécution).  
   - Protégé contre l’écriture pour éviter les erreurs ou attaques.

2. **Data segment**  
   - Contient les variables globales **initialisées**.  
   - Exemple : `int globalNumber = 10;`

3. **BSS segment**  
   - Contient les variables globales **non initialisées**.  
   - Exemple : `int globalCounter;` (valeur par défaut = 0).  

4. **Heap**  
   - Zone pour l’allocation dynamique.  
   - Gérée par le programmeur (`malloc/free` en C, `new/delete` en C++).  

5. **Stack**  
   - Contient les variables locales et les appels de fonction.  
   - Gérée automatiquement par le compilateur.  



**Exemple en **C****

```c
#include <stdio.h>
#include <stdlib.h>

// Variable globale initialisée (data segment)
int globalNumber = 10;

// Variable globale non initialisée (BSS segment)
int globalCounter;

int main(void) {
    // Variable locale (stack)
    int stackValue = 5;

    // Allocation dynamique (heap)
    int *heapValue = malloc(sizeof(int));
    if (heapValue == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    *heapValue = 20;

    // Affichage des valeurs et adresses
    printf("Global initialized (data): value=%d, address=%p\n", globalNumber, (void*)&globalNumber);
    printf("Global uninitialized (BSS): value=%d, address=%p\n", globalCounter, (void*)&globalCounter);
    printf("Local (stack): value=%d, address=%p\n", stackValue, (void*)&stackValue);
    printf("Heap: value=%d, address=%p\n", *heapValue, (void*)heapValue);

    free(heapValue);
    return 0;
}
```

**Explications**
- `globalNumber` → data segment  
- `globalCounter` → BSS segment  
- `stackValue` → stack  
- `heapValue` → heap  



**Exemple en **C++****

```cpp
#include <iostream>

// Variable globale initialisée (data segment)
int globalNumber{10};

// Variable globale non initialisée (BSS segment)
int globalCounter;

int main() {
    // Variable locale (stack)
    int stackValue{5};

    // Allocation dynamique (heap)
    int *heapValue{new int(20)};

    // Affichage des valeurs et adresses
    std::cout << "Global initialized (data): value=" << globalNumber 
              << ", address=" << &globalNumber << '\n';

    std::cout << "Global uninitialized (BSS): value=" << globalCounter 
              << ", address=" << &globalCounter << '\n';

    std::cout << "Local (stack): value=" << stackValue 
              << ", address=" << &stackValue << '\n';

    std::cout << "Heap: value=" << *heapValue 
              << ", address=" << heapValue << '\n';

    delete heapValue;
    return 0;
}
```



**Résultat attendu (exemple de sortie)**

```
Global initialized (data): value=10, address=0x601050
Global uninitialized (BSS): value=0, address=0x601060
Local (stack): value=5, address=0x7ffee3bff4ac
Heap: value=20, address=0x600003e0
```

*(les adresses varient selon l’exécution, mais on voit bien que chaque segment est distinct)*



**Points pédagogiques à retenir**
- Le programme est divisé en **segments mémoire** bien définis.  
- Les variables globales initialisées vont dans le **data segment**.  
- Les variables globales non initialisées vont dans le **BSS segment**.  
- Les variables locales sont sur la **stack**.  
- Les allocations dynamiques sont sur la **heap**.  
- Comprendre cette organisation est essentiel pour maîtriser la gestion mémoire et éviter les erreurs.







**2.4. Définition d’un pointeur**

**Explication détaillée**

Un **pointeur** est une variable qui contient **l’adresse mémoire** d’une autre variable.  
Il ne stocke pas directement la valeur, mais **l’emplacement où cette valeur est enregistrée**.

Caractéristiques principales :  
- Un pointeur a un **type** (exemple : `int*` pour pointer vers un entier).  
- Il peut être **déréférencé** avec l’opérateur `*` pour accéder à la valeur pointée.  
- Il est lié directement à la gestion de la mémoire : sans pointeurs, impossible d’accéder à la heap ou de manipuler des structures complexes.  
- Les pointeurs permettent de travailler avec des tableaux, des chaînes de caractères, des structures, et même des fonctions.

Les pointeurs sont donc **le lien direct entre le langage C/C++ et la mémoire physique**.



**Exemple en **C****

```c
#include <stdio.h>

int main(void) {
    // Déclaration d'une variable entière
    int userNumber = 50;

    // Déclaration d'un pointeur vers int
    int *pointerToUserNumber = &userNumber;

    // Affichage de la valeur et de l'adresse
    printf("Value of userNumber: %d\n", userNumber);
    printf("Address of userNumber: %p\n", (void*)&userNumber);

    // Utilisation du pointeur
    printf("Value via pointer: %d\n", *pointerToUserNumber);
    printf("Address stored in pointer: %p\n", (void*)pointerToUserNumber);

    // Modification via le pointeur
    *pointerToUserNumber = 75;
    printf("New value of userNumber after modification: %d\n", userNumber);

    return 0;
}
```

**Explications**
- `userNumber` contient la valeur **50**.  
- `pointerToUserNumber` contient l’adresse de `userNumber`.  
- `*pointerToUserNumber` permet d’accéder à la valeur stockée à cette adresse.  
- Modifier `*pointerToUserNumber` modifie directement `userNumber`.



**Exemple en **C++****

```cpp
#include <iostream>

int main() {
    // Déclaration d'une variable entière
    int userNumber{50};

    // Déclaration d'un pointeur vers int
    int *pointerToUserNumber{&userNumber};

    // Affichage de la valeur et de l'adresse
    std::cout << "Value of userNumber: " << userNumber << '\n';
    std::cout << "Address of userNumber: " << &userNumber << '\n';

    // Utilisation du pointeur
    std::cout << "Value via pointer: " << *pointerToUserNumber << '\n';
    std::cout << "Address stored in pointer: " << pointerToUserNumber << '\n';

    // Modification via le pointeur
    *pointerToUserNumber = 75;
    std::cout << "New value of userNumber after modification: " << userNumber << '\n';

    return 0;
}
```

**Explications**
- Même logique qu’en C23, mais syntaxe modernisée (`{}` pour initialisation).  
- `std::cout` est utilisé pour afficher les résultats.  
- Le pointeur permet de lire et modifier la variable originale.



**Résultat attendu (exemple de sortie)**

```
Value of userNumber: 50
Address of userNumber: 0x7ffee3bff4ac
Value via pointer: 50
Address stored in pointer: 0x7ffee3bff4ac
New value of userNumber after modification: 75
```

*(les adresses varient selon l’exécution, mais on voit bien que le pointeur stocke l’adresse et permet de modifier la valeur)*



**Points pédagogiques à retenir**
- Un pointeur est une **variable spéciale** qui stocke une adresse.  
- Le type du pointeur détermine la taille et l’interprétation de la valeur pointée.  
- L’opérateur `*` permet d’accéder à la valeur pointée (**déréférencement**).  
- L’opérateur `&` permet d’obtenir l’adresse d’une variable.  
- Les pointeurs sont indispensables pour manipuler la mémoire et les structures complexes.




**2.5. Les notations `*`, `&`, `$`**

**Explication détaillée**

**1. L’opérateur `&` — adresse**
- Permet d’obtenir l’adresse d’une variable.  
- Utilisé pour initialiser un pointeur.  
- Exemple : `int *p = &x;`

**2. L’opérateur `*` — déréférencement et déclaration**
- Sert à déclarer un pointeur (`int *p;`).  
- Sert à accéder à la valeur pointée (`*p`).  
- Exemple : `*p = 20;` modifie la valeur de la variable pointée.

**3. Le symbole `$`**
- **N’existe pas en C/C++.**  
- Ton tuteur l’a ajouté volontairement pour vérifier que tu sais distinguer la syntaxe réelle de la syntaxe inventée.  
- En C et C++, `$` n’a aucune signification.  




**Exemple en **C****

```c
#include <stdio.h>

int main(void) {
    int userNumber = 10;

    // Utilisation de & pour obtenir l'adresse
    int *pointerToUserNumber = &userNumber;

    // Affichage de l'adresse et de la valeur
    printf("Address of userNumber: %p\n", (void*)&userNumber);
    printf("Value via pointer: %d\n", *pointerToUserNumber);

    // Modification via le pointeur
    *pointerToUserNumber = 25;
    printf("New value of userNumber: %d\n", userNumber);

    // Exemple volontaire avec $ (invalide en C)
    // int $invalid = 5; // ERREUR : $ n'est pas autorisé

    return 0;
}
```

**Explications**
- `&userNumber` → adresse de la variable.  
- `*pointerToUserNumber` → valeur stockée à cette adresse.  
- `$invalid` → syntaxe invalide, prouve que `$` n’existe pas en C.



**Exemple en **C++****

```cpp
#include <iostream>

int main() {
    int userNumber{10};

    // Utilisation de & pour obtenir l'adresse
    int *pointerToUserNumber{&userNumber};

    // Affichage de l'adresse et de la valeur
    std::cout << "Address of userNumber: " << &userNumber << '\n';
    std::cout << "Value via pointer: " << *pointerToUserNumber << '\n';

    // Modification via le pointeur
    *pointerToUserNumber = 25;
    std::cout << "New value of userNumber: " << userNumber << '\n';

    // Exemple volontaire avec $ (invalide en C++)
    // int $invalid{5}; // ERREUR : $ n'est pas autorisé

    return 0;
}
```

**Explications**
- Même logique qu’en C23, mais syntaxe modernisée (`{}` pour initialisation).  
- `$` est également invalide en C++20.  



**Résultat attendu (exemple de sortie)**

```
Address of userNumber: 0x7ffee3bff4ac
Value via pointer: 10
New value of userNumber: 25
```

*(les adresses varient selon l’exécution, mais la logique reste la même)*



**Points pédagogiques à retenir**
- `&` → donne l’adresse d’une variable.  
- `*` → permet de déclarer un pointeur et d’accéder à la valeur pointée.  
- `$` → n’existe pas en C/C++, il faut le signaler explicitement.  
- La maîtrise de `*` et `&` est indispensable pour comprendre les pointeurs.  





**2.6. Référence vs Pointeur**

**Explication détaillée**

**Qu’est-ce qu’une référence ?**
- Une **référence** est un alias d’une variable existante.  
- Elle ne crée pas une nouvelle variable, mais un autre nom qui désigne la même donnée.  
- Syntaxe : `int &ref = variable;`  
- Une référence doit être initialisée dès sa déclaration.  
- Elle ne peut pas être réassignée pour pointer vers une autre variable.  
- Plus sûre et plus lisible qu’un pointeur, car elle ne peut pas être `NULL`.



**Qu’est-ce qu’un pointeur ?**
- Un **pointeur** est une variable qui contient l’adresse d’une autre variable.  
- Il peut être réassigné pour pointer vers différentes variables.  
- Il peut être `NULL` (ou `nullptr` en C++ moderne).  
- Syntaxe : `int *p = &variable;`  
- Nécessite un déréférencement (`*p`) pour accéder à la valeur.



**Différences principales**
| Aspect                  | Pointeur                        | Référence                     |
|--------------------------|---------------------------------|--------------------------------|
| Initialisation           | Peut être déclaré sans valeur   | Doit être initialisée          |
| Réassignation            | Peut changer de cible           | Ne peut pas changer de cible   |
| Nullité                  | Peut être `nullptr`             | Ne peut pas être nulle         |
| Syntaxe                  | `int *p = &x;`                  | `int &r = x;`                  |
| Accès à la valeur        | `*p`                            | `r`                            |
| Lisibilité               | Moins lisible                   | Plus lisible                   |



**Exemple en **C++ — Pointeur vs Référence****

```cpp
#include <iostream>

void modifyWithPointer(int *pointerToNumber) {
    *pointerToNumber = *pointerToNumber + 10;
}

void modifyWithReference(int &referenceToNumber) {
    referenceToNumber = referenceToNumber + 10;
}

int main() {
    int userNumber{5};

    // Utilisation d'un pointeur
    int *pointerToUserNumber{&userNumber};
    modifyWithPointer(pointerToUserNumber);
    std::cout << "After modifyWithPointer: " << userNumber << '\n';

    // Réinitialisation
    userNumber = 5;

    // Utilisation d'une référence
    modifyWithReference(userNumber);
    std::cout << "After modifyWithReference: " << userNumber << '\n';

    return 0;
}
```



**Explications**
- `modifyWithPointer` reçoit un pointeur → nécessite `*` pour accéder/modifier la valeur.  
- `modifyWithReference` reçoit une référence → syntaxe plus simple, pas besoin de `*`.  
- Les deux modifient directement la variable originale.  
- La référence est plus sûre car elle ne peut pas être `nullptr`.



**Résultat attendu (exemple de sortie)**

```
After modifyWithPointer: 15
After modifyWithReference: 15
```


**Points pédagogiques à retenir**
- Une **référence** est un alias, plus sûr et plus lisible qu’un pointeur.  
- Un **pointeur** est plus flexible (peut être réassigné, peut être `nullptr`).  
- Les références sont préférées en C++ moderne pour passer des paramètres et éviter les erreurs.  
- Les pointeurs restent indispensables pour l’allocation dynamique et certaines structures complexes.  






**2.7. Passage de paramètres**

**Explication détaillée**

Lorsqu’on appelle une fonction, il existe plusieurs manières de transmettre une variable :

**1. Passage par valeur**
- La fonction reçoit une **copie** de la variable.  
- Toute modification dans la fonction n’affecte pas la variable originale.  
- C’est le mode par défaut en C et C++.  
- Avantage : sécurité (l’original n’est pas modifié).  
- Inconvénient : inefficace pour les grandes structures (copie coûteuse).



**2. Passage par pointeur**
- La fonction reçoit l’**adresse** de la variable.  
- Permet de modifier directement la variable originale via le pointeur.  
- Utilisé en C pour simuler le passage par référence.  
- Risques : pointeur `NULL`, mauvaise gestion mémoire.



**3. Passage par référence (C++ uniquement)**
- La fonction reçoit un **alias** de la variable originale.  
- Syntaxe proche du passage par valeur, mais comportement identique au passage par pointeur.  
- Plus sûr et plus lisible que les pointeurs.  
- Ne peut pas être `NULL`.  
- Utilisé en C++ moderne pour éviter les copies inutiles.



**Exemple en **C — Par valeur vs Par pointeur****

```c
#include <stdio.h>

// Passage par valeur
void incrementByValue(int number) {
    number = number + 10;
    printf("Inside incrementByValue: number = %d\n", number);
}

// Passage par pointeur
void incrementByPointer(int *pointerToNumber) {
    *pointerToNumber = *pointerToNumber + 10;
    printf("Inside incrementByPointer: *pointerToNumber = %d\n", *pointerToNumber);
}

int main(void) {
    int userNumber = 5;

    // Passage par valeur
    incrementByValue(userNumber);
    printf("After incrementByValue: userNumber = %d\n", userNumber);

    // Passage par pointeur
    incrementByPointer(&userNumber);
    printf("After incrementByPointer: userNumber = %d\n", userNumber);

    return 0;
}
```

Explications
- `incrementByValue` → ne modifie pas `userNumber` (copie).  
- `incrementByPointer` → modifie `userNumber` car elle reçoit son adresse.  



**Exemple en **C++ — Par valeur vs Par référence****

```cpp
#include <iostream>

// Passage par valeur
void incrementByValue(int number) {
    number = number + 10;
    std::cout << "Inside incrementByValue: number = " << number << '\n';
}

// Passage par référence
void incrementByReference(int &referenceToNumber) {
    referenceToNumber = referenceToNumber + 10;
    std::cout << "Inside incrementByReference: referenceToNumber = " << referenceToNumber << '\n';
}

int main() {
    int userNumber{5};

    // Passage par valeur
    incrementByValue(userNumber);
    std::cout << "After incrementByValue: userNumber = " << userNumber << '\n';

    // Passage par référence
    incrementByReference(userNumber);
    std::cout << "After incrementByReference: userNumber = " << userNumber << '\n';

    return 0;
}
```

**Explications**
- `incrementByValue` → ne modifie pas `userNumber`.  
- `incrementByReference` → modifie directement `userNumber`.  
- Syntaxe plus simple et plus sûre qu’un pointeur.



**Résultat attendu (exemple de sortie)**

```
Inside incrementByValue: number = 15
After incrementByValue: userNumber = 5
Inside incrementByPointer: *pointerToNumber = 15
After incrementByPointer: userNumber = 15
Inside incrementByReference: referenceToNumber = 15
After incrementByReference: userNumber = 15
```



**Points pédagogiques à retenir**
- **Par valeur** → copie, ne modifie pas l’original.  
- **Par pointeur** → modifie l’original via son adresse.  
- **Par référence** → modifie l’original, syntaxe plus simple et sûre.  
- En C++ moderne, on privilégie les **références** pour la lisibilité et la sécurité.  
- Les pointeurs restent indispensables pour la gestion mémoire et certaines structures complexes.





**2.8. Exemples de pointeurs**

**Explication générale**
Les pointeurs ne se limitent pas aux entiers. Ils peuvent pointer vers différents types de données et structures.  
Voici les cas principaux à maîtriser :

1. Pointeur sur `int`  
2. Pointeur sur `char`  
3. Pointeur sur tableau  
4. Tableau de pointeurs  
5. Pointeur de pointeur  
6. Pointeur sur fonction  



**Exemple 1 — Pointeur sur `int` (C)**

```c
#include <stdio.h>

int main(void) {
    int userNumber = 10;
    int *pointerToUserNumber = &userNumber;

    printf("Value via pointer: %d\n", *pointerToUserNumber);
    *pointerToUserNumber = 20;
    printf("New value: %d\n", userNumber);

    return 0;
}
```

Le pointeur permet de lire et modifier la variable originale.



**Exemple 2 — Pointeur sur `char` (C)**

```c
#include <stdio.h>

int main(void) {
    char letter = 'A';
    char *pointerToLetter = &letter;

    printf("Character via pointer: %c\n", *pointerToLetter);
    *pointerToLetter = 'Z';
    printf("New character: %c\n", letter);

    return 0;
}
```

Très utilisé pour manipuler des chaînes de caractères.



**Exemple 3 — Pointeur sur tableau (C)**

```c
#include <stdio.h>

int main(void) {
    int numbers[3] = {1, 2, 3};
    int *pointerToArray = numbers; // équivalent à &numbers[0]

    for (int i = 0; i < 3; i++) {
        printf("numbers[%d] = %d\n", i, *(pointerToArray + i));
    }

    return 0;
}
```

Le nom du tableau est déjà un pointeur vers son premier élément.



**Exemple 4 — Tableau de pointeurs (C)**

```c
#include <stdio.h>

int main(void) {
    const char *words[3] = {"Hello", "World", "Pointers"};

    for (int i = 0; i < 3; i++) {
        printf("words[%d] = %s\n", i, words[i]);
    }

    return 0;
}
```

Chaque élément du tableau est un pointeur vers une chaîne de caractères.



**Exemple 5 — Pointeur de pointeur (C)**

```c
#include <stdio.h>

int main(void) {
    int userNumber = 42;
    int *pointerToUserNumber = &userNumber;
    int **pointerToPointer = &pointerToUserNumber;

    printf("Value via pointerToPointer: %d\n", **pointerToPointer);

    return 0;
}
```

Permet de manipuler des adresses de pointeurs, utile pour les structures complexes (tableaux dynamiques, etc.).



**Exemple 6 — Pointeur sur fonction (C)**

```c
#include <stdio.h>

void sayHello(void) {
    printf("Hello from function pointer!\n");
}

int main(void) {
    void (*functionPointer)(void) = sayHello;
    functionPointer(); // Appel via pointeur
    return 0;
}
```

Les pointeurs sur fonction permettent de stocker et appeler des fonctions dynamiquement (très utilisés en callbacks).



**Points pédagogiques à retenir**
- Les pointeurs peuvent cibler **tout type de données** : int, char, tableau, fonction…  
- Un tableau est déjà un pointeur vers son premier élément.  
- Les pointeurs de pointeurs permettent de gérer des structures imbriquées.  
- Les pointeurs sur fonction sont puissants pour la modularité et les callbacks.  
- Chaque exemple doit être compris et testé dans `main()` pour prouver la maîtrise.






**2.9. Const et pointeurs**

**Explication détaillée**

L’utilisation de `const` avec les pointeurs permet de contrôler ce qui peut être modifié :  
- La **valeur pointée**  
- L’**adresse stockée dans le pointeur**

**Les trois cas principaux :**

1. **`const int *p`**  
   - Le pointeur peut changer d’adresse.  
   - La valeur pointée ne peut pas être modifiée via le pointeur.  
   -  *Constante sur la donnée, pas sur le pointeur.*

2. **`int *const p`**  
   - Le pointeur ne peut pas changer d’adresse.  
   - La valeur pointée peut être modifiée.  
   -  *Constante sur le pointeur, pas sur la donnée.*

3. **`const int *const p`**  
   - Le pointeur ne peut pas changer d’adresse.  
   - La valeur pointée ne peut pas être modifiée.  
   -  *Constante sur les deux.*



**Exemple en **C****

```c
#include <stdio.h>

int main(void) {
    int number1 = 10;
    int number2 = 20;

    // 1. const int *p : valeur non modifiable via le pointeur
    const int *p1 = &number1;
    printf("p1 points to value: %d\n", *p1);
    // *p1 = 15; // ERREUR : impossible de modifier la valeur via p1
    p1 = &number2; // OK : le pointeur peut changer d'adresse

    // 2. int *const p : adresse non modifiable
    int *const p2 = &number1;
    *p2 = 30; // OK : modification de la valeur
    // p2 = &number2; // ERREUR : impossible de changer l'adresse

    // 3. const int *const p : ni valeur ni adresse modifiable
    const int *const p3 = &number1;
    printf("p3 points to value: %d\n", *p3);
    // *p3 = 40; // ERREUR
    // p3 = &number2; // ERREUR

    return 0;
}
```



**Exemple en **C++****

```cpp
#include <iostream>

int main() {
    int number1{10};
    int number2{20};

    // 1. const int *p : valeur non modifiable via le pointeur
    const int *p1{&number1};
    std::cout << "p1 points to value: " << *p1 << '\n';
    // *p1 = 15; // ERREUR
    p1 = &number2; // OK

    // 2. int *const p : adresse non modifiable
    int *const p2{&number1};
    *p2 = 30; // OK
    // p2 = &number2; // ERREUR

    // 3. const int *const p : ni valeur ni adresse modifiable
    const int *const p3{&number1};
    std::cout << "p3 points to value: " << *p3 << '\n';
    // *p3 = 40; // ERREUR
    // p3 = &number2; // ERREUR

    return 0;
}
```



**Résultat attendu (exemple de sortie)**

```
p1 points to value: 10
p3 points to value: 30
```

*(Ici les erreurs sont volontairement commentées pour montrer les restrictions imposées par `const`)*



**Points pédagogiques à retenir**
- `const int *p` → la valeur est constante, l’adresse peut changer.  
- `int *const p` → l’adresse est constante, la valeur peut changer.  
- `const int *const p` → tout est constant.  
- L’utilisation de `const` améliore la sécurité et la lisibilité du code.  
- En C++ moderne, on privilégie `const` pour éviter les modifications involontaires.  





**2.10. Structure `etudiant` et gestion mémoire**

**Explication détaillée**

En programmation, une **structure** permet de regrouper plusieurs champs sous un même type.  
Ici, nous définissons une structure `etudiant` avec trois champs :  
- `matricule` (identifiant)  
- `nom` (chaîne de caractères)  
- `age` (entier)

Ensuite, nous allons voir deux manières d’instancier et de libérer cette structure :  
1. **En C (C)** avec `malloc` et `free`  
2. **En C++ (C++)** avec `new` et `delete`



**Exemple en **C — malloc/free****

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure étudiant
struct Etudiant {
    int matricule;
    char nom[50];
    int age;
};

// Fonction qui instancie et supprime la structure avec malloc/free
void testEtudiantMalloc(void) {
    // Allocation dynamique
    struct Etudiant *etudiant = malloc(sizeof(struct Etudiant));
    if (etudiant == NULL) {
        printf("Allocation failed\n");
        return;
    }

    // Initialisation des champs
    etudiant->matricule = 12345;
    strcpy(etudiant->nom, "Alice");
    etudiant->age = 20;

    // Utilisation
    printf("Etudiant (malloc): matricule=%d, nom=%s, age=%d\n",
           etudiant->matricule, etudiant->nom, etudiant->age);

    // Libération
    free(etudiant);
}

int main(void) {
    testEtudiantMalloc();
    return 0;
}
```

**Explications**
- `malloc(sizeof(struct Etudiant))` → réserve de la mémoire sur la heap.  
- `->` permet d’accéder aux champs via le pointeur.  
- `free(etudiant)` libère la mémoire.  



**Exemple en **C++ — new/delete****

```cpp
#include <iostream>
#include <string>

// Définition de la structure étudiant (style C++)
struct Etudiant {
    int matricule;
    std::string nom;
    int age;
};

// Fonction qui instancie et supprime la structure avec new/delete
void testEtudiantNew() {
    // Allocation dynamique
    Etudiant *etudiant = new Etudiant;

    // Initialisation des champs
    etudiant->matricule = 54321;
    etudiant->nom = "Bob";
    etudiant->age = 22;

    // Utilisation
    std::cout << "Etudiant (new): matricule=" << etudiant->matricule
              << ", nom=" << etudiant->nom
              << ", age=" << etudiant->age << '\n';

    // Libération
    delete etudiant;
}

int main() {
    testEtudiantNew();
    return 0;
}
```

**Explications**
- `new Etudiant` → réserve de la mémoire sur la heap et appelle le constructeur par défaut.  
- `->` permet d’accéder aux champs.  
- `delete etudiant` libère la mémoire et appelle le destructeur si nécessaire.  



**Résultat attendu (exemple de sortie)**

```
Etudiant (malloc): matricule=12345, nom=Alice, age=20
Etudiant (new): matricule=54321, nom=Bob, age=22
```



**Différences entre malloc/free et new/delete**

| Aspect                  | malloc/free (C)                  | new/delete (C++)                  |
|--------------------------|----------------------------------|-----------------------------------|
| Langage                 | C (C)                         | C++ (C++)                       |
| Initialisation           | Ne fait qu’allouer la mémoire   | Appelle le constructeur            |
| Libération               | `free`                         | `delete` (appelle le destructeur) |
| Type safety              | Retourne `void*` → cast souvent nécessaire | Retourne directement le bon type |
| Utilisation              | Bas niveau, manuel              | Plus haut niveau, orienté objet   |



**Points pédagogiques à retenir**
- En C, on utilise `malloc/free` pour gérer la mémoire.  
- En C++, on utilise `new/delete`, plus sûrs et intégrés au modèle objet.  
- Les deux nécessitent une libération explicite pour éviter les fuites mémoire.  
- La syntaxe `->` est indispensable pour accéder aux champs d’une structure via un pointeur.  






**2.11. Différences entre malloc/free et new/delete**

**Explication détaillée**

**1. malloc/free (C)**
- `malloc` : alloue un bloc de mémoire brute sur la heap.  
- Retourne un pointeur de type `void*` → nécessite souvent un cast.  
- Ne fait **aucune initialisation** des données.  
- `free` : libère la mémoire allouée.  
- Utilisé dans le langage C et disponible en C++ pour compatibilité.

**2. new/delete (C++)**
- `new` : alloue de la mémoire sur la heap **et appelle le constructeur**.  
- Retourne directement un pointeur du bon type (pas besoin de cast).  
- Peut initialiser la variable avec une valeur.  
- `delete` : libère la mémoire et appelle le destructeur si nécessaire.  
- Spécifique au C++ et intégré au modèle orienté objet.



## 🖥️ Exemple en **C — malloc/free**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Allocation avec malloc
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    // Initialisation manuelle
    *p = 42;
    printf("Value allocated with malloc: %d\n", *p);

    // Libération
    free(p);

    return 0;
}
```

Ici, `malloc` réserve de la mémoire brute. On doit initialiser manuellement la valeur.



**Exemple en **C++ — new/delete****

```cpp
#include <iostream>

int main() {
    // Allocation avec new
    int *p = new int(42); // initialisation directe

    std::cout << "Value allocated with new: " << *p << '\n';

    // Libération
    delete p;

    return 0;
}
```

Ici, `new` réserve la mémoire et initialise directement la valeur à 42.



**Résultat attendu (exemple de sortie)**

```
Value allocated with malloc: 42
Value allocated with new: 42
```



**Comparaison synthétique**

| Aspect                  | malloc/free (C)                  | new/delete (C++)                  |
|--------------------------|----------------------------------|-----------------------------------|
| Langage                  | C (C)                            | C++ (C++)                         |
| Initialisation           | Non (mémoire brute)              | Oui (constructeur, valeur initiale) |
| Type safety              | Retourne `void*` → cast souvent nécessaire | Retourne directement le bon type |
| Libération               | `free`                           | `delete` (appelle destructeur)    |
| Usage                    | Bas niveau, manuel              | Plus haut niveau, orienté objet   |



**Points pédagogiques à retenir**
- `malloc/free` → bas niveau, pas d’initialisation, utilisé en C.  
- `new/delete` → haut niveau, initialise et appelle constructeurs/destructeurs, utilisé en C++.  
- En C++ moderne, on privilégie `new/delete` (ou mieux : `std::unique_ptr`, `std::shared_ptr`).  
- En C, `malloc/free` reste incontournable pour la gestion mémoire.  






**2.12. Les dangers des pointeurs**

**Explication détaillée**

Les pointeurs sont puissants mais dangereux. Une mauvaise utilisation peut provoquer des comportements indéfinis (**Undefined Behaviour, UB**) : le programme peut planter, donner des résultats incohérents, ou même sembler fonctionner correctement tout en étant faux.



**Cas principaux d’Undefined Behaviour (UB)**

1. **Déréférencement d’un pointeur non initialisé**  
   - Lire ou écrire via un pointeur qui n’a pas été assigné.  

2. **Déréférencement d’un pointeur `NULL`**  
   - Lire ou écrire via un pointeur nul.  

3. **Déréférencement d’un pointeur libéré (use-after-free)**  
   - Utiliser un pointeur après avoir libéré la mémoire.  

4. **Double libération (double free)**  
   - Libérer deux fois la même adresse mémoire.  

5. **Buffer overflow**  
   - Écrire en dehors des limites d’un tableau.  

6. **Arithmétique invalide sur pointeurs**  
   - Déplacer un pointeur en dehors de la zone mémoire valide.  

7. **Conversion incorrecte de types (aliasing)**  
   - Interpréter une zone mémoire avec un type incompatible.  



**Exemples concrets en **C****

**1. Pointeur non initialisé**
```c
#include <stdio.h>

int main(void) {
    int *p; // non initialisé
    // printf("%d\n", *p); // UB : déréférencement invalide
    return 0;
}
```



**2. Pointeur NULL**
```c
#include <stdio.h>

int main(void) {
    int *p = NULL;
    // printf("%d\n", *p); // UB : déréférencement de NULL
    return 0;
}
```



3. Use-after-free
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    *p = 42;
    free(p);
    // printf("%d\n", *p); // UB : utilisation après libération
    return 0;
}
```



**4. Double free**
```c
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    free(p);
    // free(p); // UB : libération deux fois
    return 0;
}
```



**5. Buffer overflow**
```c
#include <stdio.h>

int main(void) {
    int arr[3] = {1, 2, 3};
    // arr[3] = 10; // UB : dépassement de tableau
    return 0;
}
```



**6. Arithmétique invalide**
```c
#include <stdio.h>

int main(void) {
    int arr[3] = {1, 2, 3};
    int *p = arr;
    // printf("%d\n", *(p + 10)); // UB : accès hors limites
    return 0;
}
```



**7. Aliasing incorrect**
```c
#include <stdio.h>

int main(void) {
    double d = 3.14;
    int *p = (int*)&d; // UB : interprétation incorrecte
    // printf("%d\n", *p);
    return 0;
}
```



**Points pédagogiques à retenir**
- Les pointeurs sont puissants mais dangereux.  
- Les erreurs classiques : pointeur non initialisé, NULL, use-after-free, double free, buffer overflow.  
- Ces erreurs provoquent des comportements indéfinis (UB).  
- En C++ moderne, on réduit ces risques avec des smart pointers (`std::unique_ptr`, `std::shared_ptr`).  
- En C, il faut être extrêmement rigoureux pour éviter ces pièges.





**2.13. Arithmétique des pointeurs**

**Explication détaillée**

Les pointeurs ne sont pas de simples adresses : on peut effectuer des opérations arithmétiques dessus.  
⚠️ Attention : ces opérations sont **limitées et dangereuses** si mal utilisées.

**1. Addition d’un entier à un pointeur**
- `p + n` → déplace le pointeur de `n` éléments (pas `n` octets).  
- Exemple : si `p` est un `int*`, `p + 1` pointe vers l’élément suivant du tableau.

**2. Soustraction d’un entier à un pointeur**
- `p - n` → recule le pointeur de `n` éléments.  
- Exemple : `p - 1` pointe vers l’élément précédent.

**3. Soustraction de deux pointeurs**
- `p2 - p1` → donne le nombre d’éléments entre deux pointeurs.  
- ⚠️ Valide uniquement si les deux pointeurs pointent dans le **même tableau**.

**4. Incrémentation/décrémentation**
- `p++` → avance d’un élément.  
- `p--` → recule d’un élément.



**Exemple en **C****

```c
#include <stdio.h>

int main(void) {
    int numbers[5] = {10, 20, 30, 40, 50};
    int *p = numbers; // pointe vers numbers[0]

    // Addition
    printf("p points to: %d\n", *p);       // 10
    printf("p+2 points to: %d\n", *(p+2)); // 30

    // Soustraction
    int *q = &numbers[4]; // pointe vers numbers[4]
    printf("q points to: %d\n", *q);       // 50
    printf("q-2 points to: %d\n", *(q-2)); // 30

    // Soustraction de pointeurs
    int distance = q - p; // nombre d'éléments entre q et p
    printf("Distance between q and p: %d\n", distance); // 4

    return 0;
}
```



**Exemple en **C++****

```cpp
#include <iostream>

int main() {
    int numbers[5]{10, 20, 30, 40, 50};
    int *p{numbers}; // pointe vers numbers[0]

    // Addition
    std::cout << "p points to: " << *p << '\n';       // 10
    std::cout << "p+2 points to: " << *(p+2) << '\n'; // 30

    // Soustraction
    int *q{&numbers[4]}; // pointe vers numbers[4]
    std::cout << "q points to: " << *q << '\n';       // 50
    std::cout << "q-2 points to: " << *(q-2) << '\n'; // 30

    // Soustraction de pointeurs
    int distance = q - p;
    std::cout << "Distance between q and p: " << distance << '\n'; // 4

    return 0;
}
```



**Résultat attendu (exemple de sortie)**

```
p points to: 10
p+2 points to: 30
q points to: 50
q-2 points to: 30
Distance between q and p: 4
```



**Points pédagogiques à retenir**
- L’arithmétique des pointeurs est basée sur le **type pointé** (pas sur les octets).  
- `p + n` → avance de `n` éléments.  
- `p - n` → recule de `n` éléments.  
- `p2 - p1` → donne la distance en nombre d’éléments.  
- ⚠️ Ces opérations ne sont valides que dans le **même tableau**.  
- Hors limites → **Undefined Behaviour (UB)**.  









