JOUBERT Baptiste
ALBINET Julien
Binôme 11

# Carnet de Bord PX222 

## Partie implémentation HASKELL

### Première scéance

Lors de cette scéance, nous avons pris connaissance des consignes du projet, ainsi que du fonctionnement d'AES.
Nous avons aussi commencé le code en réalisant les définitions des groupes, des corps et des anneaux, mais sans les finir.

#### Pour la prochaine scéance il nous reste donc à faire :

    1) Terminer la définition des corps et des anneaux      (Baptiste)
    2) implémentation du corps à 2 éléments F2 = GF(2) = Z/2Z   (Julien)
    3) Implémentation (types, +,-,x) des anneaux des polynômes à coefficients dans un corps et tests sur des polynômes à coefficients dans F2   (Julien)
    4) implémentation du calcul modulo un polynôme (+,-,x) et tests avec le polynôme m d'AES
    5) implémentation de l'inverse modulo m dans F2[X]

### Entre la première scéance et la deuxième

Une fois les définitions des Corps et anneaux ayant été terminés.
Nous les avons utilisé définir le corp Z/2Z. Dans tout ce qui était démandé de faire, il nous fallait aussi implementer l'anneau des polynômes d'un corps.
Cependant, nous n'avons réussi à creer que l'Anneau des polynome à coefficient entier. 


### Deuxième scéance 

Lors de cette scéance, nous avons mis en commun les codes que nous avions fait entre les scéances.
Julien a terminé les polynômes à coefficents dans des corps, ce qui nous permet de rayer le point 3) de la to do list.  
Baptiste a avancé sur la fonction modulo de polynome en créant plusieurs fonctions utile à son écriture:
 
    -La première permet d'inverser un polynôme pour avoir son terme dominant en premier.
    -La seconde permet de simplifier les polynômes afin de ne pas avoir des 0 inutile dans le tableau représentatif.


#### Pour la prochaine scéance il nous reste donc à faire :

    4) implémentation du calcul modulo un polynôme (+,-,x) et tests avec le polynôme m d'AES (Baptiste et Julien)
    5) implémentation de l'inverse modulo m dans F2[X]

Pour la prochaine scéance, nous serons sur la même tache car la 5) nécéssite la tache 4) pour être faites.

### Entre la deuxième scéance et la troisième

Nous avons commencé par créer plusieurs fonctions afin de faciliter la manipulation des polynomes.

    -La premiére permet de déterminer le degrès d'un polynome
    -La deuxième de normaliser les polynomes (enlever tous les 0 à la fin de la liste)
    -Les deux autres fonctions ont pour but de recuperer et suprimer le dernier élement d'un polynome.

Pour s'avancer pour la prochaine scéance, nous avons codé la division euclidienne.
La fonction de la division euclidienne prend deux polynome et renvoie le quotient de la division, cette fonction nous permet donc de déduire facilement le modulo.

### Troisième scéance 

Lors de cette scéance, nous avons dans un premier temps crée des fonction nous permetant de faire l'opération modulo avec un polynome (+,*,-).
Dans un second temps, nous avons essayé de coder l'agoritme d'euclide etendue pour trouver l'inverse du modulo en fonction d'un polynome.

#### Pour la prochaine scéance il nous reste donc à faire :

    1) terminer l'implémentation d'euclide étendu pour obtenir l'inverse modulo 
    2) Réussir à encoder les polynome de GF(2^8)
    3) Implementer les opérations d'AES

Pour ces taches, ce sera Baptiste qui les réalisera avec l'aide de Julien étant donné qu'il n'a pu assisté à la scéance en cours


### Entre la troisième scéance et la quatrième

Nous avons terminer l'implémentation d'euclide étendu pour obtenir l'inverse modulo. Deplus nous avons commencé à encoder les polynômes de GF(2^8) c'est à dire des polynômes de polynôme à coefficients dans Z/2Z, cependant nous ne sommes pas sûr de notre implémentation. Il nous faudra donc demander confirmation à notre professeur.
Pour finir, nous avons aussi coder la fonction sub_bytes d'AES mais n'étant pas sûr de notre GF(2^8), la fonction n'est peut être pas bonne.

### Quatrième scéance 

Lors de cette scéance, nous avons demandé à notre professeur confirmation sur notre implémentation de GF(2^8) et comme nous le pensions, elle n'était pas juste. En effet GF(2^8) était bien plus simple car seulement des polynômes de degrès inférieur à 8 et à coefficients dans Z/2Z.
Nous avons donc du tout reprendre.
Finalement, nous avons refait notre implémentation de GF(2^8) et avons repris la fonction sub_bytes d'AES pour qu'elle fonctionne correctement. DE plus nous avons crée un type Bloc pour coder des bloc de polynômes.

#### Pour la prochaine scéance il faut donc faire :

    1) Terminer toutes les fonctions d'AES (sub_bytes, shift_rows, mix_columns et add_round_key)
    2) Implémenter la fonction cypher

    Si possible faire aussi :

    3) Les fonctions d'inverse d'AES (inv_sub_bytes, inv_shift_rows, inv_mix_columns et inv_add_round_key)
    4) Implémenter la fonction reverse_cypher


### Entre la quatrième scéance et la cinquième

Nous avons terminé les fonctions sub_bytes, shift_rows, mix_columns et add_round_key. De plus nous avons commencé les fonctions d'inverse. Il nous reste donc à finir les fonctions inverses manquantes et implementer cypher et inverse_cypher.

### Cinquième et dernière scéance

