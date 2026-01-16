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





