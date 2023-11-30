# Descripción
- El programa en C++ crea un índice invertido a partir de archivos de texto almacenados en un directorio especificado. Un índice invertido es una estructura de datos que mapea palabras a los archivos en los que aparecen junto con sus frecuencias de aparición. Este programa procesa todos los archivos en el directorio de entrada y genera un índice invertido que se almacena en un archivo de índice (.idx).

# Compilación
- Se propociona un Makefile, por lo tanto, solo debe ejecutar make en la consola.

# Ejecución
- Luego de haber hecho make, el programa se ejecuta de la siguente manera:
    - `./app INVERTED_INDEX_FILE PATH_FILES_OUT`
    - Donde:
        - `INVERTED_INDEX_FILE` es la ruta del archivo de salida .idx
        - `PATH_FILES_OUT` es la ruta donde se encuentran los archivos de entrada para este código. Se llama PATH_FILES_OUT ya que son los archivos de salida de otro codigo que hay dentro del repositorio.
- Un ejemplo de ejecución es:
    - `./app "files/file.idx" "files/out"`

# Funciones
- Dentro de la carpeta **funciones** hay un archivo en formato `.cpp` y su respectivo header `.h`.
- En este archivo residen todas las funciones esenciales que han sido creadas manualmente y resultan indispensables para asegurar la correcta ejecución del código `main03.cpp`.