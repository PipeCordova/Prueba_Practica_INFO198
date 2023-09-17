# Prueba_Practica_INFO198

# Esto es para cargar la variable de entorno en problema01
set -o allexport
source config/.env
export

# Ejecución
make
./app -u "userName" -p "password" -v a,b,c...,z