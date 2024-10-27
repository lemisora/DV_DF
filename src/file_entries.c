#include "file_entries.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void leer_primera_linea(FILE* file, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    fscanf(file, "%*s %u %*s %u %*s %u", tam_pag, num_pag, num_marcos);
}

void leer(FILE* file, tabla* t, unsigned int size, unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    int b_permiso = 0;
    int b_ref = 0;
    int b_mod = 0;
    int b_pres_aus = 0;
    int b_cache = 0;
    unsigned int n_frame = 0;

    fscanf(file, "%*s %u %*s %u %*s %u", tam_pag, num_pag, num_marcos);

    for(int i = 0; i < size; i++){
        fscanf(file, "%d %d %d %d %d %u", &b_permiso, &b_ref, &b_mod, &b_pres_aus, &b_cache, &n_frame);
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
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "tam_pag: %u num_pag: %u num_marcos: %u", tam_pag, num_pag, num_marcos);
    fprintf(file, "%s\n", buffer);
    for(int i = 0; i < num_pag; i++){
        b_permiso = rand() % 2;
        b_ref = rand() % 2;
        b_mod = rand() % 2;
        b_pres_aus = rand() % 2;
        b_cache = rand() % 2;
        n_frame = rand() % num_marcos;
        fprintf(file, "%d %d %d %d %d %d\n", b_permiso, b_ref, b_mod, b_pres_aus, b_cache, n_frame);
    }
    fclose(file);
}
