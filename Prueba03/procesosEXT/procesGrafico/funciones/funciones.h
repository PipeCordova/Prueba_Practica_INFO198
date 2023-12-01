#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <regex> // para validar el formato de datos.gra

//#include <SFML/Graphics.hpp>

using namespace std;
namespace fs = filesystem;



// declaracion funciones
pair<bool, string> validarTitulo(const string& linea);
bool validarFormato(const string& linea);
pair<vector<int>, vector<int>> extraerValoresDesdeArchivo(const string& nombreArchivo);




#endif