CC = g++
CFLAGS = -std=c++17 -O3
SOURCES = main03.cpp
FUNCTIONS = funciones/funciones.cpp 
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(FUNCTIONS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)