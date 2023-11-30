#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>
#include <unordered_map> 

using namespace std;

void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido);
void crearHash (unordered_map<string, vector<pair<string, int>>>& indiceInvertido, const string& idxFile);
void obtenerPalabras(const string &frase, vector<string> &palabras);
void buscarEnIdx(const vector<string> &palabras, int topk, unordered_map<string, vector<pair<string, int>>>& indiceInvertido);

#endif