#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//---------------------------Inverse_Sub_bytes-----------------------------------------

void Inverse_Sub_bytes(uint8_t bloc[4][4]);

//---------------------------Shift_rows-----------------------------------------

void decalaged(uint8_t row[4], int num_dec);

void Inverse_Shift_rows(uint8_t bloc[4][4]);

//---------------------------Inverse_Mix_Colonne-----------------------------------------

uint8_t mult_inverse_mix_gf(uint8_t a, uint8_t b);

void Inverse_Mix_Colonne(uint8_t bloc[4][4]);