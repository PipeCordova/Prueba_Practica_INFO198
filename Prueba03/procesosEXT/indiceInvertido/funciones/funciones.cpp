#include "funciones.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <dirent.h>         //directorios

void listaArchivos(const string& direccion, vector<string>& archivosOut){
    string elem;
    DIR *directorio; //Tipo de Dato
    struct dirent * elemento;
    if(directorio = opendir(direccion.c_str())){
        while(elemento = readdir(directorio)){
            elem = elemento -> d_name;
            if (elem.length() >= 4 && elem.substr(elem.length() - 4) == ".txt") archivosOut.push_back(elem);
        }
    }else cerr << "\n- Error al abrir directorio " << direccion << "\nEscribió mal la dirección o no existe!" << endl;
    closedir(directorio);

    if(archivosOut.size() == 0){
        cerr << "\n- No hay archivos en la direccion '" << direccion << "'\n\n";
        exit(EXIT_FAILURE);
    }
}

void imprimirVector(const vector<string>& vec) {
    for (string elemento : vec) {
        cout << elemento << " / ";
    }
    cout << endl;
}

void indexa(const string& pathOut, const string& fileName, unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
    string pathFile = pathOut + "/"+ fileName;
    //cout << pathFile << endl;
    ifstream archivo(pathFile);
    if(!archivo.is_open()){
        cerr << "\n- Error al abrir archivo '" << pathFile << "'\n\n";
        exit(EXIT_FAILURE);
    }

    string linea, pal;
    int n, pos;
    // cada linea tiene la forma palabra; int
    while(getline(archivo,linea)){
        pos = linea.find(";");
        pal = linea.substr(0,pos);
        n = stoi(linea.substr(pos+1));
        pair<string, int> res (fileName,n);

        indiceInvertido[pal].push_back(res);
    }
    //cout << "- Creacion exitosa para el archivo "<< fileName << endl;
}

void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
    for (const auto& entrada : indiceInvertido) {
        cout << "Clave: " << entrada.first << endl;
        
        for (const auto& par : entrada.second) {
            cout << "  Subclave: " << par.first << ", Valor: " << par.second << endl;
        }
    }
}

void escribirHash(const unordered_map<string, vector<pair<string, int>>> indiceInvertido, const string& idxFile){
    ofstream archivoSalida(idxFile);

    if (!archivoSalida.is_open()) {
        cerr << "No se pudo abrir el archivo " << idxFile << endl;
        exit(EXIT_FAILURE);
    }

    for (const auto& entrada : indiceInvertido) {
        archivoSalida << entrada.first << ":";
        for (const auto& par : entrada.second) archivoSalida << "(" << par.first << ";" << par.second << ");";
        archivoSalida << endl;
    }
}