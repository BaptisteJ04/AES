all: aes_test

.PHONY: all clean test demo

test: aes_test
	./aes_test

demo: test_ecb
	./test_ecb

aes_test: F_AES.o tests_AES.o F_Inverse_AES.o Table_de_multiplication.o cic.o
	gcc F_AES.o tests_AES.o F_Inverse_AES.o Table_de_multiplication.o cic.o -o aes_test

test_ecb: F_AES.o F_Inverse_AES.o Table_de_multiplication.o cic.o ecb.o bmp.o cbc.o
	gcc F_AES.o F_Inverse_AES.o Table_de_multiplication.o cic.o ecb.o bmp.o cbc.o -o test_ecb


bmp.o: bmp.c bmp.h
	gcc -Wall -Wextra -c bmp.c  -o bmp.o

cbc.o: cbc_encryption.c cbc_encryption.h
	gcc -Wall -Wextra -c cbc_encryption.c  -o cbc.o

ecb.o: ecb_encryption.c ecb_encryption.h
	gcc -Wall -Wextra -c ecb_encryption.c  -o ecb.o

cic.o: Cypher_InvCypher.c Cypher_InvCypher.h
	gcc -Wall -Wextra -c Cypher_InvCypher.c  -o cic.o

F_Inverse_AES.o: F_Inverse_AES.c F_Inverse_AES.h
	gcc -Wall -Wextra -c F_Inverse_AES.c  -o F_Inverse_AES.o

F_AES.o: F_AES.c F_AES.h
	gcc -Wall -Wextra -c F_AES.c -o F_AES.o

tests_AES.o: tests_AES.c F_AES.h
	gcc -Wall -Wextra -c tests_AES.c -o tests_AES.o

Table_de_multiplication.o: Table_de_multiplication.c Table_de_multiplication.h
	gcc -Wall -Wextra -c Table_de_multiplication.c -o Table_de_multiplication.o

Table: generation_table.o main_generation.o
	gcc generation_table.o main_generation.o -o Table

generation_table.o: ./generation_Table/generation_tables.c ./generation_Table/generation_tables.h
	gcc -Wall -Wextra -c ./generation_Table/generation_tables.c -o generation_table.o

main_generation.o: ./generation_Table/main_generation.c
	gcc -Wall -Wextra -c ./generation_Table/main_generation.c -o main_generation.o

clean:
	rm -f *.o aes_test test_ecb Table cic