#include "algorithms.h"
#include <stdio.h>

//Algoritmo de first fit
//Recordar que va comparando el atributo con cada uno de los campos hasta encontrar 
//el primero donde quepa

memory_block_t * first_fit (memory_block_t* head, size_t size){

    printf ("First-Fit: Buscando %zu bytes...\n", size);
    memory_block_t * current = head;
    size_t required_total = size + sizeof (memory_block_t);

    while (current != NULL){ //Recorremos hasta que current no sea nulo
        if (current->is_free && current->size >= required_total){
            printf ("First-Fit: Se encontro el bloque @%p de %zu bytes\n", current, current->size);
            return current;
        }
        current = current->next;
    }

    printf ("First-Fit: No se encotro el espacio necesario\n");
    return NULL;
}

//Algoritmo de best fit
//Recordar que va comparando el atrivbuto con cada uno de los campos hasta encontrar
//aquel donde mejor quepa, es decir reducir lo maximo posible la cantidad de espacio en blanco
memory_block_t * best_fit (memory_block_t* head, size_t size){
    printf ("Best-Fit: Buscando %zu bytes...\n", size);
    memory_block_t * current = head;

    //Variable para ir guardando el mejor "hasta ahora"
    memory_block_t * best = NULL;
    size_t required_total = size + sizeof (memory_block_t);

    while (current != NULL){ //Recorremos hasta que current no sea nulo

        if (current->is_free && current->size >= required_total){
            if (best == NULL || current->size < best->size){
                best = current;
                printf ("Best-Fit: Se encontro el mejor candidato: @%p (%zu bytes)\n", best, best->size);

            }
        }
        current = current->next;
    }

    if (best != NULL){
        printf ("Best-Fit: Se selecciono @%p (%zu bytes)\n", best, best->size);
    }else{
        printf ("Best-Fit: No se encontro espacio\n");
    }
    return best;
}


//Algoritmo de worst fit
//Recordar que va comprando el atributo con cada uno de los campos hasta encontrar
//aquell donde peor quepa, es decir maximizar lo maximo posible la cantidad de espacio en blanco

memory_block_t * worst_fit (memory_block_t* head, size_t size){
    printf ("Worst-Fit: Buscando %zu bytes...\n", size);
    memory_block_t * current = head;
    memory_block_t * worst = NULL;

    size_t required_total = size + sizeof(memory_block_t);

    while (current != NULL){ //Recorremos hasta que current no sea nulo
        if (current->is_free && current->size >= required_total){
            if (worst == NULL || current->size > worst->size){ //Lo contrario a best fit
                worst = current;
                printf ("Worst-Fit: Se encontro el mejor candidato: @%p (%zu bytes)\n", worst, worst->size);
            }
        }
        current = current->next;
    }

    if (worst != NULL){
        printf ("Worst-Fit: Se selecciono @%p (%zu bytes)\n", worst, worst->size);
    }else{
        printf ("Worst-Fit: No se encontro espacio\n");
    }

    return worst;

}