#include "memory_manager.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Globales
static memory_block_t * head = NULL;
static void * memory_pool = NULL;
static size_t total_memory_size = 0;

//Funcion que se encarga en inicializar el manager de la memoria

void init_memory_manager (size_t total_size){

    print ("--Iniciando memoria con los %zu bytes--", total_size);

    //Reservamos
    memory_pool = malloc (total_size);
    total_memory_size = total_size;

    if (memory_pool == NULL){
        printf ("Error: No se le pudo asignar la memoria al OS\n");
        return;
    }

    //Inicializamos los datos del primer nodo
    head = (memory_block_t * )memory_pool;
    head->size = total_size - sizeof (memory_block_t);
    head->is_free = 1;
    strcpy (head->var_name, "");
    head->next = NULL;
    head->previous = NULL;

    print ("--Memoria inicializada correctamente--");

}

//Funcion para calcular la direccion de memoria del usuario
void * get_user_memory (memory_block_t* block){
    return (void*) ((char * )block + sizeof (memory_block_t));
}

