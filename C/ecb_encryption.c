#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "F_Inverse_AES.h"
#include "Cypher_InvCypher.h"
#include "F_AES.h"
#include "Table_de_multiplication.h"

//Cette fonction va découper en bloc de 128 bits, la donnee entree en parametre, puis prendre une clef de (128, 192, 256 bits) pour crypter a l'aide d'AES, la donnee d'entree. Elle retournera la donnee cryptee.
int aes_ecb_encrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, word key[], int key_length) {
    if(key_length != 128 && key_length != 192 &&key_length != 256 &&key_length != 4 &&key_length != 6 &&key_length != 8){
        printf("WRONG KEY SIZE\n");
        return 0;
    }
    *dst_data_length = src_data_length;
    *dst = (unsigned char*)malloc(*dst_data_length); //Creation de l'espace d'ecriture de la donnee cryptee

    state bloc;

    word keyl[60];
    KeyExp(key,keyl,key_length); //Creation du tableau stockant les clefs pour chaques tours

    int nb;

    for(int i = 0 ; i < src_data_length ; i+=16) {  //Cryptage des blocs de 128 bits par AES
        for(int k=0; k<16; k++){
            bloc[k/4][k%4] = src[i+k];
        }   
        aes_encrypt(bloc, bloc, keyl, key_length);

        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + i )[4*k+j] = bloc[k][j];  //Ecriture dans la zone memoire dediee des donnees cryptees
            }
        }
        nb = i;
    }

    nb+=16;

   if (src_data_length > nb) {  //Prise en compte du padding si le dernier bloc n'est pas de 128 bits
        for (int j = 0; j < 4; j++) {
            bloc[j / 4][j % 4] = src[nb+j+16];
        }
        for (int j = src_data_length - nb; j < 16; j++) {
            bloc[j / 4][j % 4] = 0x00; //Remplissage avec des 0
        }

        aes_encrypt(bloc, bloc, keyl, key_length);

        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + nb )[4*k+j] = bloc[k][j];
            }
        }
    }
    return 0;
}

//Cette fonction va découper en bloc de 128 bits, la donnee entree sera cryptee, a l'aide d'une clef qui a servit au cryptage de la donnee. La fonction va a l'aide d'AES, decrypter la donnee d'entree. Elle retournera la donnee claire.

int aes_ecb_decrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, word key[], int key_length) {
    if(key_length != 128 &&key_length != 192 &&key_length != 256 &&key_length != 4 &&key_length != 6 &&key_length != 8){
        printf("WRONG KEY SIZE\n");
        return 0;
    }

    *dst_data_length = src_data_length;
    *dst = (unsigned char*)malloc(*dst_data_length);  //Creation de l'espace d'ecriture de la donnee claire

    state bloc;

    word keyl[60];
    KeyExp(key,keyl,key_length);

    int nb;

    for(int i = 0 ; i < src_data_length ; i+=16) { //Decryptage des blocs de 128 bits par AES
        for(int k=0; k<16; k++){
            bloc[k/4][k%4] = src[i+k];
        }   
        aes_decrypt(bloc, bloc, keyl, key_length);

        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + i )[4*k+j] = bloc[k][j];
            }
        }
        nb = i;
    }

    nb+=16;

   if (src_data_length > nb) {  //Prise en compte du padding si le dernier bloc n'est pas de 128 bits
        for (int j = 0; j < 4; j++) {
            bloc[j / 4][j % 4] = src[nb+j+16];
        }

        aes_decrypt(bloc, bloc, keyl, key_length);

        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + nb )[4*k+j] = bloc[k][j];
            }
        }
    }
    return 0;
}