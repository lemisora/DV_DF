#include "tabla_paginas.h"
#define TAM_TABLA 16
#define N_MARCOS 4

#define MASK_U_INT 1 << 31

#include <stdio.h>
#include <stdlib.h>

void printBinary(unsigned int num) {
    unsigned int mask = MASK_U_INT;  // Comenzamos con el bit más significativo
    int printed = 0;

    while (mask) {
        if (num & mask) {
            printf("1");
            printed = 1;
        } else if (printed) {
            printf("0");
        }
        mask >>= 1;  // Desplazamos la máscara hacia la derecha
    }

    if (!printed) {
        printf("0");  // Si el número es 0
    }
    printf("\n");
}


int main(){
    table_entry_t ent1 = {  .b_permiso = 1,
                            .b_ref = 1,
                            .b_mod = 1,
                            .b_pres_aus = 1,
                            .b_cache = 1,
                            .n_frame = 3};
    // unsigned int test_bit = 10;
    // printf("Valor de la variable con el bit de prueba: ");
    // printBinary(test_bit);
    unsigned int DV = 0;
    ent1.b_permiso <<= TAM_TABLA;
    ent1.b_ref <<= TAM_TABLA-1;
    ent1.b_mod <<= TAM_TABLA-2;
    ent1.b_pres_aus <<= TAM_TABLA-3;
    ent1.b_cache <<= TAM_TABLA-4;

    DV = DV | ent1.b_permiso;
    DV = DV | ent1.b_ref;
    DV = DV | ent1.b_mod;
    DV = DV | ent1.b_pres_aus;
    DV = DV | ent1.b_cache;
    DV = DV | ent1.n_frame;
    printf("Valor de bit permiso: %u\n", ent1.b_permiso);
    printf("Valor de bit referencia: %u\n", ent1.b_ref);
    printf("Valor de bit modificada: %u\n", ent1.b_mod);
    printf("Valor de bit presente/ausente: %u\n", ent1.b_pres_aus);
    printf("Valor de bit de caché: %u\n", ent1.b_cache);
    printf("Valor de DV: %u\n", DV);
    printf("Valor de DV en binario: ");
    printBinary(DV);
    return EXIT_SUCCESS;
}
