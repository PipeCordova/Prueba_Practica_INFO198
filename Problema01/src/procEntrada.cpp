#include "../include/funciones.h"

// Esta funcion valida que las entradas no sean vacias.
bool algunParametroVacio(const string &param, const string &nombreParametro) {
    if (param.empty()) {
        cerr << "El parámetro " << nombreParametro << " es OBLIGATORIO\n";
        return true;
    }
    return false;
}


vector<int> convertirlo(const string& v) {
    vector<int> vec;
    string token = "";
    for (char ch : v) {
        if (ch != ',') {
            token += ch;
        } else {
            vec.push_back(stoi(token));
            token = "";
        }
    }
    if (!token.empty()) {
        vec.push_back(stoi(token));
    }
    return vec;
}


bool usuarioExiste(const string& usuario, const string& contraseña, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(EXIT_FAILURE);
    }
    
    string linea;
    while (getline(archivo, linea)) {
        size_t igual = linea.find('=');
        if (igual != string::npos) {
            if (linea.substr(0, igual) == usuario && linea.substr(igual + 1) == contraseña) {
                archivo.close(); 
                return true;
            }
        }
    }

    archivo.close();
    return false;
}
