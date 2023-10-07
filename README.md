# Prueba_Practica_INFO198

# Variables de entorno Problema 01
- `set -o allexport`  
- `source config/.env`
- `export`  

# Ejecución Problema 01
- `make`
- `./app -u "userName" -p "password" -v "a b c z"`

# Variables de entorno Problema 02
Para poder ejecutar el codigo es necesario exportar las variables de entorno que se mencionan a continuacion:
- `export EXTENSION=txt`
- `export PATH_FILES_IN=files/in`
- `export PATH_FILES_OUT=files/out`
- `export AMOUNT_THREADS=4` Aqui debe poner con cuantos threads desea ejecutar el codigo

# Ejecución Problema 02
- `make`
- `./app`
