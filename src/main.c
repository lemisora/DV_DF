#include "tabla_paginas.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// #define TAM_TABLA 16
// #define N_MARCOS 4

/* Datos importantes para el programa:
    - Tamaño de página
    - Número de páginas
    - Número de marcos

    D.V.
    |No. página|Desplazamiento|

    D.F.
    |No. marco|Desplazamiento|

    Entrada de tabla de páginas
    |b_permiso|b_ref|b_mod|b_pres_aus|b_cache|No. marco|
*/

#define TAM_PAG 1024
#define N_PAG 512
#define N_MARCOS 32

//Elementos de la dirección física
#define BIT_N_MARCOS (int)log2(N_MARCOS) //5 bits
//Desplazamiento 10 bits

//Elementos de la dirección virtual
#define BITS_N_PAG (int)log2(N_PAG) //9 bits
#define BITS_DESP (int)log2(TAM_PAG) //10 bits

#define MASK_U_INT 1 << 31

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
    // const int tam_pag = 1024;
    // const int num_pag = 512;
    // const int num_marcos = 32;
    // const int bits_desp = log2(tam_pag);
    // //printf("Tamaño de desplazamiento: %d", (int)BIT_DESP);
    unsigned int mask = 0;
    unsigned int n_pag = 0; //Acá se almacenará el número de página
    unsigned int n_marco = 0;   //Acá se almacenará el número de marco
    unsigned int desp = 0;  //Acá se almacenará el valor de desplazamiento

    //Para el ejemplo es de 19 bits
    //Suponer la siguiente D.V. -> 0 0010 0000 10 0101 0010
    //Donde n_pag = 32 y desp = 594
    unsigned int DV = 33362;
    printf("Dirección virtual: %u\tEn binario: ", DV);
    printBinary(DV);

    //Para el ejemplo es de 15 bits
    unsigned int DF = 0;

    //Averiguar número de página de la d.v.
    unsigned int DV_TEMP = DV;
    DV_TEMP >>= BITS_DESP;
    n_pag = DV_TEMP;

    DV_TEMP <<= BITS_DESP;
    printf("Valor de DV_TEMP después de recorrimiento: %u\n", DV_TEMP);
    mask = DV_TEMP ^ UINT_MAX;
    printf("Valor de mask después de enmascaramiento con XOR: %u\n", mask);
    desp = DV & mask;

    printf("N. pág: %u\tDesp: %u\n", n_pag, desp);

    //Suponer que en la página 32 se tiene el número de marco 12
    //Averiguar la dirección física con los datos obtenidos
    n_marco = 12;
    DF = n_marco << BITS_DESP;
    DF |= desp;
    //Debería resultar en 01100 10 0101 0010 que en decimal es: 12882
    printf("Dirección físca: %u\tEn binario: ", DF);
    printBinary(DF);
    return EXIT_SUCCESS;
}
