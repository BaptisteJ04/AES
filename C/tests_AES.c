#include "F_AES.h"
#include "F_Inverse_AES.h"
#include "Cypher_InvCypher.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


//----------------test de egalite-bloc------------------------------
void test_egalite_bloc(){
    printf("\n######################test de egalite-bloc-######################\n\n");
    printf("Deux bloc identiques sont egaux : %s\n", egalite_bloc(bloc_test, bloc_test) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("Deux bloc differents sont egaux : %s\n", egalite_bloc(bloc_test, mat_mix) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//----------------test decalaged------------------------------
void test_decalaged(){
    printf("\n######################Test decalaged######################\n");
    uint8_t La_pie_de_Monet[4] = {0xef, 0x25, 0x35, 0x1f};
    uint8_t res1[4] = {0x1f, 0xef, 0x25, 0x35};
    decalaged(La_pie_de_Monet, 1);
    printf("Le 1er test de decalaged %s\n", egalite_tableau(La_pie_de_Monet, res1) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
    La_pie_de_Monet[0] = 0xef;
    La_pie_de_Monet[1] = 0x25;
    La_pie_de_Monet[2] = 0x35;
    La_pie_de_Monet[3] = 0x1f;
    uint8_t res2[4] = {0x35, 0x1f, 0xef, 0x25};
    decalaged(La_pie_de_Monet, 2);
    printf("Le 2e test de decalaged %s\n", egalite_tableau(La_pie_de_Monet, res2) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
    La_pie_de_Monet[0] = 0xef;
    La_pie_de_Monet[1] = 0x25;
    La_pie_de_Monet[2] = 0x35;
    La_pie_de_Monet[3] = 0x1f;
    uint8_t res3[4] = {0x25, 0x35, 0x1f, 0xef};
    decalaged(La_pie_de_Monet, 3);
    printf("Le 3e test de decalaged %s\n", egalite_tableau(La_pie_de_Monet, res3) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
}

//----------------test decalageg------------------------------
void test_decalageg(){
    printf("\n######################Test decalageg######################\n");
    uint8_t La_pie_de_Monet[4] = {0xef, 0x25, 0x35, 0x1f};
    uint8_t res1[4] = {0x25, 0x35, 0x1f, 0xef};
    decalageg(La_pie_de_Monet, 1);
    printf("Le 1er test de decalageg %s\n", egalite_tableau(La_pie_de_Monet, res1) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
    La_pie_de_Monet[0] = 0xef;
    La_pie_de_Monet[1] = 0x25;
    La_pie_de_Monet[2] = 0x35;
    La_pie_de_Monet[3] = 0x1f;
    uint8_t res2[4] = {0x35, 0x1f, 0xef, 0x25};
    decalageg(La_pie_de_Monet, 2);
    printf("Le 2e test de decalageg %s\n", egalite_tableau(La_pie_de_Monet, res2) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
    La_pie_de_Monet[0] = 0xef;
    La_pie_de_Monet[1] = 0x25;
    La_pie_de_Monet[2] = 0x35;
    La_pie_de_Monet[3] = 0x1f;
    uint8_t res3[4] = {0x1f, 0xef, 0x25, 0x35};
    decalageg(La_pie_de_Monet, 3);
    printf("Le 3e test de decalageg %s\n", egalite_tableau(La_pie_de_Monet, res3) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("------------\n");
    print_tableau(La_pie_de_Monet);
    printf("------------\n");
}


//------------------------Test Sub bytes-----------------------

void test_Sub_Bytes(){
    printf("\n######################Test Sub bytes######################\n");
    subbytes(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_sub_bytes,4);
    printf("------------\n");
    printf("Le test de Sub bytes %s\n", egalite_bloc(bloc_test, bloc_apres_sub_bytes) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//------------------------Test Shift Rows-----------------------

void test_Shift_Rows(){
    printf("\n######################Test Shift Rows######################\n");
    shift_rows(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_shift_rows,4);
    printf("------------\n");
    printf("Le test de Shift Rows %s\n", egalite_bloc(bloc_test, bloc_apres_shift_rows) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//------------------------Test Mix Columns---------------------------
void test_Mix_Columns(){
    printf("\n######################Test Mix Columns######################\n");
    mix_columns(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_mix_columns,4);
    printf("------------\n");
    printf("Le test de Mix colonne %s\n", egalite_bloc(bloc_test, bloc_apres_mix_columns) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//------------------------Test Mult_Mix_GF---------------------------

void test_mult_mix_gf(){
    printf("\n######################test de Mult_Mix_GF######################\n\n");
    uint8_t test1 = mult_mix_gf(0x01, 0xab);
    uint8_t test2 = mult_mix_gf(0x02, 0xd4);
    uint8_t test3 = mult_mix_gf(0x03, 0xbf);
    printf("Multiplication de %02x par %02x donne %02x\n",0x01, 0xab, test1);
    printf("Multiplication de %02x par %02x donne %02x\n",0x02, 0xd4, test2);
    printf("Multiplication de %02x par %02x donne %02x\n",0x03, 0xbf, test3);
    if((test3 == 0xda) && (test2 == 0xb3) && (test1 == 0xab)){
        printf("3 tests réussi sur mult_mix_gf()\n");
    }
    else {
        printf("test1 : %s\ntest2 : %s\ntest3 : %s\n", (test1 == 0xab)? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m", (test2 == 0xb3)? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m", (test3 == 0xd4)? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    }
}

//------------------------Test Inverse_Mix_Colonne---------------------------

void test_Inverse_Mix_Colonne(){
    printf("\n######################Test Inverse_Mix_Colonne######################\n");
    Inverse_Mix_Colonne(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_shift_rows,4);
    printf("------------\n");
    printf("Le test de Inverse Mix colonne %s\n", egalite_bloc(bloc_test, bloc_apres_shift_rows) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//------------------------Test Inverse_Shift_rows-----------------------

void test_Inverse_Shift_rows(){
    printf("\n######################Test Inverse_Shift_rows######################\n");
    Inverse_Shift_rows(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_sub_bytes,4);
    printf("------------\n");
    printf("Le test de Inverse Shift Rows %s\n", egalite_bloc(bloc_test, bloc_apres_sub_bytes) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//------------------------Test Inverse Sub bytes-----------------------

void test_Inverse_Sub_bytes(){
    printf("\n######################Test Inverse Sub bytes######################\n");
    Inverse_Sub_bytes(bloc_test);
    print_bloc(bloc_test,4);
    printf("------------\n");
    print_bloc(bloc_apres_add_round_key,4);
    printf("------------\n");
    printf("Le test de Inverse Sub bytes %s\n", egalite_bloc(bloc_test, bloc_apres_add_round_key) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

//----------------------------Test rot mat-----------------------------------------------

void test_rotmat(){
    printf("\n######################Test rotmat######################\n");
    uint8_t bloc_test_rot[4][4] = {{0x32, 0x43, 0xf6, 0xa8},
                                   {0x88, 0x5a, 0x30, 0x8d},
                                   {0x31, 0x31, 0x98, 0xa2},
                                   {0xe0, 0x37, 0x07, 0x34}
    };
    printf("matrice de depart :\n");
    print_bloc(bloc_test,4);
    rotmat(bloc_test);
    printf("------------\n");
    printf("matrice de retournée :\n");
    print_bloc(bloc_test,4);
    printf("------------\n");
    printf("Le test de rot mat %s\n", egalite_bloc(bloc_test, bloc_test_rot) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    rotmat(bloc_test);
}

//--------------------------Test Add Round Key --------------------------------------
void test_add_round_key(int a){
    printf("\n######################Test Add Round Key######################\n");
    Add_RK(bloc_test, bloc_add_round_key);
    print_bloc(bloc_test, 4);
    printf("------------\n");
    if(a==1){
        print_bloc(bloc_apres_add_round_key, 4);
        printf("------------\n");
        printf("Le test de Add Round Key %s\n", egalite_bloc(bloc_test, bloc_apres_add_round_key) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    }else{
        print_bloc(bloc_initial, 4);
        printf("------------\n");
        printf("Le test de Add Round Key %s\n", egalite_bloc(bloc_test, bloc_initial) ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    }
}

//--------------------------Test cypher et inverse cypher --------------------------------------

void test_cic1(){
    printf("\n######################Test cypher et inverse cypher######################\n");
    char blocc[100] = "3243f6a8885a308d313198a2e0370734";
    char keyc[100] = "2b7e151628aed2a6abf7158809cf4f3c";
    int kl = 4;
    uint8_t res_test1[4][4] = {
        {0x39, 0x02, 0xdc, 0x19},
        {0x25, 0xdc, 0x11, 0x6a},
        {0x84, 0x09, 0x85, 0x0b},
        {0x1d, 0xfb, 0x97, 0x32}
    };
    printf("\n######################Test1######################\n");
    state src; 
    crea_tab(blocc,src,4);
    printf("\n\nSRC:\n");
    print_bloc(src,4);

    state dst;

    word key[4];
    crea_tab(keyc,key,4);
    printf("\nKEY\n");
    print_bloc(key,4);

    word lkey[60];
    KeyExp(key,lkey,4);

    aes_encrypt(dst,src,lkey,kl);
    printf("\n\nDST:\n");
    print_bloc(dst,4);

    bool res_encrypt_test1 = egalite_bloc(dst, res_test1);

    aes_decrypt(src,dst,lkey,kl);
    printf("\n\nSRC:\n");
    print_bloc(src,4);
    bool res_decrypt_test1 = egalite_bloc(src, bloc_initial);
    printf("\nLe test1 de aes encrypt :%s\n", res_encrypt_test1 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("Le test1 de aes decrypt :%s\n", res_decrypt_test1 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

void test_cic2(){
    printf("\n######################Test2######################\n");
    char blocc2[100] = "00112233445566778899aabbccddeeff";
    char keyc2[100] = "000102030405060708090a0b0c0d0e0f1011121314151617";
    int kl2 = 6;
    uint8_t src_test2[4][4] = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}
    };
    uint8_t dst_test2[4][4] = {
        {0xdd, 0x86, 0x6e, 0xec},
        {0xa9, 0x4c, 0xaf, 0x0d},
        {0x7c, 0xdf, 0x70, 0x71},
        {0xa4, 0xe0, 0xa0, 0x91}
    };
    state src2; 
    crea_tab(blocc2,src2,4);
    printf("\n\nSRC:\n");
    print_bloc(src2,4);

    state dst2;

    word key2[4];
    crea_tab(keyc2,key2,6);
    printf("\nKEY\n");
    print_bloc(key2,6);

    word lkey2[60];
    KeyExp(key2,lkey2,6);

    aes_encrypt(dst2,src2,lkey2,kl2);
    printf("\n\nDST:\n");
    print_bloc(dst2,4);
    bool res_encrypt_test2 = egalite_bloc(dst2, dst_test2);

    aes_decrypt(src2,dst2,lkey2,kl2);
    printf("\n\nSRC:\n");
    print_bloc(src2,4);
    bool res_decrypt_test2 = egalite_bloc(src2, src_test2);
    printf("\nLe test2 de aes encrypt :%s\n", res_encrypt_test2 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("Le test2 de aes decrypt :%s\n", res_decrypt_test2 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}

void test_cic3(){
    printf("\n######################Test3######################\n");
    char blocc3[] = "00112233445566778899aabbccddeeff";
    char keyc3[] = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    int kl3 = 8;
    uint8_t dst_test3[4][4] = {
        {0x8e, 0x51, 0xea, 0x4b},
        {0xa2, 0x67, 0xfc, 0x49},
        {0xb7, 0x45, 0x49, 0x60},
        {0xca, 0xbf, 0x90, 0x89}
    };
    uint8_t src_test3[4][4] = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}
    };


    state src3; 
    crea_tab(blocc3,src3,4);
    printf("\n\nSRC:\n");
    print_bloc(src3,4);

    state dst3;

    word key3[4];
    crea_tab(keyc3,key3,8);
    printf("\nKEY\n");
    print_bloc(key3,8);

    word lkey3[60];
    KeyExp(key3,lkey3,8);

    aes_encrypt(dst3,src3,lkey3,kl3);
    printf("\n\nDST:\n");
    print_bloc(dst3,4);
    bool res_encrypt_test3 = egalite_bloc(dst3, dst_test3);

    aes_decrypt(src3,dst3,lkey3,kl3);
    printf("\n\nSRC:\n");
    print_bloc(src3,4);
    bool res_decrypt_test3 = egalite_bloc(src3, src_test3);
    printf("\nLe test3 de aes encrypt :%s\n", res_encrypt_test3 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
    printf("Le test3 de aes decrypt :%s\n", res_decrypt_test3 ? "\033[32mRAS\033[00m" : "\033[31mEchec\033[00m");
}


int main(){
    printf("\n------------------------------------------------\n");
    printf("----------------------test----------------------\n");
    printf("------------------------------------------------\n\n");
    test_rotmat();
    test_egalite_bloc();
    test_decalaged();
    test_decalageg();
    printf("\n#########################test AES#########################\n");
    printf("Notre bloc de base est :\n");
    print_bloc(bloc_initial,4);
    test_add_round_key(1);
    test_Sub_Bytes();
    test_Shift_Rows();
    test_mult_mix_gf();
    test_Mix_Columns();
    test_Inverse_Mix_Colonne();
    test_Inverse_Shift_rows();
    test_Inverse_Sub_bytes();
    test_add_round_key(0);
    test_cic1();
    test_cic2();
    test_cic3();
    return 0;
}


