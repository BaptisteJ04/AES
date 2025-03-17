#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "F_Inverse_AES.h"
#include "F_AES.h"

typedef uint8_t state [4][4];

typedef uint8_t word[4];

void aes_encrypt(state dst,state src,word key[], int key_lenght);
void aes_decrypt(state dst,state src,word key[], int key_lenght);