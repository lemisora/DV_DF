#include "tabla_paginas.h"
#include "file_entries.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

bool table_generated = false;
bool table_loaded = false;

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

void printBinary(unsigned int num, int bits_to_print) {
    for (int i = bits_to_print - 1; i >= 0; i--) {
        if (i % 4 == 3 && i != bits_to_print - 1)
        {
            printf(" ");
        }
        
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void solicitaDatos(unsigned int* tam_pag, unsigned int* num_pag, unsigned int* num_marcos){
    printf("Ingrese el tamaño de página que desea: ");
    scanf("%u", tam_pag);

    printf("Ingrese la cantidad de páginas que desea: ");
    scanf("%u", num_pag);

    printf("Ingrese la cantidad de marcos que desea: ");
    scanf("%u", num_marcos);
}

void printMenu(){
    printf("\nEstado del programa: ");
    if(!table_generated){
        printf("Tabla de páginas sin generar\n\n");
    } else if(table_generated && !table_loaded){
        printf("Tabla generada, ¡cárgela para poder usarla!\n\n");
    } else if(table_generated && table_loaded){
        printf("Tabla cargada, puede usarla\n\n");
    }
    printf("1. Generar tabla de páginas\n");
    printf("2. Cargar tabla de páginas\n");
    printf("3. Imprimir tabla de páginas\n");
    printf("4. Traducir dirección virtual a física\n");
    printf("5. Imprimir entrada específica de tabla de páginas\n");
    printf("0. Salir\n");
    printf("Ingrese la opción que desea: ");
}

int main(int argc, char** argv){

    if(argc < 2){
        printf("Uso traductor <nombre_archivo.txt>\n");
        return (EXIT_FAILURE);
    }

    FILE* archivo = NULL;
    tabla page_table = NULL;
    char binaryString[33];

    unsigned int num_pag = 0;
    unsigned int num_marcos = 0;
    unsigned int tam_pag = 0;
    unsigned int bits_desp = 0;
    unsigned int DV = 0;
    unsigned int DF = 0;

    int opc;
    unsigned int opc_num_pag = 0;

    while(true){
        printMenu();
        scanf("%d", &opc);
        if(opc == 0){
            printf("Saliendo del programa\n");
            break;
        }else if(opc == 1){
            // la generacion de tabla si sirve uwu
            printf("------------ Generación de entradas ------------\n");
            solicitaDatos(&tam_pag, &num_pag, &num_marcos);
            archivo = fopen(argv[1], "w");
            if(archivo != NULL){
                generadorEntradas(archivo, tam_pag, num_pag, num_marcos);
                table_generated = true;
            } else {
                perror("Error al abrir el archivo en el que se guardarán las entradas generadas\n");
            }
        }else if(opc == 2){
            // La tabla no carga a la primera, se tiene que ejecutar dos veces esta funcion
            printf("------------ Carga de tabla ------------\n");
            archivo = fopen(argv[1], "r");
            if(archivo == NULL){
                perror("Error al abrir el archivo del que se cargará la tabla, posiblemente aún no se ha creado");
                continue;
            }
            if(init_table(archivo, &page_table, num_pag, &tam_pag, &num_pag, &num_marcos)){
                printf("Inténtelo nuevamente\n");
            } else {
                printf("Se ha cargado correctamente la tabla de páginas\n");
                table_loaded = true;
                table_generated = true;
            }
        }else if(opc == 3){
            printf("------------ Impresión de tabla ------------\n");
            print_table(page_table, num_pag);
        }else if(opc == 4){
            printf("------------ Traducción de direcciones ------------\n");
            if(!table_loaded){
                printf("¡Primero necesita cargar la tabla de páginas!\n");
                continue;
            } else {
                printf("Ingrese la dirección virtual: ");
                scanf("%32s", binaryString);
                DV = strtoul(binaryString, NULL, 2);
                printf("\nDirección virtual\nEn decimal: %u \nEn hexadecimal: 0x%X \nEn binario: ", DV, DV);
                printBinary(DV, (int) log2(tam_pag*num_marcos));
                bits_desp = (unsigned int) log2(tam_pag);
                DF = translateVD_PD(page_table, tam_pag, num_pag, num_marcos, bits_desp, DV);
                printf("\nDirección física\nEn decimal: %u \nEn hexadecimal: 0x%X \nEn binario: ", DF, DF);
                printBinary(DF, 32);
            }
        }
        else if(opc == 5){
            printf("------------ Imprimir una Pagina ------------\n");
            if(!table_loaded){
                printf("¡Primero necesita cargar la tabla de páginas!\n");
                continue;
            } else {
                printf("Ingrese el numero de pagina: ");
                scanf("%u", &opc_num_pag);
                if (opc_num_pag >= num_pag){
                    printf("Número de página inválido\n");
                    continue;
                }else
                {
                    print_specific_table_binary(page_table, opc_num_pag, num_marcos);
                    DV = binary_especific_table(page_table, opc_num_pag, num_marcos, tam_pag);
                    printf("\nDirección virtual\nEn decimal: %u \nEn hexadecimal: 0x%X \nEn binario: ", DV, DV);
                    printBinary(DV, (int) log2(num_marcos * pow(2, 5)));
                    bits_desp = (unsigned int) log2(tam_pag*num_marcos);
                    DF = translateVD_PD(page_table, tam_pag, num_pag, num_marcos, bits_desp, DV);
                    printf("\nDirección física\nEn decimal: %u \nEn hexadecimal: 0x%X \nEn binario: ", DF, DF);
                    printBinary(DF, num_pag);
                }
            }
        }else{
            printf("Opción inválida\n¡Inténtelo nuevamente!\n");
        }
    }

    if(page_table != NULL){
        printf("Liberando memoria\n");
        free(page_table);
    }
    return EXIT_SUCCESS;
}
