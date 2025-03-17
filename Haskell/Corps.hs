module Corps where
-------------------Definition du corps-------------------------
class Corps a where
  neutreadd :: a
  neutremult :: a
  inverseadd :: a -> a
  inversemult :: a -> a
  operationadd :: a -> a -> a
  operationmult :: a -> a -> a
  is_eq :: a->a->Bool

-------------------Definition du corps (R,+,*)-------------------------
instance Corps Float where
  neutreadd = 0
  neutremult = 1
  inverseadd x = -x
  inversemult x = 1/x
  operationadd a b = a + b
  operationmult a b = a * b
  is_eq a b = a==b

newtype Reel = R Float deriving (Show)

inverseaddR :: Reel -> Reel
inverseaddR (R x) =R (-x ) 

inversemultR :: Reel -> Reel
inversemultR (R x) =R (1/x) 

operationaddR :: Reel -> Reel -> Reel
operationaddR (R x) (R y) =R (x+y)  

operationmultR :: Reel -> Reel -> Reel
operationmultR (R x) (R y) =R (x*y)  

is_eqR :: Reel -> Reel -> Bool
is_eqR (R x) (R y) = x==y  

instance Corps Reel where
  neutreadd = R 0.0
  neutremult = R 1.0
  inverseadd = inverseaddR 
  inversemult = inversemultR 
  operationadd = operationaddR 
  operationmult = operationmultR 
  is_eq = is_eqR 