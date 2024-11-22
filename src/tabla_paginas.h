#include <stdlib.h>
#include <stdio.h>
#ifndef TABLA_H
#define TABLA_H

typedef struct entrada table_entry_t;
typedef table_entry_t* tabla;

typedef struct page_num n_page_df;

struct page_num{
    unsigned int DF;
    unsigned int num_page;
};

struct entrada{
    int b_permiso;  //Permiso de lectura/escritura, 0 solo lectura, 1 lectura/escritura
    int b_ref;      //0 no accedida recientemente, 1 accedida recientemente
    int b_mod;      //0 no modificada, 1 modificada
    int b_pres_aus; //0 no está en memoria principal, 1 está en memoria principal
    int b_cache;    //0 cache habilitado, 1 caché inhabilitado
    unsigned int n_frame;
};

//Función para añadir entradas a la tabla
void add_entry(tabla table, table_entry_t entrada, int index);

//Función para obtener el número de página
int get_num_page(FILE *archivo,unsigned int* num_pag, unsigned int* tam_pag, unsigned int* num_marcos);

//Función para inicializar la tabla
int init_table(FILE* file, tabla* tabla_paginas, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);

//Función para encontrar el número de marco dado el índice de página
unsigned int getMarco(tabla t, unsigned int index);

//Función para traducir dirección virtual al física
n_page_df translateVD_PD(tabla t, const int tam_pag, const int num_pag, const int num_marcos, const int bits_desp, unsigned int DV);

//Función para imprimir la tabla de páginas
void print_table(tabla t, unsigned int size);

//Función para imprimir en formato binario
void print_binary(unsigned long int value, unsigned int page_size);

//Función para imprimir tabla en formato binario
void print_table_binary(tabla t, unsigned int size, unsigned int marco_size, int print_decimal);

void print_especific_table(tabla t, unsigned int index);

//Función para imprimir una entrada específica de la tabla
void print_specific_table_binary(tabla t, unsigned int index, unsigned int size_marco);

unsigned long int binary_especific_table(tabla t, unsigned int index, unsigned int marco_size, unsigned int page_size);
#endif
