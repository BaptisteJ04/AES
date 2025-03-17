module Anneau where
-------------------Definition de l'anneau-------------------------
class Anneau a where
  neutre1 :: a
  neutre2 :: a
  inverse :: a -> a
  operation1 :: a -> a -> a
  operation2 :: a -> a -> a

instance Anneau Integer where
  neutre1 = 0
  neutre2 = 1
  inverse x = -x
  operation1 a b = a + b
  operation2 a b = a * b

