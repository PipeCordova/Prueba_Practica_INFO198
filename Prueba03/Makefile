CC = g++
CFLAGS = -std=c++17 -O3
SOURCES = Trabajo.cpp
FUNCTIONS = funciones/menu.cpp funciones/archivos.cpp funciones/vectores.cpp
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(FUNCTIONS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)

cleand:
	rm -r carpetaBase dirBase