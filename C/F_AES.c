#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "F_Inverse_AES.h"
#include "Table_de_multiplication.h"
#include "F_AES.h"

uint8_t mat_mix[4][4] = {{0x02, 0x03, 0x01, 0x01},
                     {0x01, 0x02, 0x03, 0x01},
                     {0x01, 0x01, 0x02, 0x03},
                     {0x03, 0x01, 0x01, 0x02}
};

uint8_t bloc_initial[4][4] = {
    {0x32, 0x88, 0x31, 0xe0},
    {0x43, 0x5a, 0x31, 0x37},
    {0xf6, 0x30, 0x98, 0x07},
    {0xa8, 0x8d, 0xa2, 0x34}
};

uint8_t bloc_test[4][4] = {
    {0x32, 0x88, 0x31, 0xe0},
    {0x43, 0x5a, 0x31, 0x37},
    {0xf6, 0x30, 0x98, 0x07},
    {0xa8, 0x8d, 0xa2, 0x34}
};

uint8_t bloc_add_round_key[4][4] = {
    {0x2b, 0x28, 0xab, 0x09},
    {0x7e, 0xae, 0xf7, 0xcf},
    {0x15, 0xd2, 0x15, 0x4f},
    {0x16, 0xa6, 0x88, 0x3c}
};

uint8_t bloc_apres_add_round_key[4][4] = {
    {0x19, 0xa0, 0x9a, 0xe9},
    {0x3d, 0xf4, 0xc6, 0xf8},
    {0xe3, 0xe2, 0x8d, 0x48},
    {0xbe, 0x2b, 0x2a, 0x08}
};

uint8_t bloc_apres_sub_bytes[4][4] = {
    {0xd4, 0xe0, 0xb8, 0x1e},
    {0x27, 0xbf, 0xb4, 0x41},
    {0x11, 0x98, 0x5d, 0x52},
    {0xae, 0xf1, 0xe5, 0x30}
};

uint8_t bloc_apres_shift_rows[4][4] = {
    {0xd4, 0xe0, 0xb8, 0x1e},
    {0xbf, 0xb4, 0x41, 0x27},
    {0x5d, 0x52, 0x11, 0x98},
    {0x30, 0xae, 0xf1, 0xe5}
};
uint8_t bloc_apres_mix_columns[4][4] = {
    {0x04, 0xe0, 0x48, 0x28},
    {0x66, 0xcb, 0xf8, 0x06},
    {0x81, 0x19, 0xd3, 0x26},
    {0xe5, 0x9a, 0x7a, 0x4c}
};


//---------------------------utilitaire-----------------------------------------
//Cette fonction sert aux tests en testant si deux matrices sont égales
bool egalite_bloc(uint8_t bloc[4][4], uint8_t mat_res[4][4]){
    bool res = true;
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            if ((bloc[i][j] != mat_res[i][j])) res = false;
        }
    }
    return res;
}

bool egalite_tableau(uint8_t tableau1[4], uint8_t tableau2[4]){
    bool res = true;
    for(int i = 0; i<4; i++){
        if ((tableau1[i] != tableau2[i])) res = false;
    }
    return res;
}

void rotmat(uint8_t bloc[4][4]){
    //permet de faire tourner un matrice, echanger ligne et colone
    uint8_t temp[4][4];
    for (int i = 0; i < 4 ; i++){
        for (int j = 0; j < 4 ; j++){
            temp[i][j] = bloc[j][i];           
        }
    }
    for (int i = 0; i < 4 ; i++){
        for (int j = 0; j < 4 ; j++){
            bloc[i][j] = temp[i][j];           
        }
    }
}

void copieb(uint8_t blocs[][4],uint8_t blocd[][4],int taille){
    // copie des données d'une matrice [x][4] dans une autre  
    for (int i = 0; i < taille ; i++){
        for (int j = 0; j < 4 ; j++){
            blocd[i][j] = blocs[i][j];           
        }
    }
}

void copiec(uint8_t cols[4],uint8_t cold[4]){
    //copie un colone d'une matrice dans une autre
    for (int i = 0; i < 4 ; i++){
        cold[i] = cols[i];           
    }
}

void xor(uint8_t cola[4],uint8_t colb[4]){
    //ca xor deux colone
    for (int j = 0; j < 4 ; j++){
            cola[j] = cola[j]^colb[j];           
        }
}

