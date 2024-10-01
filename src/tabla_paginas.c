#include "tabla_paginas.h"
//#include <stdio.h>
#include <stdlib.h>

int add_entry(tabla table, table_entry_t entrada, int index){
    table[index] = entrada;
    return EXIT_SUCCESS;
}

// int init_table(tabla tabla_paginas, int size){
//     if((tabla_paginas = malloc(sizeof(tabla)*size))==NULL){
//         perror("No se pudo reservar memoria para la tabla de páginas");
//         return EXIT_FAILURE;
//     }
//     for(int i = 0; i < size; i++){
//         add_entry(tabla_paginas, NULL, i);
//     }
//     return EXIT_SUCCESS;
// }
