#include "tabla_paginas.h"
#ifndef STR_ENTR_H
#define STR_ENTR_H

#include <stdio.h>
void leer_primera_linea(FILE* file, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);
void leer(FILE* file, tabla* t, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);
void print_binary(unsigned long int value, unsigned int page_size);
void generadorEntradas(FILE* file, unsigned int tam_pag, unsigned int num_pag, unsigned int num_marcos);    //Función para generar las entradas de la tabla y ponerlas en un archivo de texto

#endif
