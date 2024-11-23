#include "tabla_paginas.h"
#include "file_entries.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void add_entry(tabla table, table_entry_t entrada, int index){
    table[index] = entrada;
}

int get_num_page(FILE *archivo,unsigned int* num_pag, unsigned int* tam_pag, unsigned int* num_marcos){
    leer_primera_linea(archivo, tam_pag, num_pag, num_marcos);
    return EXIT_SUCCESS;
}

int init_table(FILE* file, tabla* tabla_paginas, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    *tabla_paginas = (tabla)malloc(sizeof(table_entry_t)*size);
    if(tabla_paginas == NULL){
        perror("No se pudo reservar memoria para la tabla de páginas");
        return EXIT_FAILURE;
    }
    /* Añadir entradas */
    leer(file, tabla_paginas, size, tam_pag, num_pag, num_marcos);
    return EXIT_SUCCESS;
}

unsigned int getMarco(tabla t, unsigned int index){
    unsigned int frame;
    frame = t[index].n_frame;
    return frame;
}

int get_b_pres_aus(tabla t, unsigned int n_page){
    int b_pres_aus = t[n_page].b_pres_aus;
    return b_pres_aus;
}

n_page_df translateVD_PD(tabla t, const int tam_pag, const int num_pag, const int num_marcos, const int bits_desp, unsigned int DV){
    n_page_df temp;

    unsigned int DF = 0;    //Dirección física
    unsigned int DV_TEMP = DV;  //Variable auxiliar para tratar con bits
    unsigned int mask = 0;  //Máscara
    unsigned int n_pag = 0; //Acá se almacenará el número de página
    unsigned int n_marco = 0;   //Acá se almacenará el número de marco
    unsigned int desp = 0;  //Acá se almacenará el valor de desplazamiento

    //Averiguando el número de página de la D.V.
    DV_TEMP >>= bits_desp;//Se eliminan los bits del desplazamientoo
    n_pag = DV_TEMP;

    printf("\nNúmero de página: %u\n", n_pag);

    if(!get_b_pres_aus(t, n_pag)){
        temp.estado = 0;    //Estado fallido, por fallo de página
        return temp;
    }

    //Averiguando el valor de desplazamiento
    DV_TEMP <<= bits_desp;//Se colocan los bits de número de página en su lugar original
    mask = DV_TEMP ^ UINT_MAX;//Con OR se forma la máscara de 11111 para poder averiguar el desplazamiento
    desp = DV & mask;//Enmascaramiento de la dirección original para obtener desplazamiento

    //Formar la dirección física
    n_marco = getMarco(t, n_pag);//Obtener el número de marco de la tabla de páginas
    //printf("Valor número de marco: %u", n_marco);
    DF = n_marco << bits_desp;//Colocar el valor del marco en las posiciones correctas con corrimiento
    DF |= desp;//Encender los bits del desplazamiento

    temp.DF = DF;
    temp.num_page = n_pag;
    temp.estado = 1;    //Estado exitoso
    return temp;
}

void print_table(tabla t, unsigned int size, unsigned int marco_size, int print_decimal){
    if (print_decimal)
    {
        printf("|i|\t|R|M|A|C|P|FRAME_BINARY|\t|FRAME_DECIMAL|\n\n");
    }else{
        printf("|i|\t|R|M|A|C|P|FRAME_BINARY|\n\n");
    }

    for(int i = 0; i < size; i++){
        printf("|%d|\t|%d|%d|%d|%d|%d",
            i,
            t[i].b_ref,
            t[i].b_mod,
            t[i].b_permiso,
            t[i].b_cache,
            t[i].b_pres_aus);
        printf("|");
        print_binary(t[i].n_frame, marco_size);

        if(print_decimal){
            printf("|%17s|%u", "", t[i].n_frame);
        }

        printf("|\n");
    }
}

void print_specific_table_binary(tabla t, unsigned int index, unsigned int size_marco){
    printf("Contenido: %u\n", t[index].raw_entry);
    printf("\n|R|M|A|C|P|FRAME_BINARY|\n");
    printf("|%d|%d|%d|%d|%d",
        t[index].b_ref,
        t[index].b_mod,
        t[index].b_permiso,
        t[index].b_cache,
        t[index].b_pres_aus);
    printf("|");
    print_binary(t[index].n_frame, size_marco);
    printf("|\n");
}

void print_binary(unsigned long int value, unsigned int page_size) {
    for (int i = (int)log2(page_size)-1; i >= 0; i--) {
        if (i % 4 == 3 && i != 0) {
            printf(" ");
        }
        printf("%lu", (value >> i) & 1UL);
    }
}
