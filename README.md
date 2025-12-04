# Red-Black Tree en C++

Ce projet contient une implémentation d'un **arbre rouge-noir** (Red-Black Tree) en C++ pour stocker et rechercher des chaînes de caractères.

## Description

L'application lit un fichier texte `chaines.txt`, charge tous les mots dans un arbre rouge-noir, et permet de rechercher un mot spécifique tout en mesurant le temps de chargement et le temps moyen de recherche.  

### Fonctionnalités

- Insertion de chaînes de caractères dans un arbre rouge-noir.
- Recherche d'un mot dans l'arbre.
- Mesure du temps de chargement et du temps moyen de recherche.
- Gestion automatique des doublons.

## Fichiers

- `main.cpp` : code source principal contenant l'implémentation de l'arbre et la logique de chargement/recherche.
- `chaines.txt` : fichier texte contenant les mots à charger (à fournir).

## Compilation et exécution

Pour compiler et exécuter le programme sur un système Unix (Linux/macOS) avec `g++` :

```bash
g++ -std=c++17 -o rbt main.cpp
./rbt
