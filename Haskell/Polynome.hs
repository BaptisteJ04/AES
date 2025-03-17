module Polynome where
import Anneau
import Corps
import Z_sur_2Z

newtype Polynome a= Pol [a] deriving (Show) --[2,3,7]=2+3X+7X²
                                            -- On decide que []=[0]= le polynome nul

{-On untilise (Corps a) => dans la definition de nos fonctions
pour forcer les coefficient de nos polynomes à apartenir à des corps-}

addPol:: (Corps a) => Polynome a-> Polynome a-> Polynome a
--Prend en entré deux polynome et renvoie leur somme
addPol (Pol []) (Pol l) = Pol l
addPol (Pol l) (Pol []) = Pol l
addPol (Pol (x:xs)) (Pol  (y:ys)) = let Pol l = (addPol (Pol xs) (Pol ys)) in Pol ((operationadd x y):l)

multPol:: (Corps a) => Polynome a-> Polynome a-> Polynome a
--Prend en entré deux polynome et renvoie leur produit
multPol (Pol []) _ = Pol []
multPol _ (Pol []) = Pol []
multPol (Pol (x:xs)) (Pol l) = let Pol l1 = multPol (Pol xs) (Pol l) in addPol (Pol (map (operationmult x)(l))) (Pol (neutreadd:l1))

inverseaddPol:: (Corps a) => Polynome a-> Polynome a
--Prend en entré un polynome et renvoie leur produit
inverseaddPol (Pol []) = Pol []
inverseaddPol (Pol (x:xs))=let Pol l = inverseaddPol (Pol xs) in Pol ((inverseadd x):l)

instance  (Corps a) => Anneau (Polynome a) where
--creation des l'anneau des polynomes à cofficient dans un corp
  neutre1 = Pol [neutreadd]
  neutre2 = Pol [neutremult] 
  inverse x = inverseaddPol x
  operation1 a b = addPol a b
  operation2 a b = multPol a b


{-retournerPol :: (Corps a) => Polynome a-> Polynome a
retournerPol (Pol []) = Pol []
retournerPol (Pol (x:xs)) = let Pol l = retournerPol (Pol xs) in Pol (l ++ [x])-}

normalize_Pol :: (Corps a) => Polynome a-> Polynome a
--prend un polynome et y enleve les '0' inutiles (le reduit au plus petit degré possible)
normalize_Pol (Pol []) = Pol []
normalize_Pol (Pol l) | is_eq (take_last (Pol l)) neutreadd = normalize_Pol ((cut_last (Pol l)))
                           | otherwise =  (Pol l) 

degres_Pol :: (Corps a) => Polynome a-> Int 
--s'applique sur des polynomes "normalizés" et renvoie son degré
degres_Pol (Pol []) = -1
degres_Pol (Pol [x]) = if is_eq x neutreadd then -1 else 0
degres_Pol (Pol l) = length l -1

crea_pol_m:: (Corps a) => a-> Int -> Polynome a
--cree un polynome du degré de l'int donné et de coefficient de plus haut degré a
crea_pol_m a 0 = Pol [a]
crea_pol_m a x = let Pol l = crea_pol_m a (x-1) in Pol (neutreadd:l)

cut_last :: (Corps a) => Polynome a-> Polynome a
--supprime coefficient de plus haut degré d'un polynome
cut_last (Pol []) = Pol []
cut_last (Pol [x]) = Pol []
cut_last (Pol (x:xs)) = let Pol l = cut_last (Pol xs) in Pol (x: l)

take_last :: (Corps a) => Polynome a -> a
--renvoie coefficient de plus haut degré d'un polynome
take_last (Pol [x]) = x
take_last (Pol (x:xs)) = take_last (Pol xs)

egalite_pol :: (Corps a) => Polynome a -> Polynome a -> Bool
--teste l'egalité entre deux polynome (true si egalité false sinon)
egalite_pol (Pol []) (Pol []) = True
egalite_pol (Pol [neutreadd]) (Pol []) = True
egalite_pol (Pol []) (Pol [neutreadd]) = True
egalite_pol (Pol (x:xs)) (Pol []) = False
egalite_pol (Pol []) (Pol (x:xs)) = False
egalite_pol (Pol (x:xs)) (Pol (y:ys)) |(degres_Pol (Pol (x:xs))) ==  (degres_Pol (Pol (y:ys))) = if (is_eq x y) then egalite_pol (Pol xs) (Pol ys) else False
                                      |otherwise = False


