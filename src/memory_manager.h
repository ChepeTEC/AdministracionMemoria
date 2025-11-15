#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

//Es el nodo de nuestra lista doblemente enlazada
typedef struct memory_block {

    size_t size;
    int is_free;
    char var_name [32];

    //Puntero delantero
    struct memory_block* next;
    struct memory_block* previous;

} memory_block_t;

typedef enum {
    FIRST_FIT = 0,
    BEST_FIT = 1,
    WORST_FIT = 2
} allocation_algorithm_t;



void init_memory_manager (size_t total_size); //Inicializar el modulo de memoria
void set_allocation_algorithm (int algorithm); //Setear "globalmente" el algoritmo a usar

void* allocate_memory (const char* var_name, size_t size); //ALLOC
void free_memory (const char* var_name); //FREE
void* reallocate_memory (const char* var_name, size_t new_size); //REALLOC
void  print_memory_state (); //PRINT

#endif
