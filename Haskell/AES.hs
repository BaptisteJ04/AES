module AES where
import Anneau
import Corps
import Z_sur_2Z
import Polynome
import GF28


newtype Colone_AES = Col (Polynome Gf28) deriving (Show)
--colone d'un bloc AES binaire (considéré comme un polynome à coefficient dan GF2⁸)
newtype Bloc_AES = Blc ([Colone_AES]) deriving (Show)
--Bloc d'AES avec ses coefficient en binaires
newtype Bloc_AES_hexa = Blch ([[String]]) deriving (Show)
--Bloc d'AES avec ses coefficient en hexadécimal


-----------SubByte


sub_octet_mult::  Polynome Z_sur_2Z
sub_octet_mult = Pol [Z2Z 1,Z2Z 1,Z2Z 1,Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0]
sub_octet_add::  Polynome Z_sur_2Z
sub_octet_add = Pol [Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 1,Z2Z 1,Z2Z 0]
octet_magique::  Polynome Z_sur_2Z
octet_magique = Pol [Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 1]


sub_bytes :: Bloc_AES -> Bloc_AES
sub_bytes (Blc []) = Blc []
sub_bytes (Blc (x:xs)) = let Blc q = sub_bytes (Blc xs) in Blc ((sub_bytes_col x) :q) 

sub_bytes_col :: Colone_AES -> Colone_AES
sub_bytes_col (Col (Pol [])) = (Col (Pol []))
sub_bytes_col (Col (Pol (x:xs))) = let Col (Pol q) = sub_bytes_col (Col (Pol xs)) in Col (Pol ((sub_bytes_aux x) :q) )

sub_bytes_aux :: Gf28 -> Gf28
sub_bytes_aux (Gf l) = let Gf p = (inversemultPolgf28 (Gf l)) in Gf(addPol sub_octet_add (multmodulo p sub_octet_mult octet_magique)) 
 
-----------InvSubByte


inv_sub_octet_mult::  Polynome Z_sur_2Z
inv_sub_octet_mult = Pol [Z2Z 0,Z2Z 1,Z2Z 0,Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 1,Z2Z 0]
inv_sub_octet_add::  Polynome Z_sur_2Z
inv_sub_octet_add = Pol [Z2Z 1,Z2Z 0,Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0]


inv_sub_bytes :: Bloc_AES -> Bloc_AES
inv_sub_bytes (Blc []) = Blc []
inv_sub_bytes (Blc (x:xs)) = let Blc q = inv_sub_bytes (Blc xs) in Blc ((inv_sub_bytes_col x) :q) 

inv_sub_bytes_col :: Colone_AES -> Colone_AES
inv_sub_bytes_col (Col (Pol [])) = (Col (Pol []))
inv_sub_bytes_col (Col (Pol (x:xs))) = let Col (Pol q) = inv_sub_bytes_col (Col (Pol xs)) in Col (Pol ((inv_sub_bytes_aux x) :q) )

inv_sub_bytes_aux :: Gf28 -> Gf28
inv_sub_bytes_aux (Gf l) = inversemultPolgf28 (Gf(addPol inv_sub_octet_add (multmodulo l inv_sub_octet_mult octet_magique)))
 


-------------ShiftRows

shift_rows :: Bloc_AES -> Bloc_AES 
shift_rows (Blc [Col (Pol [a,b,c,d]),Col (Pol [e,f,g,h]), Col (Pol [i,j,k,l]),Col (Pol [m,n,o,p])]) = Blc [Col (Pol [a,f,k,p]),Col (Pol [e,j,o,d]), Col (Pol [i,n,c,h]),Col (Pol [m,b,g,l])]


-------------InvShiftRows

inv_shift_rows :: Bloc_AES -> Bloc_AES 
inv_shift_rows (Blc [Col (Pol [a,f,k,p]),Col (Pol [e,j,o,d]), Col (Pol [i,n,c,h]),Col (Pol [m,b,g,l])]) = (Blc [Col (Pol [a,b,c,d]),Col (Pol [e,f,g,h]), Col (Pol [i,j,k,l]),Col (Pol [m,n,o,p])])


------------MixColone

polynome_mix_col :: Polynome Gf28
polynome_mix_col = let Col c = col_hextobin ["02","01","01","03"] in c

