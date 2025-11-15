#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "memory_manager.h" 

//Algoritmos de asignacion de memoria

memory_block_t * best_fit (memory_block_t* head, size_t size);
memory_block_t * first_fit (memory_block_t* head, size_t size);
memory_block_t * worst_fit (memory_block_t* head, size_t size);

#endif