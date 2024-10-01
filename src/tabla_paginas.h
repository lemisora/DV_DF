#include <stdlib.h>
#ifndef TABLA_H
#define TABLA_H

typedef struct entrada table_entry_t;
typedef table_entry_t* tabla;

struct entrada{
    int b_permiso;  //Permiso de lectura/escritura, 0 solo lectura, 1 lectura/escritura
    int b_ref;      //0 no accedida recientemente, 1 accedida recientemente
    int b_mod;      //0 no modificada, 1 modificada
    int b_pres_aus; //0 no está en memoria principal, 1 está en memoria principal
    int b_cache;    //0 cache habilitado, 1 caché inhabilitado
    int n_frame;
};

int add_entry(tabla table, table_entry_t entrada, int index); //Función para añadir entradas a la tablaa
int init_table(int size);   //Función para inicializar la tabla
int translateVD_PD();   //Función para traducir memoria virtual a física

#endif
