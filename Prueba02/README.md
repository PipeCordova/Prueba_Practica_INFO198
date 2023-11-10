# Prueba02_Practica_INFO198

# Cargar variables de entorno

Abrir 3 consolas diferentes en la carpeta src para cada programa.  

# Variables de entorno frontend.cpp

`export FROM=./searcher`  
`export TO=./memcache`  

# Variables de entorno cache.cpp

`export HOST=./memcache`  
`export FRONT=./searcher`  
`export BACK=./invertedIndex`  
`export MEMORY_SIZE=4`  

# Variables de entorno backend.cpp

`export FROM=./invertedIndex`  
`export TO=./searcher`  
`export FILE=./file.idx`  
`export TOPK=5`  
