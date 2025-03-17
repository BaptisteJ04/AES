/* bmp.c: utilitaires pour la manipulation de fichiers images au format BMP */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bmp.h"
#include "ecb_encryption.h"
#include "cbc_encryption.h"


typedef struct chunk {
  int size;
  unsigned char *data;
} chunk;

typedef struct bmp_image {
  chunk *header, *pixels;
} bmp_image;

void*
mem_alloc(unsigned int size)
{
  void *r;

  r = malloc(size);
  if (r == NULL)
  {
    printf("bmp.c: mem_alloc(): plus de mémoire disponible!\n");
    printf("(Taille demandée: %d)\n", size);
    exit(1);
  }
  return r;
}

chunk*
chunk_allocate(unsigned int size)
{
  chunk *ch;

  ch = mem_alloc(sizeof(chunk));
  ch -> size = size;
  ch -> data = mem_alloc(size);

  return ch;
}

chunk*
chunk_copy(chunk *src)
{
  chunk *r;

  r = chunk_allocate(src -> size);
  memcpy(r -> data, src -> data, src -> size);

  return r;
}

chunk*
as_chunk(char *src, int size)
{
  chunk *ch;

  ch = mem_alloc(sizeof(chunk));
  ch -> size = size;
  ch -> data = src;

  return ch;
}

void
chunk_free(chunk *c)
{
  free(c -> data);
  free(c);
}

int
chunk_get_size(chunk *c)
{
  return c -> size;
}

char*
chunk_get_data(chunk *c)
{
  return c -> data;
}

void
int_to_bytes(unsigned char *d, int s)
{
  d[0] = s;
  d[1] = s >> 8;
  d[2] = s >> 16;
  d[3] = s >> 24;
}

unsigned int
bytes_to_int(unsigned char *a)
{
  return (a[3] << 24) + (a[2] << 16) + (a[1] << 8) + a[0];
}

bmp_image*
bmp_read(char *fname)
{
  FILE *f;
  char basic_header[14];
  chunk *header, *pixels;
  unsigned int r, header_size, file_size, pixels_size;
  const unsigned int basic_header_size = 14;

  f = fopen(fname, "r");        /* open file <fname> for reading */
  if (f == NULL)                /* error handling */
  {
    perror("bmp_read, fopen()");
    printf("(file name: %s)\n", fname);
    exit(2);
  }

/* The first header in a bitmap file is 14 bytes long */
/* This header contains all the information needed to split
the file into a "headers" part, and a "pixels" part. */
  
  r = fread(basic_header, 1, basic_header_size, f);
  if (r != basic_header_size)
  {
    perror("bmp_read, fread(), basic header");
    exit(3);
  }

  r = fseek(f, 0, SEEK_SET);   /* return to start of file */
  if (r != 0)
  {
    perror("bmp_read, fseek()");
    exit(4);
  }

  header_size = bytes_to_int((unsigned char*)basic_header+10);
  header = chunk_allocate(header_size);

  r = fread(header -> data, 1, header_size, f);
  if (r != header_size)
  {
    perror("bmp_read, fread(), header");
    exit(5);
  }

  file_size = bytes_to_int((unsigned char*)basic_header+2);
  pixels_size = file_size - header_size;

  pixels = chunk_allocate(pixels_size);

  r = fread(pixels -> data, 1, pixels_size, f);
  if (r != pixels_size)
  {
    perror("bmp_read, fread(), pixels");
    exit(6);
  }

  fclose(f);    /* Be nice, close the file when finished with it */

  return bmp_create(header, pixels);
}

void
bmp_write(char *fname, bmp_image *img)
{
  FILE *f;
  int r;

  f = fopen(fname, "wx");        /* open file <fname> for writing */
  if (f == NULL)                /* error handling */
  {
    perror("bmp_write, fopen()");
    printf("(file name: %s)\n", fname);
    exit(7);
  }

/* Indicate the correct values in the header */

/* Offset is the size of the header */
  int_to_bytes((unsigned char*) img -> header -> data+10, img -> header -> size);

/* File size is the sum of the sizes of header and pixels chunks */
  int_to_bytes((unsigned char*) img -> header -> data+2, img -> header -> size + img -> pixels -> size);

  r = fwrite(img -> header -> data, 1, img -> header -> size, f);
  if (r != img -> header -> size)
  {
    perror("bmp_write, fwrite(), header");
    exit(8);
  }

  r = fwrite(img -> pixels -> data, 1, img -> pixels -> size, f);
  if (r != img -> pixels -> size)
  {
    perror("bmp_write, fwrite(), pixels");
    exit(9);
  }

  fclose(f);    /* Be nice, close the file when finished with it */
}


void
bmp_free(bmp_image *img)
{
  chunk_free(img -> header);
  chunk_free(img -> pixels);
  free(img);
}
  