col_magique :: Polynome Gf28  --Le polynome est en hexa {03}x3 + {01}x2 + {01}x + {02}
col_magique = let Col c =  col_hextobin ["01","00","00","00","01"] in c

mix_col :: Bloc_AES -> Bloc_AES
mix_col (Blc []) = Blc []
mix_col (Blc (x:xs)) = let Blc q = mix_col (Blc xs) in Blc ((mix_col_aux x) :q) 

mix_col_aux :: Colone_AES -> Colone_AES
mix_col_aux (Col (Pol l)) = (Col (multmodulo (Pol l) polynome_mix_col col_magique))

{-Version utilisant le calcul matriciel non tésté car suite aux retours des enseignant
ils s'est avéré plus facile d'utiliser une autre technique

mix_columns_matrix :: [[Gf28]]
mix_columns_matrix = [
    [Gf (Pol [Z2Z 0, Z2Z 1]), Gf (Pol [Z2Z 1, Z2Z 1]), Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 1])], -- 02, 03, 01, 01
    [Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 0, Z2Z 1]), Gf (Pol [Z2Z 1, Z2Z 1]), Gf (Pol [Z2Z 1])], -- 01, 02, 03, 01
    [Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 0, Z2Z 1]), Gf (Pol [Z2Z 1, Z2Z 1])], -- 01, 01, 02, 03
    [Gf (Pol [Z2Z 1, Z2Z 1]), Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 1]), Gf (Pol [Z2Z 0, Z2Z 1])]  -- 03, 01, 01, 02
    ]

mix_col_bloc :: Bloc_AES -> Bloc_AES
mix_col_bloc (Blc []) = (Blc [])
mix_col_bloc (Blc a) = Blc (map mix_col a)

mix_col :: Colone_AES -> Colone_AES
mix_col (Col (Pol [])) = Col (Pol [])
mix_col (Col (Pol b)) = Col (Pol (map (mix_col_aux b) mix_columns_matrix))

mix_col_aux :: [Gf28] -> [Gf28] -> Gf28
mix_col_aux col mat = foldl1 xor_pol (zipWith multPolgf28 col mat)-}


------------InvMixColone

polynome_inv_mix_col :: Polynome Gf28
polynome_inv_mix_col = let Col c = col_hextobin ["0e","09","0d","0b"] in c

inv_mix_col :: Bloc_AES -> Bloc_AES
inv_mix_col (Blc []) = Blc []
inv_mix_col (Blc (x:xs)) = let Blc q = inv_mix_col (Blc xs) in Blc ((inv_mix_col_aux x) :q) 

inv_mix_col_aux :: Colone_AES -> Colone_AES
inv_mix_col_aux (Col (Pol l)) = (Col (multmodulo (Pol l) polynome_inv_mix_col col_magique))

----------addRoundKey

add_round_key :: Bloc_AES -> Bloc_AES -> Bloc_AES 
add_round_key (Blc []) (Blc []) =  (Blc [])
add_round_key (Blc (x:xs)) (Blc (y:ys)) = let Blc b = (add_round_key (Blc xs) (Blc ys)) in Blc ((xor_col x y):b)

xor_col :: Colone_AES -> Colone_AES -> Colone_AES
xor_col (Col (Pol (x:xs))) (Col (Pol (y:ys))) = Col( addPol (Pol (x:xs)) (Pol (y:ys)))

------------Key Schedule
rconh = Blch [
              ["01","00","00","00"],
              ["02","00","00","00"],
              ["04","00","00","00"],
              ["08","00","00","00"],
              ["10","00","00","00"],
              ["20","00","00","00"],
              ["40","00","00","00"],
              ["80","00","00","00"],
              ["1b","00","00","00"],
              ["36","00","00","00"]
             ]
rcon = bloc_hextobin rconh

rconh192 = Blch [
              ["01","00","00","00"],
              ["02","00","00","00"],
              ["04","00","00","00"],
              ["08","00","00","00"],
              ["10","00","00","00"],
              ["20","00","00","00"],
              ["40","00","00","00"],
              ["80","00","00","00"]
             ]
rcon192 = bloc_hextobin rconh192

rconh256 = Blch [
              ["01","00","00","00"],
              ["02","00","00","00"],
              ["04","00","00","00"],
              ["08","00","00","00"],
              ["10","00","00","00"],
              ["20","00","00","00"],
              ["40","00","00","00"]
             ]
rcon256 = bloc_hextobin rconh256


