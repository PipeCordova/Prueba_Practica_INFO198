all: app

app: src/main.cpp src/procEntrada.cpp
	g++ -fopenmp src/main.cpp src/procEntrada.cpp -o app

clean:
	rm -f app