Pour cette dernière scéance, nous n'avions plus qu'à modifier certaines parties du code, notamment pour l'implementation de la routine de clé pour des clés de 192 et 256 bits. Cependant cela a été vite fait grace à notre implementation qui a permis une grosse versatilité sur ce point.
Nous avons donc vite finit cette tache. Ne nous laissant plus qu'avec quelques modifications mineures à terminer pour clore cette partie du projet et pouvoir serenement débuter l'implementation en C aprés.



## Partie implémentation C

### Avant le premier jour

Pour bien débuter notre semaine d'implémentation en C, nous avons décidé de commencer le projet le week-end du 15 et 16 juin. Nous avons donc commencé la construction de la S-box de la fonction `subbyte` ainsi que l'implémentation de cette dernière. De plus, nous avons ajouté quelques fonctions utilitaires pour faciliter la création de blocs et l'affichage de ceux-ci.

### Lundi 17/06 (Premier jour)

Nous avons débuté ce premier jour par un échec. En effet, lors du passage de notre professeur, nous avons découvert que l'utilisation de `char` pour stocker nos valeurs dans les blocs était une mauvaise idée. Nous sommes donc repartis de zéro en modifiant nos blocs (passant de tableaux de `char` vers des tableaux de `int`). Ensuite, nous nous sommes répartis les fonctions d'AES à coder :

- Julien s'est chargé d'implémenter :
    1) `subbyte`
    2) `add_round_key`

- Baptiste s'est chargé d'implémenter :
    1) `shift_rows`
    2) `mix_columns`

Il était aussi prévu que celui qui finirait sa to-do list en premier commence l'implémentation de `key_expansion`. À la fin de la matinée, nous avions déjà plus de la moitié de ces fonctions et étions en train d'implémenter les plus difficiles (`mix_columns`, `key_expansion`).

Durant l'après-midi, nous avons terminé `mix_columns`. Cependant, nous avons eu une remarque d'un élève de l'autre TD à propos de l'optimisation de `mix_columns`. Baptiste est donc reparti sur son implémentation de `mix_columns` pour l'optimiser pendant que Julien travaillait sur `key_expansion`.

#### Pour mardi il faut donc faire :
- finir `key_expansion`
- Implémenter les fonctions inverse d'AES
- réimplémenter `mix_columns` pour l'optimiser


### Mardi 18/06 (Deuxième jour)

Au début de ce second jour, Julien a terminé l'implémentation de `key_expansion` en 128 bits, mais il lui restait à faire 192 bits et 256 bits. En parallèle, Baptiste a commencé à travailler sur les fonctions d'inversion d'AES. 

En début d'après-midi, nous avions réussi à terminer l'implémentation de `key_expansion`, ainsi que de toutes les fonctions inverses d'AES. Cependant, il restait toujours ce problème d'optimisation de `mix_columns` à régler ainsi que l'implémentation de `cypher` et `inverse_cypher`. 

En fin d'après midi, nous avons donc un algorithme pour optimiser `mix_columns` en utilisant des tables de "transformés" pour réaliser la multiplication dans GF(2⁸). Pour générer ces tables, il a donc fallu utiliser le code non optimisé réalisé précédemment. En parallèle, nous avons aussi commencé l'implémentation de `cypher` et `inverse_cypher`. 

#### Pour mercredi il faut donc faire :
- finir `cypher` et `inverse_cypher`
- finir de réimplémenter `mix_columns` pour l'optimiser


### Mercredi 19/06 (Troisième jour)

Au début de ce troisième jour, Julien a continué d'implémenter `cipher` et `inverse_cipher`. Cependant, lors de l'implémentation de cypher, nous nous sommes rendu compte que nos tables générées pour la multiplication dans GF(2⁸) étaient incorrectes. Il a donc fallu les régénérer et, pour cela, refaire le code non optimisé de la multiplication (ce problème était dû à une erreur dans la multiplication par 2, qui était à la base des autres multiplications).

En début d'après-midi, Julien avait terminé l'implémentation de `cipher`, il a donc commencé `inverse_cipher`. Pendant ce temps, Baptiste s'est chargé de terminer de manière optimisée `mix_columns`.

En fin de journée, nous avions donc terminé `cipher` et `inverse_cipher` ainsi que l'optimisation de `mix_columns`. Nous avons alors commencé à nous renseigner sur l'implémentation de `ecb`.

#### Pour jeudi, il faut donc :
- Implémenter `ecb`


### Jeudi 20/06 (Quatrième jour)

Au début de cet avant-dernier jour, nous nous sommes penchés sur l'implémentation de `ecb`. Cela nous a pris toute la matinée et, en fin de matinée, nous avions l'encodage par AES de `ecb`. Cependant, nous avons rencontré un problème avec le décodage. Notre algorithme permet donc d'encoder des chaînes de caractères et des images avec le principe de `ecb`, mais une fois encryptés, nous n'arrivons pas à les décrypter.

#### Pour vendredi, il faut donc :
- Corriger le décryptage de `ecb`


### Vendredi 21/06 (Dernier jour)

Pour ce dernier jour, nous nous sommes dépêchés de terminer le cryptage avec `ecb` afin de pouvoir nous pencher au plus vite sur l'implémentation de `cbc`.

En fin de matinée, nous avions terminé `ecb`. Il nous était donc possible de crypter et décrypter l'image donnée. Cependant, nous avons décidé de nous repencher sur `key_expansion` afin d'avoir un en-tête conforme à celui demandé.

En début d'après-midi, nous avons attendu notre tour pour passer en soutenance. En attendant, nous avons mis ce temps à profit pour terminer de modifier `key_expansion` et répéter notre présentation à venir.


