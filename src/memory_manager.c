#include "memory_manager.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Globales
static memory_block_t * head = NULL;
static void * memory_pool = NULL;
static size_t total_memory_size = 0;
static allocation_algorithm_t current_algorithm = FIRST_FIT;

//Funcion que se encarga en inicializar el manager de la memoria

void init_memory_manager (size_t total_size){

    printf ("--Iniciando memoria con los %zu bytes--", total_size);

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

    printf ("--Memoria inicializada correctamente--");

}

//Funcion para calcular la direccion de memoria del usuario
void * get_user_memory (memory_block_t* block){
    return (void*) ((char * )block + sizeof (memory_block_t));
}
//Funcion para setear y cambiar el algoritmo a usar
void set_allocation_algorithm(int algorithm) {
    current_algorithm = (allocation_algorithm_t)algorithm;
    
    const char* algo_name = "";
    switch(current_algorithm) {
        case FIRST_FIT: algo_name = "First-Fit"; break;
        case BEST_FIT: algo_name = "Best-Fit"; break;
        case WORST_FIT: algo_name = "Worst-Fit"; break;
        default: algo_name = "Desconocido"; break;
    }
    printf("Algoritmo cambiado a: %s (valor: %d)\n", algo_name, current_algorithm);
}


// ALLOC
void* allocate_memory(const char* var_name, size_t size) {
    printf("ALLOC: %s de %zu bytes\n", var_name, size);
    
    memory_block_t* block = NULL;
    
    printf("  [DEBUG] current_algorithm = %d\n", current_algorithm);
    switch ((allocation_algorithm_t)current_algorithm) {
        case FIRST_FIT:
            printf("  [DEBUG] Usando First-Fit\n");
            block = first_fit(head, size);
            break;
        case BEST_FIT:
            printf("  [DEBUG] Usando Best-Fit\n");
            block = best_fit(head, size);
            break;
        case WORST_FIT:
            printf("  [DEBUG] Usando Worst-Fit\n");
            block = worst_fit(head, size);
            break;
        default:
        printf("Error: Algoritmo desconocido (valor: %d)\n", current_algorithm);
        return NULL;
    }
    
    if (block == NULL) {
        printf("Error: No hay espacio para %s\n", var_name);
        return NULL;
    }
    
    
    // Calculamos si se puede dividir el bloque
    size_t required_space = size + sizeof(memory_block_t);
    size_t remaining_space = block->size - required_space;
    
    // Dividimos bloque si sobra espacio suficiente
    if (remaining_space > sizeof(memory_block_t)) {
        // Creamos nuevo bloque libre con el espacio sobrante
        memory_block_t* new_block = (memory_block_t*)((char*)block + required_space);
        new_block->size = remaining_space;
        new_block->is_free = 1;
        strcpy(new_block->var_name, "");
        
        // Enlazar nuevo bloque
        new_block->next = block->next;
        new_block->previous = block;
        
        if (block->next != NULL) {
            block->next->previous = new_block;
        }
        block->next = new_block;
        
        // Ajustar tamaño del bloque original
        block->size = size;
    }
    
    // Asignamos el bloque
    block->is_free = 0;
    strcpy(block->var_name, var_name);
    
    // Rellenamos memoria con nombre de variable (como pide el profesor)
    void* user_memory = get_user_memory(block);
    size_t name_len = strlen(var_name);
    
    for (size_t i = 0; i < size; i++) {
        ((char*)user_memory)[i] = var_name[i % name_len];
    }
    
    printf("Asignado: %s - %zu bytes\n", var_name, block->size);
    return user_memory;
}

// PRINT
void print_memory_state() {
    const char* algo_name = "";
    switch(current_algorithm) {
        case FIRST_FIT: algo_name = "First-Fit"; break;
        case BEST_FIT: algo_name = "Best-Fit"; break;
        case WORST_FIT: algo_name = "Worst-Fit"; break;
    }
    
    printf("\n--- ESTADO MEMORIA (%s) ---\n", algo_name);
    
    memory_block_t* current = head;
    int block_count = 0;
    size_t total_used = 0;
    size_t total_free = 0;
    
    while (current != NULL) {
        printf("Bloque %d: %zub | %s | %s\n", 
               ++block_count,
               current->size,
               current->is_free ? "LIBRE" : "OCUPADO",
               current->var_name[0] ? current->var_name : "-");
        
        if (current->is_free) {
            total_free += current->size;
        } else {
            total_used += current->size;
        }
        
        current = current->next;
    }
    
    printf("Total: %zub usados, %zub libres, %d bloques\n", 
           total_used, total_free, block_count);
    printf("----------------------\n\n");
}


//Auxiliar de FREE
// Función para unir bloques libres adyacentes
void coalesce_free_blocks() {
    memory_block_t* current = head;
    
    while (current != NULL && current->next != NULL) {
        if (current->is_free && current->next->is_free) {
            // Unir current con current->next
            current->size += sizeof(memory_block_t) + current->next->size;
            current->next = current->next->next;
            if (current->next != NULL) {
                current->next->previous = current;
            }
        } else {
            current = current->next;
        }
    }
}

// FREE
void free_memory(const char* var_name) {
    printf("FREE: %s\n", var_name);
    
    memory_block_t* current = head;
    
    while (current != NULL) {
        if (!current->is_free && strcmp(current->var_name, var_name) == 0) {
            current->is_free = 1;
            strcpy(current->var_name, "");
            printf("Liberado: %s\n", var_name);
            
            // Unir bloques libres adyacentes
            coalesce_free_blocks();
            return;
        }
        current = current->next;
    }
    
    printf("Error: Variable %s no encontrada\n", var_name);
}

// REALLOC
void* reallocate_memory(const char* var_name, size_t new_size) {
    printf("REALLOC: %s a %zu bytes\n", var_name, new_size);
    
    // Buscar el bloque actual
    memory_block_t* current = head;
    while (current != NULL) {
        if (!current->is_free && strcmp(current->var_name, var_name) == 0) {
            break;
        }
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Variable %s no existe\n", var_name);
        return NULL;
    }
    
    // Si el nuevo tamaño cabe en el bloque actual
    if (new_size <= current->size) {
        // Podemos mantenerlo en el mismo sitio
        void* user_memory = get_user_memory(current);
        
        // Rellenar con el nombre (como pide el profesor)
        size_t name_len = strlen(var_name);
        for (size_t i = 0; i < new_size; i++) {
            ((char*)user_memory)[i] = var_name[i % name_len];
        }
        
        printf("REALLOC: %s ajustado a %zu bytes (misma ubicacion)\n", var_name, new_size);
        return user_memory;
    }
    
    // Si no cabe, buscar nuevo espacio
    free_memory(var_name);
    void* new_memory = allocate_memory(var_name, new_size);
    
    if (new_memory != NULL) {
        printf("REALLOC exitoso: %s movido a %zu bytes\n", var_name, new_size);
    } else {
        printf("REALLOC fallo: No hay espacio para %s\n", var_name);
    }
    
    return new_memory;
}