void crea_tab(char phrase[],uint8_t bloc[][4],int taille){
    //permet à partir d'une chaine de charactère hexa de créer sa matrice correspondante
    char c[2];
    for (int i = 0; i < taille ; i++){
        for (int j = 0; j < 4 ; j++){
            c[0] = phrase [2*(4*i+j)];
            c[1] = phrase [2*(4*i+j)+1];
            bloc[i][j]=(uint8_t)strtol(c, NULL, 16); // convertion dun char vers sa valeur hexa
        }
    }
    if(taille == 4){
        rotmat(bloc); // si taile == 4 on retourne car les blocs qui ne sont pas des clé sont dans l'autre sens
    }
}

void print_bloc(uint8_t bloc[][4],int taille){
    //affiche un bloc
    for (int i = 0; i < taille ; i++){
        for (int j = 0; j < 4 ; j++){
            printf("%02x ",bloc[i][j]);
        }
        printf("\n");
    }
}


void print_tableau(uint8_t tableau[4]){
    //affiche un tableau
    for (int i = 0; i < 4 ; i++){
        printf("%02x ",tableau[i]);
    }
    printf("\n");
}

void rotword(uint8_t col[4]){
    // permet de faire passser le premier élément d'un tableau en dérnière position
    uint8_t temp = col[0];
    for(int i = 0 ; i < 3 ; i++){
        col[i] = col[i+1];
    }
    col[3]=temp;
}

//---------------------------Sub_bytes-----------------------------------------

