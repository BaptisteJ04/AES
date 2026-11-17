# C implementation: files and functions

**Authors:** Baptiste Joubert, Julien Albinet

Educational code, not for protecting real data. See the [root README](../README.md) for build instructions.

## Files

### F_AES.c: AES functions

Implements the AES building blocks.

#### Global variables
Several matrices and blocks used for the tests and the AES process:

- `mat_mix[4][4]`: the matrix used by **MixColumns**.
- `bloc_initial[4][4]`: the initial plaintext block.
- `bloc_test[4][4]`: a test block used to check the operations.
- `bloc_add_round_key[4][4]`, `bloc_apres_add_round_key[4][4]`: the block before/after **AddRoundKey**.
- `bloc_apres_sub_bytes[4][4]`: the block after **SubBytes**.
- `bloc_apres_shift_rows[4][4]`: the block after **ShiftRows**.
- `bloc_apres_mix_columns[4][4]`: the block after **MixColumns**.

#### Utility functions

- **egalite_bloc**: checks whether two 4x4 byte blocks are equal.
- **egalite_tableau**: checks whether two 4-element arrays are equal.
- **rotmat**: rotates a 4x4 byte matrix by 90 degrees.
- **copieb**: copies a 2D block into another.
- **copiec**: copies a 4-byte column into another.
- **xor**: XOR of two 4-byte columns.
- **crea_tab**: builds a block array from a hex string (used to initialise blocks).
- **print_bloc**: prints a 4x4 block to the console.
- **print_tableau**: prints a 4-element array to the console.
- **rotword**: rotates a word (column), used in key expansion.

#### AES operations

1. **SubBytes**
   - **subbytes**: replaces each byte of a 4x4 block with its S-Box value.
   - **subbytesCol**: applies **SubBytes** to one column.
2. **AddRoundKey**
   - **Add_RK**: XORs the block with a given round key.
3. **ShiftRows**
   - **decalageg**: shifts one row of the block by `num_dec` positions.
   - **shift_rows**: applies **ShiftRows** to a 4x4 block following the AES rules.
4. **MixColumns**
   - **mult_mix_gf**: multiplication in GF(2⁸), used by **MixColumns**.
   - **mix_columns**: applies **MixColumns** by multiplying each column by the mixing matrix.
5. **Key expansion**
   - **decoupe192**, **decoupe256**: split a 192/256-bit key schedule into the parts needed for round keys.
   - **list_key_to_word**: converts a list of keys into an array of 4-byte words.
   - **KeyExp**: expands the initial key into all round keys.
   - **extrat_key**: extracts the round key for a given round.

---

### F_Inverse_AES.c: inverse AES functions

Implements the inverse operations used for decryption.

- **Inverse_Sub_bytes**: replaces each byte of a 4x4 block with its inverse S-Box value.
- **decaled**: shifts a row in the opposite direction of **ShiftRows**.
- **Inverse_Shift_rows**: applies **Inverse ShiftRows** to a 4x4 block.
- **mult_inverse_mix_gf**: GF(2⁸) multiplication used by **Inverse MixColumns**.
- **Inverse_Mix_Colonne**: applies **Inverse MixColumns** with the inverse mixing matrix.

### Cypher_InvCypher.c

`aes_encrypt` and `aes_decrypt` encrypt/decrypt one 128-bit block with a 128-, 192- or 256-bit key (given as a key length of 4, 6 or 8 words).

### ecb_encryption.c / cbc_encryption.c

ECB and CBC modes (`aes_ecb_encrypt`, `aes_cbc_encrypt`, and the matching decrypt functions) working on byte buffers.

### bmp.c

BMP reading/writing. Its `main` is the image demo: it encrypts and decrypts `Tux.bmp` in ECB and CBC mode (`make demo`).

### tests_AES.c

Test program (`make test`): unit tests of each transformation, plus full encrypt/decrypt tests on the FIPS 197 Appendix C vectors for 128-, 192- and 256-bit keys.

---

## Retrospective

Teamwork was much better on the C part. We structured the work from the start and coded our features separately while staying in almost constant contact. However, we did not always keep our logbook up to date, which sometimes caused confusion about progress, and we underestimated the time some tasks would take. Still, we learned from the mistakes of the Haskell part and improved our coordination.
