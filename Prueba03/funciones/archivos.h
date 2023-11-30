#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <string>
#include <vector>

using namespace std;

bool archivoExiste(const string& path);
void crearArchivo(const string& path);
void agregarAlArchivo(const string& f, const string& nuevaLinea);
string obtenerRango(const string& u, const string& path);
void cuentaPalabras(const string &i, const string &o);
// Funciones situacionales
void imprimirVector(const vector<int>& vec);
void imprimirVector(const vector<string>& vec);

#endif