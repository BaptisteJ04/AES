### JOUBERT Baptiste & ALBINET Julien

# Bilan et explication du projet (Documentation du Binôme 11)

## Les fichiers

### F_AES.c - Fonctions AES

Le fichier **F_AES.c** contient l'implémentation des différentes fonctions utilisées dans l'algorithme de chiffrement AES. Voici une description des fonctions principales et de leur rôle dans le processus de chiffrement/déchiffrement.

#### Variables Globales
Le fichier définit plusieurs matrices et blocs utilisés dans le processus AES :

- `mat_mix[4][4]` : La matrice de mélange utilisée pour l'opération **MixColumns**.
- `bloc_initial[4][4]` : Le bloc de texte brut initial à chiffrer.
- `bloc_test[4][4]` : Un bloc de test servant à vérifier le bon fonctionnement des opérations.
- `bloc_add_round_key[4][4]` : Le bloc après l'ajout de la clé de ronde.
- `bloc_apres_add_round_key[4][4]` : Le bloc après l'opération **AddRoundKey**.
- `bloc_apres_sub_bytes[4][4]` : Le bloc après l'opération **SubBytes**.
- `bloc_apres_shift_rows[4][4]` : Le bloc après l'opération **ShiftRows**.
- `bloc_apres_mix_columns[4][4]` : Le bloc après l'opération **MixColumns**.

#### Fonctions Utilitaires
Ces fonctions sont utilisées pour manipuler les blocs de données et effectuer des opérations de bas niveau :

- **egalite_bloc** : Vérifie l'égalité entre deux blocs de 4x4 octets.
- **egalite_tableau** : Vérifie l'égalité entre deux tableaux de 4 éléments.
- **rotmat** : Effectue une rotation de 90 degrés de la matrice de 4x4 octets.
- **copieb** : Copie un tableau 2D de blocs dans un autre.
- **copiec** : Copie une colonne de 4 octets d'un tableau dans une autre.
- **xor** : Effectue une opération XOR entre deux colonnes de 4 octets.
- **crea_tab** : Crée un tableau de blocs à partir d'une phrase (utile pour l'initialisation des blocs).
- **print_bloc** : Affiche un bloc 4x4 dans la console.
- **print_tableau** : Affiche un tableau de 4 éléments dans la console.
- **rotword** : Effectue une rotation de mot sur une colonne, utilisée dans l'expansion de clé.

#### Opérations AES

1. **SubBytes**
   - **subbytes** : Applique l'opération **SubBytes** sur un bloc de 4x4 octets, où chaque octet est remplacé par son équivalent dans la table S-Box.
   - **subbytesCol** : Applique **SubBytes** sur une colonne de 4 octets.

2. **AddRoundKey**
   - **Add_RK** : Effectue l'addition (XOR) du bloc de données avec une clé de ronde spécifique.

3. **ShiftRows**
   - **decalageg** : Effectue un décalage d'une ligne du bloc de texte de `num_dec` positions.
   - **shift_rows** : Applique l'opération **ShiftRows** sur un bloc de 4x4 octets en décalant les lignes du bloc selon les règles de l'algorithme AES.

4. **MixColumns**
   - **mult_mix_gf** : Effectue une multiplication dans le corps GF(2^8), utilisée pour l'opération **MixColumns**.
   - **mix_columns** : Applique l'opération **MixColumns** sur un bloc de 4x4 octets en multipliant chaque colonne par une matrice de mixage.

5. **Expansion de Clé**
   - **decoupe192** : Découpe la clé de 192 bits en plusieurs parties nécessaires pour l'expansion de clé.
   - **decoupe256** : Découpe la clé de 256 bits en plusieurs parties nécessaires pour l'expansion de clé.
   - **list_key_to_word** : Convertit une liste de clés en un tableau de mots de 4 octets pour l'expansion de clé.
   - **KeyExp** : Effectue l'expansion de clé pour générer toutes les clés de ronde à partir de la clé initiale.
   - **extrat_key** : Extrait une clé de ronde à partir de l'expansion de clé pour un tour donné.

---
  
### F_inverse_AES.c - Fonctions AES Inverses

Le fichier **F_inverse_AES.c** contient l'implémentation des différentes fonctions inverses utilisées dans l'algorithme AES pour le déchiffrement. Voici une description des fonctions principales et de leur rôle dans le processus de déchiffrement.

#### 1. **Inverse_Sub_bytes**
- **Inverse_Sub_bytes** : Cette fonction applique l'opération **Inverse SubBytes** sur un bloc de 4x4 octets, où chaque octet du bloc est remplacé par son équivalent dans la table S-Box inverse, utilisée dans le processus de déchiffrement d'AES.

#### 2. **Inverse_Shift_rows**
- **decalaged** : Effectue un décalage d'une ligne de 4 octets d'un bloc dans le sens inverse de l'opération **ShiftRows**, en fonction du nombre de décalages spécifié (`num_dec`).
- **Inverse_Shift_rows** : Applique l'opération **Inverse ShiftRows** sur un bloc de 4x4 octets en réarrangeant les lignes du bloc selon l'inverse des règles de l'algorithme AES de chiffrement.

#### 3. **Inverse_Mix_Colonne**
- **mult_inverse_mix_gf** : Effectue une multiplication de deux éléments dans le corps GF(2^8) utilisée pour l'opération inverse de multiplication dans **Inverse MixColumns**.
- **Inverse_Mix_Colonne** : Applique l'opération **Inverse MixColumns** sur un bloc de 4x4 octets en multipliant chaque colonne du bloc par une matrice inverse de mixage. Cela permet de récupérer l'information après l'opération **MixColumns** réalisée lors du chiffrement.

---


## Conclusion et retour sur la deuxième partie du projet
Lors de cette partie en Haskell, nous avons rencontré plusieurs problèmes, tout d'abord sur l'organisation. Malgré l'effort que nous avions mis dès le début, il nous est arrivé de faire la même chose chacun de notre côté, ou bien d'avoir une mauvaise estimation du travail pour la séance d'après (notamment entre les séances 3 et 4).  
De plus, il nous est arrivé de ne pas assez communiquer sur nos avancements, ou de ne pas remplir le carnet de bord pour que l'autre sache ce qui avait été fait.  
Cependant, au fil des séances, nous nous sommes améliorés sur ces points et nous espérons pouvoir être efficaces dans la dernière ligne droite du projet dans trois semaines.