### JOUBERT Baptiste & ALBINET Julien

# Bilan et explication du projet (Documentation du Binôme 11)

## Les fichiers

### Groups.hs et Anneau.hs
Ces fichiers renferment les classes `Groupe` et `Anneau` qui permettent de créer des groupes et des anneaux. Ils nous ont permis de créer mieux comprendre les classe et instance pour pouvoir coder `Corps.hs`, un fichier très utile car toutes nos opérations mathématiques du projet avaient lieu dans des ensembles de  polynomes à coefficient dans des corps.

### Corps.hs
Ce fichier renferme la classe `Corps`, qui nous a servi à définir les opérations et fonctions dans un corps afin de pouvoir utiliser AES.

### ZsurNZ.hs
Ce fichier renferme les types `Z_sur5Z` et `Z_sur_6Z` ainsi que les fonctions d'inverse et d'addition de ces groupes. Ces exemples ont servi plus tard à créer le corps `Z_sur2Z`.

### Z_sur_2Z.hs
Comme nous le disions auparavant, ce fichier renferme le corps `Z_sur_2Z` qui nous a servi plus tard à créer des bytes (1 ou 0). Nous l'avons initialisé en corps et non en groupe car, dans notre utilisation pour les polynômes et AES, nous avions besoin que ce soit un corps et non un groupe (le groupe aurait trop limité nos opérations sur ce type). De plus, nous avons initialisé toutes les opérations dans ce corps (addition, multiplication, inverse, égalité).

### Polynome.hs
Ce fichier renferme toutes les opérations sur les polynômes ainsi que la définition du type `Pol`, qui n'est ni plus ni moins qu'une liste de `a`. Nous avons choisi que le terme de plus petit degré serait en première position de la liste et le terme de plus haut degré en fin (exemple : 2x² + 1 donne [1, 0, 2]).  
En effet, en regardant comment il fallait coder les fonctions d'opérations sur les polynômes, nous avons trouvé plus simple d'opérer de cette manière. Les polynômes sont donc une instance d'anneau, avec un inverse, une addition et une multiplication. De plus toutes nos foncions et la declaration de l'anneau des polynomes ont une contrainte suplementaire imposant que les coefficients de nos polynomes soit dans des corps. Nous avons imposé cela car tous les polynomes que nous utiliserons par la suite respecterons cette contraintes et comme cela nous pouvons utiliser les fonctions définit sur les corps.
De plus, ce fichier contient des fonctions comme `take_last` ou `cut_last` qui servent à simplifier certaines fonctions de calcul. Finalement, il reste la fonction `algo_euclide` que nous avons utilisée pour trouver l'inverse modulo pour la multiplication. Toutes ces fonctions de modulo étant les prémices de la création du corps GF(2^8) qui nous servira à encoder des octets pour AES.

### GF28.hs
Dans ce fichier, nous avons écrit les fonctions pour le corps GF(2^8). En effet, pour pouvoir représenter un octet, il nous fallait une représentation mathématique afin de pouvoir y effectuer les opérations que nous avions codées précédemment (`Z_sur_2Z` et polynômes).  
On crée un types plus specifiques car si l'ensembles de polynomesà coefficient dans un corps et un anneau, GF(2^8) est lui un anneau. 
Nous avons donc choisi de représenter chaque octet par un polynôme de degré inférieur ou égal à 7, afin d'avoir un polynôme à 8 coefficients. Pour représenter chaque byte, nous avons pris les coefficients de ce polynôme dans `Z_sur_2Z`. Nous avons donc un type GF28 qui est un polynôme à coefficients dans `Z_sur_2Z`, nous pouvions donc utiliser nos fonctions mathématiques sur des octets. Il ne nous restait donc plus qu'à faire les fonctions d'AES.

### AES.hs
Ce fichier contient la définition des colonnes. En effet, nous avons décidé de représenter les colonnes des blocs par des polynômes afin de pouvoir utiliser nos fonctions sur les colonnes.  
Les blocs sont eux des listes de colonnes.  

    -Pour `SubBytes`, nous l'avons implémentée en utilisant la multiplication par le polynôme donné dans le PDF sur AES. 
    -Pour `ShiftRows`, nous avons simplement déplacé les éléments de notre bloc. 
    -Pour `MixColumns`, nous avons codé une première version en utilisant le produit de matrice. Cependant, après le retour de M. Guisse, nous avons amélioré cette fonction en remplaçant le produit matriciel par un produit de polynômes. 
    -Pour `AddRoundKey`, c'est une addition de polynômes. 
    -Pour `KeySchedule`, nous avons plusieurs versions, qui permettent de s'adapter aux différents cas (128, 192 ou 256). Nous avons préféré faire trois fonctions distinctes plutôt qu'une modulable pour la facilité de code que cela impliquait.  

Ce fichier contient aussi toutes les fonctions inverse.

Finalement, nous avons décidé de rajouter des fonctions `hextobin` et `binthex` afin de simplifier la lecture des blocs lors des tests ainsi que l'écriture des tests.

### Cypher.hs
Ce fichier contient les deux fonctions finales, permettant d'encoder et de décoder avec AES. Ces deux fonctions utilisent les fonctions d'AES, qui elles-mêmes regroupent toutes les fonctions et classes contenues dans tous nos autres fichiers.

## Conclusion et retour sur la première partie du projet
Lors de cette partie en Haskell, nous avons rencontré plusieurs problèmes, tout d'abord sur l'organisation. Malgré l'effort que nous avions mis dès le début, il nous est arrivé de faire la même chose chacun de notre côté, ou bien d'avoir une mauvaise estimation du travail pour la séance d'après (notamment entre les séances 3 et 4).  
De plus, il nous est arrivé de ne pas assez communiquer sur nos avancements, ou de ne pas remplir le carnet de bord pour que l'autre sache ce qui avait été fait.  
Cependant, au fil des séances, nous nous sommes améliorés sur ces points et nous espérons pouvoir être efficaces dans la dernière ligne droite du projet dans trois semaines.