#include <stdio.h>
#include "generation_tables.h"
#include <stdint.h>

//############################################Version pas optimisée qui servira a generer les tables###############################################
//Cette fonction ne traite que la multiplication par 0x01, 0x02, 0x03 car on ne rencontre que ces cas dans l'implementation de mix colonne
// Cette fonction ne traite que la multiplication par 0x01, 0x02, 0x03 car on ne rencontre que ces cas dans l'implementation de mix colonne
uint8_t mult_mix_gf(uint8_t a, uint8_t b) {
    if (a == 0x01) { // Multiplication par 0x01 (neutre multiplicatif)
        return b;
    } else if (a == 0x02) {
        if (b & 0x80) {
            return (b << 1) ^ 0x11B;
        } else {
            return (b << 1);
        }
    } else if (b == 0x03) {
        return mult_mix_gf(0x02, b) ^ b;
    } else {
        // Si b n'est pas parmi 2, 3, 9, 11, 13, ou 14, retourner 0 (pourrait gérer autrement selon les besoins)
        return 0;
    }
}
// On ne prend en compte que la multiplication par 0x09, 0x0B, 0x0D et 0x0E car on n'a que ces cas dans inverse Mix Colonne
uint8_t mult_inverse_mix_gf(uint8_t a, uint8_t b) {
    if (a == 0x09) {
        return mult_mix_gf(0x02, mult_mix_gf(0x02, mult_mix_gf(0x02, b))) ^ b;
    } else if (a == 0x0B) {
        return mult_mix_gf(0x02, mult_mix_gf(0x02, mult_mix_gf(0x02, b)) ^ b) ^ b;
    } else if (a == 0x0D) {
        return mult_mix_gf(0x02, mult_mix_gf(0x02, mult_mix_gf(0x02, b)) ^ b) ^ b;
    } else if (a == 0x0E) {
        return mult_mix_gf(0x02, mult_mix_gf(0x02, mult_mix_gf(0x02, b) ^ b) ^ b);
    } else {
        return 0; // Cas non vu dans notre implementation
    }
}

//Dans cette fonction, on construit nos tables de multiplication pour la fonction de multiplication dans GF(2⁸)
void Generation_Table(){
    printf("};\n######################################Generation Table############################################\n");
    for(int j = 0x02; j<=0x03; j++){
        printf("\n##################################################################################################\n");
        printf("uint8_t mul%d[256] = {",j);
        for(int i = 0; i<=0xFF; i++){
            if(i%16 == 0x00) printf("\n");
            printf("0x%02x, ",mult_mix_gf(j, i));
        }
        printf("};\n##################################################################################################\n");
    }for(int j = 0x09; j<=0x0D; j = j+2){
        printf("\n##################################################################################################\n");
        printf("uint8_t mul%d[256] = {",j);
        for(int i = 0; i<=0xFF; i++){
            if(i%16 == 0x00) printf("\n");
            printf("0x%02x, ",mult_inverse_mix_gf(j, i));
        }
        printf("};\n##################################################################################################\n");
    }
    printf("\n##################################################################################################\n");
    printf("uint8_t mul14[256] = {");
    for(int i = 0; i<=0xFF; i++){
        if(i%16 == 0x00) printf("\n");
        printf("0x%02x, ",mult_inverse_mix_gf(0x0E, i));
    }
    printf("};\n##################################################################################################\n");
}