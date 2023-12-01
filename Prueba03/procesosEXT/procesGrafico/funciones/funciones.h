#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cctype>  // Necesario para la función isdigit

#include <GL/glut.h>


//#include <SFML/Graphics.hpp>

using namespace std;
namespace fs = filesystem;


// declaracion funciones
pair<bool, string> validarPrimeraLinea(const string& archivo);
bool validarFormato(const string& linea);
bool validarArchivo(const string& nombreArchivo);




#endif