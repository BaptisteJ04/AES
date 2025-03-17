#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "F_Inverse_AES.h"
#include "Cypher_InvCypher.h"
#include "F_AES.h"
#include "Table_de_multiplication.h"

int aes_ecb_encrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, word key[], int key_length);
int aes_ecb_decrypt(unsigned char** dst, int *dst_data_length, unsigned char* src, int src_data_length, word key[], int key_length);