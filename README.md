# Projet : Simple Shell

Ce projet consiste à créer un interpréteur de cmdes UNIX, également appelé shell, en respectant des normes de qualité de code, de collaboration et de fonctionnalité spécifiques.

## Objectifs d'Apprentissage

À la fin de ce projet, l'objectif est de pouvoir expliquer sans assistance externe :

- L'histoire et les créateurs du système d'exploitation Unix.
- Les bases du fonctionnement d'un shell.
- Les concepts de PID (Process ID) et PPID (Parent Process ID).
- La manipulation de l'environnement d'un processus.
- La différence entre une fonction et un appel système.
- La création et la gestion de processus.
- Les trois prototypes de la fonction main.
- L'utilisation du PATH pour trouver des programmes.
- L'exécution d'un programme externe avec l'appel système execve.
- La suspension de l'exécution d'un processus jusqu'à ce qu'un enfant se termine.
- La signification d'EOF (End-of-File).

## Exigences du Projet

### Code et Collaboration

- Respecter le style de codage Betty.
- Limiter chaque fichier à un maximum de 5 fonctions.
- Utiliser des gardiens d'inclusion de fichiers d'en-tête.
- Aucune fuite de mémoire autorisée.
- Collaboration avec un partenaire sans création de doublons de répertoires.

### Compilation et Tests

- Compiler avec `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`.
- Tests en mode interactif et non interactif.
- Créer un fichier README.md et AUTHORS.

### Fonctions et Appels Systèmes Autorisés

- Utilisation spécifique des fonctions et appels système autorisés.

## Compilation et Tests Exemples

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
./hsh
# Interactive mode example
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

# Non-interactive mode example
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
