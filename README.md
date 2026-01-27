```markdown
# TP8 - Les pointeurs

Ce projet regroupe la partie **théorique** et la partie **pratique** du TP8 sur les pointeurs en C/C++.

**Partie théorique**
La théorie est disponible dans le dossier :
```
theory/full_theory.md
```
Elle couvre :
- La mémoire (stack, heap, segments)
- Définition et utilisation des pointeurs
- Références et passage de paramètres
- Exemples de pointeurs (int, char, tableau, pointeur de pointeur, pointeur sur fonction)
- Const et pointeurs
- Structure `etudiant` et gestion mémoire
- Différences malloc/free et new/delete
- Dangers des pointeurs (UB, buffer overflow, use-after-free, double free)
- Arithmétique des pointeurs

**Partie pratique**
Le code C++20 est disponible dans :
```
practical/main.cpp
```
Il contient :
- Pointeur simple sur int et déréférencement
- Exemples pratiques de pointeurs (int, char, tableau, tableau de pointeurs, pointeur de pointeur, pointeur sur fonction)
- Cas d’utilisation de `const` avec les pointeurs
- Structure `Student` avec allocation/libération via `malloc/free` et `new/delete`
- Arithmétique des pointeurs
- Exemples de comportements indéfinis (UB) commentés

**Compilation et exécution**
Pour compiler et exécuter la partie pratique :

```bash
g++ -std=c++20 practical/main.cpp -o tp8
./tp8
```

## Auteur
Projet réalisé par **Cedric-Vincent-dev** dans le cadre du TP8 sur les pointeurs.
```
```
Add README.md with project overview
```

