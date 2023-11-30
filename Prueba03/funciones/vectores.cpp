#include "vectores.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

vector<int> verificarOpValidas(const string& rango, const string& path){
    ifstream archivo;
    archivo.open(path);
    if(!archivo.is_open()){
        cerr << "No se pudo abrir el archivo perfiles.txt\n\n";
        exit(EXIT_FAILURE);
    }

    vector<int> permisos;
    string linea;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        string nivel;
        getline(ss,nivel,',');

        if(nivel == rango){
            string permiso;
            while(getline(ss,permiso,',')) permisos.push_back(stoi(permiso));
            break;
        }
    }
    archivo.close();
    return permisos;
}


vector<int> stringToVector(const string& cadena) {
    vector<int> numeros;
    stringstream ss(cadena);

    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        int num = stoi(substr);
        numeros.push_back(num);
    }
    return numeros;
}

int sumatoria(const vector<int>& vec){
    int s = 0;
    for(int i=0 ; i<vec.size() ; i++) s = s + vec[i];
    return s;
}

double promedio(const vector<int>& vec){
    double x = sumatoria(vec);
    return x/vec.size();
}


int moda(const vector<int>& numeros) {
    int moda = numeros[0];  // Valor inicial para la moda
    int maxFrecuencia = 0;  // Frecuencia máxima registrada

    for (int i = 0; i < numeros.size(); ++i) {
        int frecuencia = 1;  // Frecuencia actual del número
        for (int j = i + 1; j < numeros.size(); ++j) {
            if (numeros[i] == numeros[j]) {
                frecuencia++;
            }
        }

        if (frecuencia > maxFrecuencia) {
            maxFrecuencia = frecuencia;
            moda = numeros[i];
        }
    }
    return moda;
}