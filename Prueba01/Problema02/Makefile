CC = g++
CFLAGS = -std=c++17 -O3 -pthread
SOURCES = main02.cpp
FUNCTIONS = funciones/funciones.cpp 
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(FUNCTIONS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)