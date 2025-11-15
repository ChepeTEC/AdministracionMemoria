#include "parser.h"
#include "memory_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Lectura de archivo
void process_input_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo: %s\n", filename);
        return;
    }

    char line[256];
    int line_num = 0;

    printf("Leyendo archivo: %s\n", filename);

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Ignorar comentarios y lineas vacias
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }
        
        // Eliminar salto de linea
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;
        
        printf("Linea %d: %s\n", line_num, line);
        
        // Parsear comandos
        char var_name[32];
        size_t size;
        
        // Comando ALLOC
        if (sscanf(line, "ALLOC %s %zu", var_name, &size) == 2) { 
            printf("  -> Ejecutando ALLOC %s %zu\n", var_name, size);
            allocate_memory(var_name, size);
        }
        // Comando FREE
        else if (sscanf(line, "FREE %s", var_name) == 1) {
            printf("  -> Ejecutando FREE %s\n", var_name);
            free_memory(var_name);
        }
        // Comando REALLOC
        else if (sscanf(line, "REALLOC %s %zu", var_name, &size) == 2) {
            printf("  -> Ejecutando REALLOC %s %zu\n", var_name, size);
            reallocate_memory(var_name, size);
        }
        // Comando SET_ALGORITHM
        else if (sscanf(line, "SET_ALGORITHM %s", var_name) == 1) {
            printf("  -> Ejecutando SET_ALGORITHM %s\n", var_name);
            if (strcmp(var_name, "FIRST_FIT") == 0) {
                set_allocation_algorithm(FIRST_FIT);
            } else if (strcmp(var_name, "BEST_FIT") == 0) {
                set_allocation_algorithm(BEST_FIT);
            } else if (strcmp(var_name, "WORST_FIT") == 0) {
                set_allocation_algorithm(WORST_FIT);
            } else {
                printf("Error: Algoritmo desconocido: %s\n", var_name);
            }
        }
        // Comando PRINT
        else if (strcmp(line, "PRINT") == 0) {
            printf("  -> Ejecutando PRINT\n"); 
            print_memory_state();
        }
        else {
            printf("Error: Comando no reconocido\n");
            printf("Comandos válidos: ALLOC, FREE, REALLOC, PRINT, SET_ALGORITHM\n");
        }
    }
    
    fclose(file);
    printf("\nArchivo procesado completamente\n");
}