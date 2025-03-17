#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>



// Déclaration des variables globales
extern uint8_t mat_mix[4][4];
extern uint8_t bloc_initial[4][4];
extern uint8_t bloc_test[4][4];
extern uint8_t bloc_add_round_key[4][4];
extern uint8_t bloc_apres_add_round_key[4][4];
extern uint8_t bloc_apres_sub_bytes[4][4];
extern uint8_t bloc_apres_shift_rows[4][4];
extern uint8_t bloc_apres_mix_columns[4][4];

//---------------------------utilitaire-----------------------------------------

bool egalite_bloc(uint8_t bloc[4][4], uint8_t mat_res[4][4]);

bool egalite_tableau(uint8_t tableau1[4], uint8_t tableau2[4]);

void rotmat(uint8_t bloc[4][4]);

void copieb(uint8_t blocs[][4],uint8_t blocd[][4],int taille);

void copiec(uint8_t cols[4],uint8_t cold[4]);

void xor(uint8_t cola[4],uint8_t colb[4]);

void crea_tab(char phrase[],uint8_t bloc[][4],int taille);

void print_bloc(uint8_t bloc[][4],int taille);

void print_tableau(uint8_t tableau[4]);

void rotword(uint8_t col[4]);

//---------------------------Sub_bytes-----------------------------------------

void subbytes(uint8_t bloc[4][4]);

void subbytesCol(uint8_t col[4]);

//---------------------------Add_RK-----------------------------------------

void Add_RK (uint8_t bloc[4][4],uint8_t key[4][4]);

//---------------------------Shift_rows-----------------------------------------

void decalageg(uint8_t row[4], int num_dec);

void shift_rows(uint8_t bloc[4][4]);

//---------------------------Mix_Columns-----------------------------------------

uint8_t mult_mix_gf(uint8_t a, uint8_t b);

void mix_columns(uint8_t bloc[4][4]);

//---------------------------Key expantion-----------------------------------------

void decoupe192(uint8_t lkeyp[10][8][4],uint8_t lkeyf[15][4][4]);

void decoupe256(uint8_t lkeyp[10][8][4],uint8_t lkeyf[15][4][4]);

void list_key_to_word(uint8_t keylist[15][4][4],uint8_t keyl[60][4]);

void KeyExp(uint8_t bloc[][4],uint8_t keylist[60][4],int taille);

void extrat_key(uint8_t keyl[60][4],uint8_t bloc[4][4],int i);