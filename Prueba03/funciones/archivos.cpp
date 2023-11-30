#include "archivos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool archivoExiste(const string& path) {
    ifstream archivo(path.c_str());
    return archivo.good();
}

void crearArchivo(const string& path) {
    ofstream archivo(path);

    if (archivo.is_open()) {
        archivo.close();
        cout << "- Archivo '" << path << "' creado exitosamente! \n\n";
    } else {
        cerr << "- No se pudo crear el archivo '" << path <<"'\n- Tu ruta puede no existir! \n\n";
    }
}

void agregarAlArchivo(const string& f, const string& nuevaLinea){
    ofstream archivo(f, ios::app);  // Abre el archivo en modo añadir
    if (archivo.is_open()) {
        archivo << nuevaLinea << "\n";
        archivo.close();
        cout << "- Nueva linea agregada a '" << f << "' correctamente!!\n\n";
    } else {
        cerr << "- Error al abrir el archivo '" << f <<"'\n\n";
    }
}

string obtenerRango(const string& u, const string& path){
    ifstream archivo;
    string linea, aux;
    archivo.open(path);

    if(!archivo.is_open()) cerr << "- Base de datos '" << path << "' NO encontrada\n\n";

    while (getline(archivo, linea, ';')) {
        vector<string> fila;
        istringstream ss(linea);
        while (getline(ss, aux, ',')) {
            fila.push_back(aux);
        }
        if (fila[0] == u) {
            archivo.close();
            return fila[1];
        }
    }
    archivo.close();
    cerr << "\n- Usuario '" << u << "' NO registrado!\n\n";
    exit(EXIT_FAILURE);
}

// Función para limpiar una palabra de caracteres no alfabéticos
string limpiarPalabra(const string &palabra) {
    string limpia = "";
    for (char c : palabra) {
        if (isalpha(c)) { // isalpha retorna True cuando el char 'c' es del alfabeto
            limpia += tolower(c);
        }
    }
    return limpia;
}

void cuentaPalabras(const string &i, const string &o) {
    ifstream input(i);
    if (!input) {
        cerr << "- Error al abrir el archivo de entrada '" << i << "'\n\n";
        return;
    }

    // Aregar que verifique que el archivo de texto pesa mas de un MB (Opcional)

    unordered_map<string, int> contadorPalabras; // Hash para contar las palabras
    string palabra;
    while (input >> palabra) { // se va leyendo palabra a palabra desde el input y se guarda en 'palabra'
        palabra = limpiarPalabra(palabra);
        if (!palabra.empty()) {
            contadorPalabras[palabra]++;
        }
    }
    input.close();
    ofstream output(o);
    if (!output) {
        cerr << "- Error al crear el archivo de salida '" << o << "'\n\n";
        return;
    }
    // Ordenar las palabras según su cantidad de repeticiones
    // Transferir los elementos del unordered_map a un vector de pares (clave, valor)
    vector<pair<string, int>> elementos(contadorPalabras.begin(), contadorPalabras.end());

    // Ordenar el vector en función del valor (int) en orden descendente
    sort(elementos.begin(), elementos.end(), [](const auto &a, const auto &b) { // Se implementa una funcion lambda para comparar el INT del par
        return a.second > b.second;
    });

    for (const auto &pair : elementos) {
        output << pair.first << "; " << pair.second << endl;
    }
    output.close();
    cout << "- Conteo de palabras completado y guardado en el archivo '" << o << "'\n\n";
}

// Sobrecarga de funciones (Funciones usadas solamente para comprobar que la creacion de vectores este bien hecha)
void imprimirVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}
void imprimirVector(const vector<string>& vec) {
    for (string elemento : vec) {
        cout << elemento << " ";
    }
    cout << endl;
}
