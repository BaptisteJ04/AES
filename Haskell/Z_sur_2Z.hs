module Z_sur_2Z where
import Corps

newtype Z_sur_2Z = Z2Z Integer deriving (Show)

addMod2 :: Z_sur_2Z-> Z_sur_2Z -> Z_sur_2Z
--addition d'element de Z/2Z
--Prend en entrée les deux élément à additionner et renvoie le résultat
addMod2 (Z2Z x) (Z2Z y) = Z2Z $ (x+y) `mod` 2 

multMod2 :: Z_sur_2Z-> Z_sur_2Z -> Z_sur_2Z
--multiplication d'element de Z/2Z
--Prend en entrée les deux élément à multiplier et renvoie le résultat
multMod2 (Z2Z x) (Z2Z y) = Z2Z $ (x*y) `mod` 2 

inverseaddMod2 :: Z_sur_2Z-> Z_sur_2Z
--inverse pour l'addition dans Z/2Z
--Prend en entrée un élément de 2/2Z et renvoie son opposé
inverseaddMod2 (Z2Z x) = Z2Z x

inversemultMod2 :: Z_sur_2Z-> Z_sur_2Z 
--inverse pour la multiplication dans Z/2Z
--Prend en entrée un élément de 2/2Z et renvoie son inverse
inversemultMod2 (Z2Z 1) = Z2Z 1

egalite_Z2Z :: Z_sur_2Z-> Z_sur_2Z -> Bool
--fonction pour tester l'égalité dans Z/2Z
-- prend deux élément de Z/2Z et renvoie True s'ils sont égaux False sinon
egalite_Z2Z (Z2Z 0) (Z2Z 0) = True
egalite_Z2Z  (Z2Z 1) (Z2Z 1) = True
egalite_Z2Z _ _ = False

instance Corps Z_sur_2Z where
--définitin du corp Z/2Z
  neutreadd = Z2Z 0
  neutremult = Z2Z 1
  inverseadd = inverseaddMod2
  inversemult = inversemultMod2
  operationadd = addMod2
  operationmult = multMod2
  is_eq = egalite_Z2Z
