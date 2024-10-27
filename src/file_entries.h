#include "tabla_paginas.h"
#ifndef STR_ENTR_H
#define STR_ENTR_H

#include <stdio.h>

//Función para leer los datos de la primera línea del archivo que contienen información de la tabla
void leer_primera_linea(FILE* file, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);

//Función para leer los datos del archivo y cargarlos en memoria
void leer(FILE* file, tabla* t, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos);

//Función para generar entradas de la tabla de páginas y guardarlas en un archivo de texto
void generadorEntradas(FILE* file, unsigned int tam_pag, unsigned int num_pag, unsigned int num_marcos);

#endif
