#include "tabla_paginas.h"
#ifndef STR_ENTR_H
#define STR_ENTR_H

#include <stdio.h>
void leer(FILE* file, tabla* t, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);
void generadorEntradas(FILE* file, unsigned int tam_pag, unsigned int num_pag, unsigned int num_marcos);    //Función para generar las entradas de la tabla y ponerlas en un archivo de texto

#endif
