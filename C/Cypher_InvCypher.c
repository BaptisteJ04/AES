#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "F_Inverse_AES.h"
#include "Cypher_InvCypher.h"
#include "F_AES.h"
#include "Table_de_multiplication.h"

//Cette fonction, va encrypter un bloc clair de 128 bits à l'aide d'une clef de (128, 192, 256 bits), et "renvoyer" le bloc crypte 
void aes_encrypt(state dst,state src,word lkey[], int key_lenght){
    copieb(src,dst,4);
    int nbt;
    word key[4];
    //On teste quelle type de clef est rentree afin d'utiliser le bon format d'AES (128, 192, 256)
    if(key_lenght == 128||key_lenght == 4){key_lenght = 4;nbt = 9;}
    if(key_lenght == 192||key_lenght == 6){key_lenght = 6;nbt = 11;}
    if(key_lenght == 256||key_lenght == 8){key_lenght = 8;nbt = 13;}
    extrat_key(lkey,key,0);
    Add_RK(dst,key);
    for(int t = 1; t<=nbt;t++){ //Le nombre de tour de boucle depend de la version de cryptage d'AES (128, 192, 256)
        subbytes(dst);
        shift_rows(dst);
        mix_columns(dst);
        extrat_key(lkey,key,t); //Choix de la clef de la boucle suivante 
        Add_RK(dst,key);
    }
    subbytes(dst);
    shift_rows(dst);
    extrat_key(lkey,key,nbt+1); 
    Add_RK(dst,key);
}

//Cette fonction, va encrypter un bloc clair de 128 bits à l'aide d'une clef de (128, 192, 256 bits), et "renvoyer" le bloc crypte
void aes_decrypt(state dst,state src,word lkey[], int key_lenght){
    copieb(src,dst,4);
    int nbt;
    word key[4];
    //On teste quelle type de clef est rentree (comme pour le cryptage)
    if(key_lenght == 128||key_lenght == 4){key_lenght = 4;nbt = 9;}
    else if(key_lenght == 192||key_lenght == 6){key_lenght = 6;nbt = 11;}
    else if(key_lenght == 256||key_lenght == 8){key_lenght = 8;nbt = 13;}
    extrat_key(lkey,key,nbt+1);
    Add_RK(dst,key);
    Inverse_Shift_rows(dst);
    Inverse_Sub_bytes(dst);
    for(int t = nbt; t>=1;t--){ //Cette fois ci, on n'utilise les fonctions inverses de celle du cryptage. De plus, les fonctions sont utilisees dans le sens inverse.
        extrat_key(lkey,key,t);
        Add_RK(dst,key);
        Inverse_Mix_Colonne(dst);;
        Inverse_Shift_rows(dst);
        Inverse_Sub_bytes(dst);       
    }
    extrat_key(lkey,key,0);
    Add_RK(dst,key);
}

