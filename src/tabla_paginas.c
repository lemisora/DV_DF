#include "tabla_paginas.h"
#include "file_entries.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int add_entry(tabla table, table_entry_t entrada, int index){
    table[index] = entrada;
    return EXIT_SUCCESS;
}

int init_table(FILE* file, tabla* tabla_paginas, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    *tabla_paginas = (tabla)malloc(sizeof(table_entry_t)*size);
    if(tabla_paginas == NULL){
        perror("No se pudo reservar memoria para la tabla de páginas");
        fclose(file);
        return EXIT_FAILURE;
    }
    /* Añadir entradas */
    leer(file, tabla_paginas, size, tam_pag, num_pag, num_marcos);
    fclose(file);
    return EXIT_SUCCESS;
}

unsigned int getMarco(tabla t, unsigned int index){
    unsigned int frame;
    frame = t[index].n_frame;
    return frame;
}

int translateVD_PD(tabla t, const int tam_pag, const int num_pag, const int num_marcos, const int bits_desp, unsigned int DV){
    unsigned int DF = 0;    //Dirección física
    unsigned int DV_TEMP = DV;  //Variable auxiliar para tratar con bits
    unsigned int mask = 0;  //Máscara
    unsigned int n_pag = 0; //Acá se almacenará el número de página
    unsigned int n_marco = 0;   //Acá se almacenará el número de marco
    unsigned int desp = 0;  //Acá se almacenará el valor de desplazamiento

    //Averiguando el número de página de la D.V.
    DV_TEMP >>= bits_desp;//Se eliminan los bits del desplazamientoo
    n_pag = DV_TEMP;

    //Averiguando el valor de desplazamiento
    DV_TEMP <<= bits_desp;//Se colocan los bits de número de página en su lugar original
    mask = DV_TEMP ^ UINT_MAX;//Con OR se forma la máscara de 11111 para poder averiguar el desplazamiento
    desp = DV & mask;//Enmascaramiento de la dirección original para obtener desplazamiento

    //Formar la dirección física
    n_marco = getMarco(t, n_pag);//Obtener el número de marco de la tabla de páginas
    //printf("Valor número de marco: %u", n_marco);
    DF = n_marco << bits_desp;//Colocar el valor del marco en las posiciones correctas con corrimiento
    DF |= desp;//Encender los bits del desplazamiento

    return DF;
}

void print_table(tabla t, unsigned int size){
    printf("|A|R|M|P|C|FRAME|\n");
    for(int i = 0; i < size; i++){
        printf("|%d|%d|%d|%d|%d|%u|\n",
            t[i].b_permiso,
            t[i].b_ref,
            t[i].b_mod,
            t[i].b_pres_aus,
            t[i].b_cache,
            t[i].n_frame);
    }
}
