all: app

app: src/main.cpp src/procEntrada.cpp src/interaccion.cpp src/opciones.cpp
	g++ -fopenmp src/main.cpp src/procEntrada.cpp src/interaccion.cpp src/opciones.cpp -o app

clean:
	rm -f app
