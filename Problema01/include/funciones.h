#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>  
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

bool algunParametroVacio(const string &param, const string &nombreParametro);
vector<int> convertirlo(const string& v);
bool usuarioExiste(const string& usuario, const string& contrasena, const string& nombreArchivo);

void mostrarMenu(ifstream& archivoMenu);

int obtenerEleccion();
void ejecutarOpcion(int eleccion, const vector<int>& vectorPemisos, const string& nombreArchivo, const string& usuario, vector<int>& vectorEntrada);

void agregarElementosBD(const string &ruta);
void mostrarMensaje (const string &usuario);
void ordenarVector(vector<int>& vectorEntrada);

#endif 