division_pol :: (Corps a) => Polynome a-> Polynome a-> Polynome a 
--renvoie le quotient de la division euclidienne du premier pol par le deuxième
division_pol (Pol l) (Pol []) = Pol []
division_pol (Pol l1) (Pol l2) | degres_Pol (Pol l1) < degres_Pol (Pol l2) = Pol [neutreadd]
                               | is_eq (take_last (Pol l1)) neutreadd = division_pol (cut_last (Pol l1)) (Pol l2)
                               | is_eq (take_last (Pol l2)) neutreadd = division_pol (Pol l1) (cut_last (Pol l2)) 
                               | otherwise = let m = crea_pol_m (operationmult (take_last (Pol l1)) (inversemult (take_last (Pol l2)))) (degres_Pol (Pol l1) - degres_Pol (Pol l2)) in 
                                           addPol  m (division_pol ((addPol (Pol l1) (inverseaddPol (multPol m (Pol l2))))) (Pol l2))

modulo_pol :: (Corps a) => Polynome a-> Polynome a-> Polynome a
--renvoie le reste de la division euclidienne du premier pol par le deuxième
modulo_pol (Pol l1) (Pol l2) = normalize_Pol (addPol (Pol l1) (inverse (multPol (Pol l2) (division_pol (Pol l1) (Pol l2)))))

addmodulo :: (Corps a) => Polynome a -> Polynome a -> Polynome a -> Polynome a
--addation du premier polynome et du deuxième modulo le troisième
addmodulo (Pol l1) (Pol l2) (Pol l3) = modulo_pol (addPol (Pol l1) (Pol l2)) (Pol l3) 

multmodulo :: (Corps a) => Polynome a -> Polynome a -> Polynome a -> Polynome a
--multiplication du premier polynome et du deuxième modulo le troisième
multmodulo (Pol l1) (Pol l2) (Pol l3) = modulo_pol (multPol (Pol l1) (Pol l2)) (Pol l3) 

inverseaddmodulo :: (Corps a) => Polynome a -> Polynome a -> Polynome a 
--opposé du premier polynome modulo le deuxième
inverseaddmodulo (Pol l1) (Pol l2)  = modulo_pol (inverseaddPol (Pol l1)) (Pol l2) 

--premier_pol :: (Corps a) => Polynome a -> Polynome a -> Polynome a 
--premier_pol (Pol l) (Pol [neutreadd]) = Pol l
--premier_pol (Pol l1) Pol (Pol l2) = premier_pol (Pol l2) (modulo_pol (Pol l1) Pol (Pol l2))

algo_euclide_et :: (Corps a) => Polynome a -> Polynome a -> (Polynome a , Polynome a , Polynome a)
--algo d'euclide pour déterminer l'inverse modulo
algo_euclide_et (Pol l1) (Pol l2) = euclide_aux (Pol l1) (Pol l2) (Pol[neutremult]) (Pol[neutreadd]) (Pol[neutreadd]) (Pol[neutremult])

euclide_aux :: (Corps a) => Polynome a -> Polynome a -> Polynome a -> Polynome a -> Polynome a -> Polynome a ->(Polynome a , Polynome a , Polynome a)
euclide_aux (Pol l1) (Pol l2) (Pol l3) (Pol l4) (Pol l5) (Pol l6) |egalite_pol (Pol l2) (Pol [neutreadd]) = ((Pol l1),(Pol l3),(Pol l5))
                                                                  | otherwise = let ((Pol r), (Pol q)) = (modulo_pol (Pol l1) (Pol l2), division_pol (Pol l1) (Pol l2)) in
                                                                       euclide_aux (Pol l2) (Pol r) (Pol l5) (Pol l6) (addPol (Pol l3) (inverseaddPol(multPol (Pol l5) (Pol q)))) (addPol (Pol l4) (inverseaddPol(multPol (Pol l6) (Pol q))))

                                                                       
inverse_modulo :: (Corps a) => Polynome a -> Polynome a ->  Polynome a
--inverse du premier polynome modulo le deuxième
inverse_modulo (Pol l1) (Pol l2) = l3
  where (_, l3, _) = algo_euclide_et (Pol l1) (Pol l2) 
