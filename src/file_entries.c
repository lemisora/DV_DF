#include "file_entries.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void leer_primera_linea(FILE* file, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    fscanf(file, "%*s %u %*s %u %*s %u", tam_pag, num_pag, num_marcos);
}

void leer(FILE* file, tabla* t, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    int b_permiso = 0;
    int b_ref = 0;
    int b_mod = 0;
    int b_pres_aus = 0;
    int b_cache = 0;

    unsigned int num = 0;
    unsigned int n_frame = 0;
    unsigned int desp = log2(*num_marcos);

    fscanf(file, "%*s %u %*s %u %*s %u", tam_pag, num_pag, num_marcos);

    for(int i = 0; i < size; i++){
        // fscanf(file, "%d %d %d %d %d %u", &b_permiso, &b_ref, &b_mod, &b_pres_aus, &b_cache, &n_frame);
        fscanf(file, "%u", &num);
        //num = (b_permiso << (desp+5)) | (b_ref << (desp+4)) | (b_mod << (desp+3)) | (b_pres_aus << (desp+2)) | (b_cache << (desp+1)) | n_frame;
        b_permiso = (num >> (desp+4)) & 1;
        b_ref = (num >> (desp+3)) & 1;
        b_mod = (num >> (desp+2)) & 1;
        b_pres_aus = (num >> (desp+1)) & 1;
        b_cache = (num >> (desp)) & 1;
        n_frame = num & desp;
        table_entry_t temp = {
                                   .b_permiso = b_permiso,
                                   .b_ref = b_ref,
                                   .b_mod = b_mod,
                                   .b_pres_aus = b_pres_aus,
                                   .b_cache = b_cache,
                                   .n_frame = n_frame
                             };
        add_entry(*t, temp, i);
    }
}

//Tamaño página, Cantidad de páginas, Cantidad marcos
void generadorEntradas(FILE* file, unsigned int tam_pag, unsigned int num_pag, unsigned int num_marcos){
    srand(time(NULL));
    int b_permiso, b_ref, b_mod, b_pres_aus, b_cache, n_frame;
    unsigned int num = 0;
    unsigned int desp = log2(num_marcos);
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "tam_pag: %u num_pag: %u num_marcos: %u", tam_pag, num_pag, num_marcos);
    fprintf(file, "%s\n", buffer);
    for(int i = 0; i < num_pag; i++){
        num = 0;
        b_permiso = rand() % 2;
        b_ref = rand() % 2;
        b_mod = rand() % 2;
        b_pres_aus = rand() % 2;
        b_cache = rand() % 2;
        n_frame = rand() % num_marcos;
        // fprintf(file, "%d %d %d %d %d %d\n", b_permiso, b_ref, b_mod, b_pres_aus, b_cache, n_frame);
        // num <<= b_permiso ; num &= b_permiso;
        // num <<= b_ref; num &= b_ref;
        // num <<= b_mod; num &= b_mod;
        // num <<= b_pres_aus; num &= b_pres_aus;
        // num <<= b_cache; num &= b_cache;
        // num <<= n_frame; num &= n_frame;
        num = (b_permiso << (desp+5)) | (b_ref << (desp+4)) | (b_mod << (desp+3)) | (b_pres_aus << (desp+2)) | (b_cache << (desp+1)) | n_frame;
        fprintf(file, "%d\n", num);
    }
    fclose(file);
}
