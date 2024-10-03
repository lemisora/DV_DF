#include <stdlib.h>
#include <stdio.h>
#ifndef TABLA_H
#define TABLA_H

typedef struct entrada table_entry_t;
typedef table_entry_t* tabla;

struct entrada{
    int b_permiso;  //Permiso de lectura/escritura, 0 solo lectura, 1 lectura/escritura
    int b_ref;      //0 no accedida recientemente, 1 accedida recientemente
    int b_mod;      //0 no modificada, 1 modificada
    int b_pres_aus; //0 no está en memoria principal, 1 está en memoria principal
    int b_cache;    //0 cache habilitado, 1 caché inhabilitado
    unsigned int n_frame;
};

int add_entry(tabla table, table_entry_t entrada, int index); //Función para añadir entradas a la tablaa
int init_table(FILE* file, tabla* tabla_paginas, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);   //Función para inicializar la tabla
unsigned int getMarco(tabla t, unsigned int index);   //Función para encontrar el número de marco dado un índice de página
int translateVD_PD(tabla t, const int tam_pag, const int num_pag, const int num_marcos, const int bits_desp, unsigned int DV);   //Función para traducir memoria virtual a física
void print_binary(unsigned long int value, unsigned int page_size);
void print_table(tabla t, unsigned int size);
void print_especific_table(tabla t, unsigned int index);
unsigned long int binary_especific_table(tabla t, unsigned int index, unsigned int marco_size, unsigned int page_size);
#endif