key_schedule_128 :: Bloc_AES -> [Bloc_AES]
key_schedule_128 key = (key_schedule_aux key rcon)

key_schedule_192 :: Bloc_AES -> [Bloc_AES]
key_schedule_192 key = cut_first(rearange(key:(key_schedule_aux key rcon192)))

key_schedule_256 :: Bloc_AES -> [Bloc_AES]
key_schedule_256 key = init(cut_first(rearange(key:(key_schedule_256_aux key rcon256))))


key_schedule_aux :: Bloc_AES -> Bloc_AES -> [Bloc_AES]
key_schedule_aux (Blc key) (Blc (y:[])) = [next_key (Blc key) (Blc ([y])) ]
key_schedule_aux (Blc key) (Blc (y:ys)) = let k = next_key (Blc key) (Blc (y:ys)) in k: (key_schedule_aux k (Blc ys))

key_schedule_256_aux :: Bloc_AES -> Bloc_AES -> [Bloc_AES]
key_schedule_256_aux (Blc key) (Blc (y:[])) = [next_key_256 (Blc key) (Blc ([y])) ]
key_schedule_256_aux (Blc key) (Blc (y:ys)) = let k = next_key_256 (Blc key) (Blc (y:ys)) in k: (key_schedule_256_aux k (Blc ys))

rot_word :: Colone_AES -> Colone_AES
rot_word (Col(Pol (x:xs))) = Col (Pol (xs++[x]))

take_last_col :: Bloc_AES -> Colone_AES 
take_last_col (Blc (x:[]))= x
take_last_col (Blc (x:xs))= take_last_col (Blc xs)

cut_first :: [a] -> [a]
cut_first [] = []
cut_first (x:xs)= xs

next_key_256 :: Bloc_AES -> Bloc_AES -> Bloc_AES
next_key_256 (Blc (x:xs)) (Blc (y:ys)) =  let z = xor_col (xor_col (sub_bytes_col(rot_word (take_last_col (Blc xs)))) y) x in (let Blc bs = next_col_k_256 z (Blc xs) 0 in  Blc (z : bs))

next_key :: Bloc_AES -> Bloc_AES -> Bloc_AES
next_key (Blc (x:xs)) (Blc (y:ys)) =  let z = xor_col (xor_col (sub_bytes_col(rot_word (take_last_col (Blc xs)))) y) x in (let Blc bs = next_col_k z (Blc xs) in  Blc (z : bs))

next_col_k :: Colone_AES -> Bloc_AES -> Bloc_AES
next_col_k c (Blc [])  = Blc []
next_col_k c (Blc(x:xs)) = let (cs,Blc ls) = ((xor_col c x),(next_col_k cs (Blc xs))) in Blc(cs : ls)

next_col_k_256 :: Colone_AES -> Bloc_AES -> Int -> Bloc_AES
next_col_k_256 c (Blc []) a = Blc []
next_col_k_256 c (Blc(x:xs)) a = if a == 3 then let (cs,Blc ls) = ((xor_col (sub_bytes_col(c)) x),(next_col_k_256 cs (Blc xs) (a+1))) in Blc(cs : ls)
                                           else let (cs,Blc ls) = ((xor_col c x),(next_col_k_256 cs (Blc xs) (a+1))) in Blc(cs : ls)


rearange :: [Bloc_AES] -> [Bloc_AES]
rearange lb = rearange_auxb (rearange_auxc lb)

rearange_auxb :: [Colone_AES] -> [Bloc_AES]
rearange_auxb [] = []
rearange_auxb lc |length lc >= 4 = let a:b:c:d:sl = lc in (Blc [a,b,c,d]):(rearange_auxb sl)
            |otherwise = []

rearange_auxc :: [Bloc_AES] -> [Colone_AES]
rearange_auxc [] = [] 
rearange_auxc ((Blc b):bs) = b ++ (rearange_auxc bs)


test_192=Blch [["8e","73","b0","f7"],
              ["da","0e","64","52"],
              ["c8","10","f3","2b"],
              ["80","90","79","e5"],
              ["62","f8","ea","d2"],
              ["52","2c","6b","7b"]
             ]

test_192_2=Blch [["00","01","02","03"],
              ["04","05","06","07"],
              ["08","09","0a","0b"],
              ["0c","0d","0e","0f"],
              ["10","11","12","13"],
              ["14","15","16","17"]
             ]
            
