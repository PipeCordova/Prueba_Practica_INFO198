# Descripción
- Este programa en C++ procesa archivos de texto y cuenta las palabras contenidas en ellos de manera eficiente mediante el uso de hilos (threads). El código se encarga de dividir la tarea de procesamiento en múltiples hilos, lo que permite una mayor velocidad de procesamiento.

# Compilación
- Se propociona un Makefile, por lo tanto, solo debe ejecutar make en la consola.

# Ejecución
- Luego de haber hecho make, el programa se ejecuta de la siguente manera:
    - `./app EXTENSION PATH_FILES_IN PATH_FILES_OUT AMOUNT_THREADS`
    - Donde:
        - `EXTENSION` es el tipo de archivos que se quiere leer (.txt, .csv, etc)
        - `PATH_FILES_IN` es la ruta de la carpeta donde se encuentran los archivos de entrada
        - `PATH_FILES_OUT` es la ruta de la carpeta donde se guardaran los archivos de salida (archivos de conteo de palabras)
        - `AMOUNT_THREADS` es la cantidad de threads que desea utilizar
- Un ejemplo de ejecución es:
    - `./app ".txt" "files/in" "files/out" 4`

# Funciones
- Dentro de la carpeta **funciones** hay un archivo en formato `.cpp` y su respectivo header `.h`.
- En este archivo residen todas las funciones esenciales que han sido creadas manualmente y resultan indispensables para asegurar la correcta ejecución del código `main02.cpp`.
