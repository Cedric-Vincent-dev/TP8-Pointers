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

