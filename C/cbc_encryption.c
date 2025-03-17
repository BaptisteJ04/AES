#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "F_Inverse_AES.h"
#include "Cypher_InvCypher.h"
#include "F_AES.h"
#include "Table_de_multiplication.h"

int aes_cbc_encrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, unsigned char* vi,word key[], int key_length) {
    if(key_length != 128 && key_length != 192 &&key_length != 256 &&key_length != 4 &&key_length != 6 &&key_length != 8){
        printf("WRONG KEY SIZE");
        return 0;
    }
    
    *dst_data_length = src_data_length;
    *dst = (unsigned char*)malloc(*dst_data_length);

    state bloc;
    state bloc_p;

    word keyl[60];
    KeyExp(key,keyl,key_length);

    int nb;

    for(int i = 0 ; i < src_data_length ; i+=16) {
        copieb(bloc,bloc_p,4);
        for(int k=0; k<16; k++){
            bloc[k/4][k%4] = src[i+k];
           
            if(i==0){bloc_p[k/4][k%4] = vi[i+k];}
        }   
        Add_RK(bloc,bloc_p);
        aes_encrypt(bloc, bloc, keyl, key_length);
        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                
                (* dst + i )[4*k+j] = bloc[k][j];
            }
        }
        nb = i;    
    }

    nb+=16;
    

   if (src_data_length > nb) {
        copieb(bloc,bloc_p,4);
        for (int j = 0; j < 4; j++) {
            bloc[j / 4][j % 4] = src[nb+j+16];
        }
        for (int j = src_data_length - nb; j < 16; j++) {
            bloc[j / 4][j % 4] = 0x00;
        }

        Add_RK(bloc,bloc_p);
        aes_encrypt(bloc, bloc, keyl, key_length);
    
        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + nb )[4*k+j] = bloc[k][j];
            }
        }
    }
    return 0;
}

int aes_cbc_decrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, unsigned char* vi,word key[], int key_length) {
    if(key_length != 128 && key_length != 192 &&key_length != 256 &&key_length != 4 &&key_length != 6 &&key_length != 8){
        printf("WRONG KEY SIZE");
        return 0;
    }
    
    *dst_data_length = src_data_length;
    *dst = (unsigned char*)malloc(*dst_data_length);

    state bloc;
    state bloc_p;

    word keyl[60];
    KeyExp(key,keyl,key_length);

    int nb;

    for(int i = 0 ; i < src_data_length ; i+=16) {
        copieb(bloc,bloc_p,4);
        for(int k=0; k<16; k++){
               
            if(i==0){bloc_p[k/4][k%4] = vi[i+k];bloc[k/4][k%4] = src[i+k];}
            else{bloc_p[k/4][k%4] = src[i-1+k];bloc[k/4][k%4] = src[i+k];}
        }   
        Add_RK(bloc,bloc_p);
        aes_encrypt(bloc, bloc, keyl, key_length);
        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                
                (* dst + i )[4*k+j] = bloc[k][j];
            }
        }
        nb = i;    
    }

    nb+=16;
    

   if (src_data_length > nb) {
        copieb(bloc,bloc_p,4);
        for (int j = 0; j < 4; j++) {
            bloc[j / 4][j % 4] = src[nb+j+16];
        }

        Add_RK(bloc,bloc_p);
        aes_encrypt(bloc, bloc, keyl, key_length);
    
        for(int k=0; k<4; k++){
            for (int j=0; j<4; j++){
                (* dst + nb )[4*k+j] = bloc[k][j];
            }
        }
    }
    return 0;
}