bmp_image*
bmp_create(chunk *header, chunk *pixels)
{
  bmp_image *img;

  img = mem_alloc(sizeof(bmp_image));
  img -> header = header;
  img -> pixels = pixels;

  return img;
}
  
chunk*
bmp_get_header(bmp_image *img)
{
  return img -> header;
}

chunk*
bmp_get_pixels(bmp_image *img)
{
  return img -> pixels;
}

void ecb_encrypt_img(char *source , char *destination){
  bmp_image *img, *img2;
  chunk *h, *h2, *p, *p2;

  /* Chargement de l'image en mémoire */
  img = bmp_read(source);

  /* Récupération de l'en-tête et des pixels *?*/
  h = bmp_get_header(img);
  p = bmp_get_pixels(img);

  /* Copie des blocs en-tête et pixels*/
  
  h2 = chunk_copy(h);
  p2 = chunk_copy(p);
  img2 = bmp_create(h2, p2);

  char keyc[]="000102030405060708090a0b0c0d0e0f";
  word key[4];

  crea_tab(keyc,key,4);
 
  aes_ecb_encrypt(&(p2->data),&(p2->size),p->data,p->size,key,4);

    /* Libération de la mémoire de l'image originale */
  bmp_free(img);

  /* Ecriture de l'image img2 sur disque */
  remove(destination);
  bmp_write(destination, img2);
}

void ecb_decrypt_img(char *source , char *destination){
  bmp_image *img, *img2;
  chunk *h, *h2, *p, *p2;

  /* Chargement de l'image en mémoire */
  img = bmp_read(source);

  /* Récupération de l'en-tête et des pixels *?*/
  h = bmp_get_header(img);
  p = bmp_get_pixels(img);

  /* Copie des blocs en-tête et pixels*/
  
  h2 = chunk_copy(h);
  p2 = chunk_copy(p);
  img2 = bmp_create(h2, p2);

  char keyc[]="000102030405060708090a0b0c0d0e0f";
  word key[4];

  crea_tab(keyc,key,4);
 
  aes_ecb_decrypt(&(p2->data),&(p2->size),p->data,p->size,key,4);

    /* Libération de la mémoire de l'image originale */
  bmp_free(img);

  /* Ecriture de l'image img2 sur disque */
  remove(destination);
  bmp_write(destination, img2);
}



void cbc_encrypt_img(char *source , char *destination){
  bmp_image *img, *img2;
  chunk *h, *h2, *p, *p2;

  /* Chargement de l'image en mémoire */
  img = bmp_read(source);

  /* Récupération de l'en-tête et des pixels *?*/
  h = bmp_get_header(img);
  p = bmp_get_pixels(img);

  /* Copie des blocs en-tête et pixels*/
  
  h2 = chunk_copy(h);
  p2 = chunk_copy(p);
  img2 = bmp_create(h2, p2);

  char keyc[]="000102030405060708090a0b0c0d0e0f";
  word key[4];

  crea_tab(keyc,key,4);

  unsigned char vi[] = "000102030405060708090a0b0c0d0e0f";
 
  aes_cbc_encrypt(&(p2->data),&(p2->size),p->data,p->size,vi,key,4);

    /* Libération de la mémoire de l'image originale */
  bmp_free(img);

  /* Ecriture de l'image img2 sur disque */
  remove(destination);
  bmp_write(destination, img2);
}



void cbc_decrypt_img(char *source , char *destination){
  bmp_image *img, *img2;
  chunk *h, *h2, *p, *p2;

  /* Chargement de l'image en mémoire */
  img = bmp_read(source);

  /* Récupération de l'en-tête et des pixels *?*/
  h = bmp_get_header(img);
  p = bmp_get_pixels(img);

  /* Copie des blocs en-tête et pixels*/
  
  h2 = chunk_copy(h);
  p2 = chunk_copy(p);
  img2 = bmp_create(h2, p2);

  char keyc[]="000102030405060708090a0b0c0d0e0f";
  word key[4];

  unsigned char vi[] = "000102030405060708090a0b0c0d0e0f";

  crea_tab(keyc,key,4);
 
  aes_cbc_decrypt(&(p2->data),&(p2->size),p->data,p->size,vi,key,4);

    /* Libération de la mémoire de l'image originale */
  bmp_free(img);

  /* Ecriture de l'image img2 sur disque */
  remove(destination);
  bmp_write(destination, img2);
}

int
main()
{
  ecb_encrypt_img("Tux.bmp","Tux_encrypte.bmp");
  ecb_decrypt_img("Tux_encrypte.bmp","Tux_decrypte.bmp");

  cbc_encrypt_img("Tux.bmp","Tux_encrypte2.bmp");
  cbc_decrypt_img("Tux_encrypte2.bmp","Tux_decrypte2.bmp");

  return 0;
}