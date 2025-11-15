#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    printf("SIMULADOR DE MEMORIA\n");
    
    if (argc != 2) {
        printf("Uso: %s <archivo_entrada>\n", argv[0]);
        printf("Ejemplo: %s test/input.txt\n", argv[0]);
        return 1;
    }
    
    init_memory_manager(1024);
    process_input_file(argv[1]);
    
    printf("Simulacion completada\n");
    return 0;
}