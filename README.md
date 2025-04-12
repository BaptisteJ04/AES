

# Implémentation d'AES en Haskell et en C
## Auteurs

    JOUBERT Baptiste 
    ALBINET Julien

## Description du projet

Ce projet est une implémentation complète de l'algorithme de chiffrement AES (Advanced Encryption Standard) en Haskell et en C. Il permet de chiffrer et déchiffrer des fichiers, notamment des images BMP, en utilisant AES sous différents modes (ECB, CBC).

L'implémentation en Haskell se concentre sur l'aspect mathématique d'AES, tandis que celle en C est optimisée pour le traitement de fichiers et la performance.
# Structure du projet
## Partie Haskell

L'implémentation Haskell se trouve dans le dossier Haskell/ et comprend plusieurs fichiers modulaires :

- AES.hs : Implémentation des transformations AES (SubBytes, ShiftRows, MixColumns, AddRoundKey).
- Anneau.hs, Corps.hs, Group.hs : Définition des structures mathématiques utilisées (groupes, anneaux, corps).
- Polynome.hs : Gestion des polynômes pour représenter les opérations de Galois Field GF(2⁸).
- GF28.hs : Implémentation du corps fini GF(2⁸), utilisé dans AES.
- Cypher.hs : Contient les fonctions de chiffrement et déchiffrement AES.
- Fichiers de test (test_AES.ghci, test_Cypher.ghci, etc.) : Scripts pour tester l'implémentation.

## Partie C

L'implémentation en C se trouve dans le dossier C/ et comprend plusieurs fichiers :

- F_AES.c / F_AES.h : Fonctions principales d'AES + Fonctions utilitaires.
- F_Inverse_AES.c / F_Inverse_AES.h : Fonctions de déchiffrement AES.
- cbc_encryption.c / cbc_encryption.h : Implémentation d'AES en mode CBC.
- ecb_encryption.c / ecb_encryption.h : Implémentation d'AES en mode ECB.
- bmp.c / bmp.h : Gestion des fichiers BMP (lecture, écriture).
- Table_de_multiplication.c : Table de multiplication pour GF(2⁸).
- tests_AES.c : Programme de test de l'implémentation AES en C.
- Makefile : Automatisation de la compilation du projet.

### Fonctionnalités

- Chiffrement/Déchiffrement AES (128, 192, 256 bits).
- Modes ECB et CBC pour le chiffrement.
- Support des fichiers BMP (pour observer visuellement l'effet du chiffrement).
- Tests unitaires en Haskell et en C.

## Compilation et Exécution
### Partie Haskell

Assurez-vous d'avoir GHC (Glasgow Haskell Compiler) installé. Pour tester l'implémentation Haskell :
'''bash
    ghci test_AES.ghci
'''
### Partie C

Pour compiler et exécuter le programme en C, utilisez Makefile :

'''bash
cd C
make
./tests_AES
'''

## Résultats et Analyse

L'implémentation a été testée sur des fichiers BMP, ce qui permet d'observer directement l'effet du chiffrement AES. En mode ECB, des motifs visuels restent visibles, tandis qu'en mode CBC, l'image est complètement brouillée, ce qui montre l'efficacité du mode CBC contre les attaques par motifs répétitifs.
### Améliorations possibles

- Optimisation des performances en C avec SIMD.
- Implémentation d'autres modes comme CTR ou GCM.
- Interface utilisateur pour simplifier l'utilisation.

# Conclusion

Ce projet a permis d'approfondir la compréhension d'AES et des mathématiques sous-jacentes, en comparant une approche fonctionnelle en Haskell et une approche impérative en C.