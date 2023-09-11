CC = g++
CFLAGS = -std=c++17 -O3
SOURCES = main02.cpp
#FUNCTIONS = funciones/menu.cpp 
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(FUNCTIONS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)