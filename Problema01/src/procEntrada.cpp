#include "../include/funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric> 

// Esta funcion valida que las entradas no sean vacias.
bool algunParametroVacio(const string &param, const string &nombreParametro) {
    if (param.empty()) {
        cerr << "El parámetro " << nombreParametro << " es OBLIGATORIO\n";
        return true;
    }
    return false;
}

void leerConfiguracion(string& rutaUsers) {
    ifstream envFile("config/.env");
    if (envFile.is_open()) {
        string linea;
        while (getline(envFile, linea)) {
            if (linea.find("DB_USERS=") == 0) {
                rutaUsers = linea.substr(9);
            }
        }
        envFile.close();
    } else {
        cerr << "No se pudo abrir el archivo de configuración (.env)" << endl;
    }
}


bool usuarioExiste(const string& usuario, const string& contraseña, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    
    // Verificar si la apertura del archivo falló
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return false;
    }
    
    string linea;
    while (getline(archivo, linea)) {
        size_t espacio = linea.find(' ');
        if (espacio != string::npos) {
            if (linea.substr(0, espacio) == usuario && linea.substr(espacio + 2) == contraseña) {
                archivo.close(); // Cerrar el archivo antes de salir
                return true;
            }
        }
    }
    
    archivo.close(); // Cerrar el archivo antes de salir
    return false;
}
