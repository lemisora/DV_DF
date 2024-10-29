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
        //fclose(file);
        return EXIT_FAILURE;
    }
    /* Añadir entradas */
    leer(file, tabla_paginas, size, tam_pag, num_pag, num_marcos);
    //fclose(file);
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

void print_table_binary(tabla t, unsigned int size, unsigned int marco_size, int print_decimal){
    if (print_decimal)
    {
        printf("|i|\t|A|R|M|P|C|FRAME_BINARY|\t|FRAME_DECIMAL|\n\n");
    }else{
        printf("|i|\t|A|R|M|P|C|FRAME_BINARY|\n\n");
    }

    for(int i = 0; i < size; i++){
        printf("|%d|\t|%d|%d|%d|%d|%d",
            i,
            t[i].b_permiso,
            t[i].b_ref,
            t[i].b_mod,
            t[i].b_pres_aus,
            t[i].b_cache);
        printf("|");
        print_binary(t[i].n_frame, marco_size);

        if(print_decimal){
            printf("|%17s|%u", "", t[i].n_frame);
        }

        printf("|\n");
    }
}

void print_especific_table(tabla t, unsigned int index){
    printf("|A|R|M|P|C|FRAME|\n");
    printf("|%d|%d|%d|%d|%d|%u|\n",
        t[index].b_permiso,
        t[index].b_ref,
        t[index].b_mod,
        t[index].b_pres_aus,
        t[index].b_cache,
        t[index].n_frame);


}

void print_specific_table_binary(tabla t, unsigned int index, unsigned int size_marco){
    printf("|A|R|M|P|C|FRAME_BINARY|\n");
    printf("|%d|%d|%d|%d|%d",
        t[index].b_permiso,
        t[index].b_ref,
        t[index].b_mod,
        t[index].b_pres_aus,
        t[index].b_cache);
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

unsigned long int binary_especific_table(tabla t, unsigned int index, unsigned int marco_size, unsigned int page_size){
    unsigned long int binary = 0;
    unsigned long int size_bits = (unsigned int)log2(marco_size);
    unsigned long int frame_mask = (1UL << size_bits) - 1; // Create a mask with size_bits number of 1s

    /* printf("Size bits: %lu frame_mask: %lu\n", size_bits, frame_mask);
 */
    binary |= (t[index].b_permiso & 1UL) << 4;
    binary |= (t[index].b_ref & 1UL) << 3;
    binary |= (t[index].b_mod & 1UL) << 2;
    binary |= (t[index].b_pres_aus & 1UL) << 1;
    binary |= (t[index].b_cache & 1UL) << 0;
    binary <<= size_bits; // Shift the bits size bits

    binary |= (t[index].n_frame & frame_mask) << 0; // Set the remaining bits for n_frame


    return binary;
}
