#ifndef FUNCIONESBACKEND
#define FUNCIONESBACKEND_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Mensaje{
    string origen;
    string destino;
    string txtToSearch;
    vector<pair<string, int>> data;
};


// Funciones para transformar el idx en un hash, y para buscar palabras (un vector de palabras) dentro del hash
void obtenerPalabras(const string &frase, vector<string> &palabras);
void buscarEnIdx(const vector<string> &palabras, int topk, unordered_map<string, vector<pair<string, int>>>& indiceInvertido, Mensaje &msg);
void verificarCantidad (unordered_map<string, int>& interseccion, const int &cantPalabras, vector<string>& textosAceptados);
void crearHash (unordered_map<string, vector<pair<string, int>>>& indiceInvertido, const string& idxFile);
void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido);

#endif 