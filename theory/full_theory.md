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







