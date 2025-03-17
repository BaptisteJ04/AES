module GF28 where
import Anneau
import Corps
import Z_sur_2Z
import Polynome

newtype Gf28 = Gf (Polynome Z_sur_2Z) deriving (Show)
--ensemble des polynome de degré à coefficient dans Z/2Z

m ::  Polynome Z_sur_2Z
m = Pol [Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 1]

multPolgf28 ::  Gf28 -> Gf28 -> Gf28
--multplication dans GF2⁸
multPolgf28 (Gf l1) (Gf l2) = Gf (multmodulo l1 l2 m)

addPolgf28 :: Gf28 -> Gf28 -> Gf28
--addition dans GF2⁸
addPolgf28 (Gf l1) (Gf l2) = Gf(addmodulo l1 l2 m)

inverseaddPolgf28 :: Gf28 -> Gf28 
--opposé dans GF2⁸
inverseaddPolgf28 (Gf l) = Gf (inverseaddmodulo l  m)

is_eqgf :: Gf28 -> Gf28 -> Bool
--égalité dans GF2⁸
is_eqgf (Gf l1) (Gf l2) = egalite_pol l1 l2

inversemultPolgf28 :: Gf28 -> Gf28 
--inverse dans GF2⁸
inversemultPolgf28 (Gf l) = Gf (inverse_modulo l m)


instance  Corps Gf28 where
--instancation de GF2⁸ en tant que corps
  neutreadd = Gf (Pol [neutreadd])
  neutremult = Gf (Pol [neutremult])
  inverseadd a = inverseaddPolgf28 a
  inversemult a = inversemultPolgf28 a
  operationadd a b = addPolgf28 a b
  operationmult a b = multPolgf28 a b
  is_eq a b = is_eqgf a b
