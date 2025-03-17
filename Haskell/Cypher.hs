module Cypher where
import Anneau
import Corps
import Z_sur_2Z
import Polynome
import GF28
import AES

cypher :: Bloc_AES -> Bloc_AES->Bloc_AES
--Prend le bloc à coder et la clé de départ et renvoie le bloce crypté
cypher b (Blc l) |length l == 4 = cypher_aux (add_round_key b key) (key_schedule_128 key)
                 |length l == 6 = cypher_aux (add_round_key b key) (key_schedule_192 key)
                 |length l == 8 = cypher_aux (add_round_key b key) (key_schedule_256 key)

cypher_aux :: Bloc_AES -> [Bloc_AES] -> Bloc_AES 
--Prend le bloc à coder et la liste des clé de départ et renvoie le bloce crypté
cypher_aux mot [k] = add_round_key k (shift_rows(sub_bytes mot))
cypher_aux mot (x:xs) = cypher_aux (add_round_key x (mix_col(shift_rows(sub_bytes mot)))) xs

inv_cypher :: Bloc_AES -> Bloc_AES -> Bloc_AES
--Prend le bloc coder et la clé de départ et renvoie le bloce décrypté 
inv_cypher b (Blc l) |length l == 4 = let k:ks = rev (key_schedule_128 key) in add_round_key (inv_cypher_aux (inv_shift_rows(inv_sub_bytes(add_round_key b k))) ks) key
                     |length l == 6 = let k:ks = rev (key_schedule_192 key) in add_round_key (inv_cypher_aux (inv_shift_rows(inv_sub_bytes(add_round_key b k))) ks) key
                     |length l == 8 = let k:ks = rev (key_schedule_256 key) in add_round_key (inv_cypher_aux (inv_shift_rows(inv_sub_bytes(add_round_key b k))) ks) key


inv_cypher_aux :: Bloc_AES -> [Bloc_AES] -> Bloc_AES
--Prend le bloc coder et la liste des clés et renvoie le bloce décrypté 
inv_cypher_aux b [] = b
inv_cypher_aux b (x:xs) = inv_cypher_aux (inv_sub_bytes(inv_shift_rows(inv_mix_col(add_round_key x b)))) xs

rev :: [a] -> [a]
rev [] = []
rev (b:bs) = (rev bs) ++ [b]



keyh :: Bloc_AES_hexa 
keyh = Blch  [["2b","7e","15","16"],
             ["28","ae","d2","a6"],
             ["ab","f7","15","88"],
             ["09","cf","4f","3c"]
            ]   

key :: Bloc_AES
key = bloc_hextobin keyh


bloc_testh = Blch [
                  ["32","43","f6","a8"],
                  ["88","5a","30","8d"],
                  ["31","31","98","a2"],
                  ["e0","37","07","34"]
                ]

bloc_test = bloc_hextobin bloc_testh

inv_bloc_testh = Blch [
                  ["39","25","84","1d"],
                  ["02","dc","09","fb"],
                  ["dc","11","85","97"],
                  ["19","6a","0b","32"]
                ]

inv_bloc_test = bloc_hextobin inv_bloc_testh

