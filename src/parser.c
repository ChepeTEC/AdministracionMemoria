#include "parser.h"
#include "memory_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Lectura de archivo
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
        
        // Ignorar los comentarios
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }
        
        // Eliminar enter
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;
        
        printf("Línea %d: %s\n", line_num, line);
        
        // Parsear comandos
        char command[20];
        char var_name[32];
        size_t size;
        
        //Llamada de ALLOC
        if (sscanf(line, "ALLOC %s %zu", var_name, &size) == 2) { 
            printf("  -> Ejecutando ALLOC %s %zu\n", var_name, size);
            allocate_memory(var_name, size, FIRST_FIT);
        }
        //Llamada de FREE
        else if (sscanf(line, "FREE %s", var_name) == 1) {
            printf("  -> Ejecutando FREE %s\n", var_name);
            free_memory(var_name);
        }
        //Llamada de REALLOC
        else if (sscanf(line, "REALLOC %s %zu", var_name, &size) == 2) {
            printf("  -> Ejecutando REALLOC %s %zu\n", var_name, size);
            reallocate_memory(var_name, size);
        }
        //LLamada de PRINT
        else if (strcmp(line, "PRINT") == 0) {
            printf("  -> Ejecutando PRINT\n"); 
            print_memory_state();
        }
        else {
            printf("El comando ingresado no es valido, revise el documento\n");
        }
    }
    
    fclose(file);
    printf("\nArchivo procesado completamente\n");
}