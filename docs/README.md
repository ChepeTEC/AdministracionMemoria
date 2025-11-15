# Simulador de Gestión de Memoria - PSO TC3

## Descripción
Programa en C que simula la gestión dinámica de memoria implementando los algoritmos **First-fit**, **Best-fit** y **Worst-fit**. Desarrollado como tarea para el curso Principios de Sistemas Operativos.

## Características
- Simula `malloc`, `realloc` y `free`
- Implementa los 3 algoritmos de asignación de memoria
- Demuestra fragmentación de memoria
- Simula fugas de memoria
- Lee operaciones desde archivo de entrada

## Estructura del Proyecto
AdministracionMemoria/
├── src/
│ ├── main.c # Programa principal
│ ├── memory_manager.h # Definiciones y estructuras
│ ├── memory_manager.c # Gestión de memoria
│ ├── algorithms.h # Algoritmos de asignación
│ ├── algorithms.c # Implementación algoritmos
│ ├── parser.h # Parser de archivos
│ └── parser.c # Implementación parser
├── test/
│ ├── demo_completo.txt # Demostración completa
│ └── debug_first_fit.txt # Prueba específica
├── bin/ # Ejecutable (generado)
|__ docs/ #Documentación general del proyecto
└── Makefile # Compilación automática

## Compilación
make clean

make


## Ejecución
./bin/memory_simulator <archivo_entrada>

Ejemplo: ./bin/memory_simulator test/demo_completo.txt

## Formatos de comando

- ALLOC <variable> <tamaño> - Asigna memoria
- FREE <variable> - Libera memoria
- REALLOC <variable> <nuevo_tamaño> - Reasigna memoria
- SET_ALGORITHM <FIRST_FIT|BEST_FIT|WORST_FIT> - Selecciona algoritmo
- PRINT - Muestra estado de memoria
- # comentario - Líneas comentadas

## Algoritmos implementados
- First-Fit: Asigna en el primer bloque libre que encuentre
- Best-Fit: Asigna en el bloque que mejor se ajuste al tamaño
- Worst-Fit: Asigna en el bloque libre más grande disponible

## Demostraciones importantes
- Fragmentación: El espacio libre no contiguo que impide asignaciones grandes
- Fugas de memoria: Memoria asignada que nunca se libera

