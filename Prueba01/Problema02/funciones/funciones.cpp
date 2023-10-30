#include "funciones.h"
#include <iostream>
#include <dirent.h>         //directorios
#include <unordered_map>    //hash
#include <algorithm>        //sort
#include <fstream>          //leer archivos

void listaArchivos(const string& dir, vector<string>& archivos){
    string elem;
    DIR *directorio; //Tipo de Dato
    struct dirent * elemento;
    if(directorio = opendir(dir.c_str())){
        while(elemento = readdir(directorio)){
            elem = elemento -> d_name;
            if (elem.length() >= 4 && elem.substr(elem.length() - 4) == ".txt") archivos.push_back(elem);
        }
    }else cerr << "Error al abrir directorio " << dir << "\nEscribió mal la dirección o no existe!" << endl;
    closedir(directorio);
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
}