test_256=Blch [["60","3d","eb","10"],
              ["15","ca","71","be"],
              ["2b","73","ae","f0"],
              ["85","7d","77","81"],
              ["1f","35","2c","07"],
              ["3b","61","08","d7"],
              ["2d","98","10","a3"],
              ["09","14","df","f4"]
             ]




--Convertion de binaire vers hexa et inversement pour faciliter la manipulation et le test des fonctions

bloc_hextobin :: Bloc_AES_hexa -> Bloc_AES
bloc_hextobin (Blch []) =  (Blc [])
bloc_hextobin (Blch (x:xs)) = let Blc b = bloc_hextobin (Blch xs) in Blc ((col_hextobin x) : b)

col_hextobin :: [String] -> Colone_AES
col_hextobin [] = Col(Pol [])
col_hextobin (x:xs) = let Col(Pol c) = col_hextobin xs in Col (Pol((hextobin x) : c))

hextobin :: String -> Gf28
hextobin [] = Gf(Pol [])
hextobin ('0':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 0]))
hextobin ('1':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 0]))
hextobin ('2':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 1,Z2Z 0,Z2Z 0]))
hextobin ('3':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 0]))
hextobin ('4':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 0,Z2Z 1,Z2Z 0]))
hextobin ('5':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 0,Z2Z 1,Z2Z 0]))
hextobin ('6':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 1,Z2Z 1,Z2Z 0]))
hextobin ('7':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 1,Z2Z 1,Z2Z 0]))
hextobin ('8':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 0,Z2Z 0,Z2Z 1]))
hextobin ('9':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 0,Z2Z 0,Z2Z 1]))
hextobin ('a':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 1,Z2Z 0,Z2Z 1]))
hextobin ('b':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 1,Z2Z 0,Z2Z 1]))
hextobin ('c':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 0,Z2Z 1,Z2Z 1]))
hextobin ('d':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 0,Z2Z 1,Z2Z 1]))
hextobin ('e':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 0,Z2Z 1,Z2Z 1,Z2Z 1]))
hextobin ('f':xs) = let Gf(Pol p) = hextobin xs in Gf (Pol (p ++ [Z2Z 1,Z2Z 1,Z2Z 1,Z2Z 1]))


lbloc_bintohex :: [Bloc_AES] -> [Bloc_AES_hexa]
lbloc_bintohex [] = []
lbloc_bintohex (x:xs) = (bloc_bintohex x) : (lbloc_bintohex xs)

bloc_bintohex :: Bloc_AES -> Bloc_AES_hexa
bloc_bintohex (Blc []) = Blch []
bloc_bintohex (Blc (x:xs)) = let Blch b = bloc_bintohex (Blc xs) in Blch ((col_bintohex x):b)

col_bintohex :: Colone_AES -> [String]
col_bintohex (Col (Pol [])) = []
col_bintohex (Col (Pol (x:xs))) = (bintohex (complete x)) : (col_bintohex  (Col (Pol xs)))

bintohex :: Gf28 -> String
bintohex (Gf(Pol [])) = []
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 0 :  Z2Z 0 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "0"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 0 :  Z2Z 0 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "1"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 1 :  Z2Z 0 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "2"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 1 :  Z2Z 0 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "3"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 0 :  Z2Z 1 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "4"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 0 :  Z2Z 1 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "5"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 1 :  Z2Z 1 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "6"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 1 :  Z2Z 1 :  Z2Z 0 : xs))) = (bintohex (Gf(Pol xs))) ++ "7"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 0 :  Z2Z 0 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "8"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 0 :  Z2Z 0 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "9"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 1 :  Z2Z 0 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "a"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 1 :  Z2Z 0 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "b"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 0 :  Z2Z 1 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "c"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 0 :  Z2Z 1 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "d"
bintohex (Gf(Pol(Z2Z 0 :  Z2Z 1 :  Z2Z 1 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "e"
bintohex (Gf(Pol(Z2Z 1 :  Z2Z 1 :  Z2Z 1 :  Z2Z 1 : xs))) = (bintohex (Gf(Pol xs))) ++ "f"

complete :: Gf28 -> Gf28 
complete (Gf(Pol l)) | length l < 8 = complete (Gf(Pol (l++[Z2Z 0])))
                     |otherwise = (Gf(Pol l))
