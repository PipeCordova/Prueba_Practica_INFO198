#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void listaArchivos(const string& direccion, vector<string>& archivosOut);
void imprimirVector(const vector<string>& vec);
void indexa(const string& pathOut, const string& fileName, unordered_map<string, vector<pair<string, int>>>& indiceInvertido);
void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido);
void escribirHash(const unordered_map<string, vector<pair<string, int>>> indiceInvertido, const string& idxFile);

#endif