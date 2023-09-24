# Prueba_Practica_INFO198

# Problema 01
# Variables de entorno
set -o allexport  
source config/.env  
export  

# Ejecución
- `make`
- `./app -u "userName" -p "password" -v a,b,c...,z`

# Problema 02
# Variables de entorno
Para poder ejecutar el codigo es necesario exportar las variables de entorno que se mencionan a continuacion:
- `export EXTENSION=txt`
- `export PATH_FILES_IN=files/in`
- `export PATH_FILES_OUT=files/out`
- `export AMOUNT_THREADS=4` Aqui debe poner con cuantos threads desea ejecutar el codigo

# Ejecución 
- `make`
- `./app`