uint8_t sbox[16][16] ={ {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
                     {0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
                     {0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
                     {0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
                     {0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
                     {0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
                     {0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
                     {0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
                     {0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
                     {0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
                     {0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
                     {0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
                     {0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
                     {0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
                     {0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
                     {0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}};



void subbytes(uint8_t bloc[4][4]){
    // parcours d'une matrice et applique la transformation donné par la sbox pour chaque élément
    for (int i = 0; i < 4 ; i++){
        for (int j = 0; j < 4 ; j++){
            bloc[i][j] = sbox[bloc[i][j]/16][bloc[i][j]%16] ;           
        }
    }
}

void subbytesCol(uint8_t col[4]){
    //subbytes mais sur une colone utile pour la key expansion
    for (int i = 0; i < 4 ; i++){
        col[i] = sbox[col[i]/16][col[i]%16] ;           
    }
}

//---------------------------Add_RK-----------------------------------------

void Add_RK (uint8_t bloc[4][4],uint8_t key[4][4]){
    //xor chaque élément de la première matrice avec ceeux de la deuxième
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            bloc[i][j]=bloc[i][j]^key[i][j];
        }
    }
}


//---------------------------Shift_rows-----------------------------------------

//Une fonction qui decale de num_dec places vers la gauche en rebouclant dans un tableau de taille 4
//On va à chaque tour de boucle, prendre le premier element du tableau et decaler en ecrasant toutes les autres valeurs vers la gauche puis rajouter le premier à la fin
void decalageg(uint8_t row[4], int num_dec){
    uint8_t aux;
    for(int j = 0; j < num_dec; j++){
        aux = row[0];
        for(int i = 0; i < 3; i++){  
            row[i] = row[i+1];  
        }
        row[3] = aux; 
    }
}

//Fonction Shift_rows d'AES sur un bloc de 4 lignes avec 4 elements par lignes qui decale du numero de ligne vers la gauche chaque ligne
void shift_rows(uint8_t bloc[4][4]){
    for(int i = 0; i < 4; i++){
        decalageg(bloc[i], i);
    }
}

//---------------------------Mix_Columns-----------------------------------------

//Cette fonction ne traite que la multiplication par 0x01, 0x02, 0x03, 0x09, 0x0B, 0x0D, 0x0E car on ne rencontre que ces cas dans l'implementation de mix colonne et reverse mix colonne
//Pour optimiser les calculs, on utilise des tables de "transforme" pour trouver la multiplication dans GF(2⁸).
uint8_t mult_mix_gf(uint8_t a, uint8_t b) {
    if (a == 0x01) { // Multiplication par 0x01 (neutre multiplicatif)
        return b;
    } else if (a == 0x02){
        return mul2[b];
    }else if (a == 0x03){
        return mul3[b];
    }else if (a == 0x09){
        return mul9[b];
    }else if (a == 0x0B){
        return mul11[b];
    }else if (a == 0x0D){
        return mul13[b];
    }else if (a == 0x0E){
        return mul14[b];
    }
    else return 0;

}

//Fonction Mix_colonne d'AES sur un bloc de 4 lignes avec 4 elements par lignes
void mix_columns(uint8_t bloc[4][4]){
    uint8_t temp[4][4];
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < 4; i++) {
            temp[i][c] = mult_mix_gf(mat_mix[i][0], bloc[0][c]) ^ mult_mix_gf(mat_mix[i][1], bloc[1][c]) ^ mult_mix_gf(mat_mix[i][2], bloc[2][c]) ^ mult_mix_gf(mat_mix[i][3], bloc[3][c]);
        }
    }
    copieb(temp, bloc,4);
}


//---------------------------Key expantion-----------------------------------------

uint8_t rcon [10][4]={{0x01,0x00,0x00,0x00},
                      {0x02,0x00,0x00,0x00},
                      {0x04,0x00,0x00,0x00},
                      {0x08,0x00,0x00,0x00},
                      {0x10,0x00,0x00,0x00},
                      {0x20,0x00,0x00,0x00},
                      {0x40,0x00,0x00,0x00},
                      {0x80,0x00,0x00,0x00},
                      {0x1b,0x00,0x00,0x00},
                      {0x36,0x00,0x00,0x00}
                     };

void decoupe192(uint8_t lkeyp[10][8][4],uint8_t lkeyf[15][4][4]){
    //pemrmet de transformer une liste de clé de taille 192 en une liste de clé de taille 128bit
    //les deux for parcours la liste de mat final et a,b parcourt liste de mat de base;
    int b = 0;
    int a = 0;
    for(int i = 0;i<13;i++){
        for(int j = 0;j<4;j++){
            copiec(lkeyp[b][a],lkeyf[i][j]);
            a++;
            if(a==6){a=0;b++;}
        }
    }
}

void decoupe256(uint8_t lkeyp[10][8][4],uint8_t lkeyf[15][4][4]){
    //meme chose que précedement mais avec desclé de taille 256 bit
    int b = 0;
    int a = 0;
    for(int i = 0;i<15;i++){
        for(int j = 0;j<4;j++){
            copiec(lkeyp[b][a],lkeyf[i][j]);
            a++;
            if(a==8){a=0;b++;}
        }
    }
}

void list_key_to_word(uint8_t keylist[15][4][4],uint8_t keyl[60][4]){
    int a = 0;
    for(int i = 0 ; i< 15;i++ ){
        for(int j = 0 ; j<4;j++){
            copiec(keylist[i][j],keyl[a]);
            a ++;
        }
        
    }
}

void KeyExp(uint8_t bloc[][4],uint8_t keyl[60][4],int taille){
    uint8_t keylist[15][4][4];
    //cre la liste de toute les clé étendue;
    if(taille==4){rotmat(bloc);}//On veut les clé dans l'autre sens pour la génération or les clé 4 4 ont été retourné et pas les autres
    uint8_t tkeyl[11][8][4];
    copieb(bloc,tkeyl[0],taille);
    uint8_t col[4];
    int nbt = 11;//nombre de tour pour t=128
    if (taille == 6) {nbt = 10;}//nombre de tour pour t=192
    if (taille == 8) {nbt = 9;}//nombre de tour pour t=256
    for (int i = 1 ; i<nbt;i++){
        copiec (tkeyl[i-1][taille-1],col);
        rotword(col);
        subbytesCol(col);
        xor(col,rcon[i-1]);xor(col,tkeyl[i-1][0]);
        copiec(col,tkeyl[i][0]);
        for(int j = 1 ; j < taille ; j++){
            if(taille == 8 && j == 4 ){subbytesCol(col);}
            xor(col,tkeyl[i-1][j]);
            copiec(col,tkeyl[i][j]);
        }
    }
    if(taille == 4){
        for(int i = 0; i<nbt;i++){
            rotmat(tkeyl[i]);
            copieb(tkeyl[i],keylist[i],4);
        }
    }
    else if(taille==6){
        decoupe192(tkeyl,keylist);
        for(int i = 0; i<13;i++){
            rotmat(keylist[i]);
        }
    }
    else{
        decoupe256(tkeyl,keylist);
        for(int i = 0; i<15;i++){
            rotmat(keylist[i]);
        }
    }
    list_key_to_word(keylist,keyl);
}


void extrat_key(uint8_t keyl[60][4],uint8_t bloc[4][4],int i){
    /*copiec(keyl[0],bloc[0]);
    copiec(keyl[1],bloc[1]);
    copiec(keyl[2],bloc[2]);
    copiec(keyl[3],bloc[3]);*/
    for(int j = 0;j<4;j++){
        copiec(keyl[4*i+j],bloc[j]);
    }
}
