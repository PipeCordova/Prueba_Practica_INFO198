#include "funciones.h"
#include <iostream>
#include <vector>
#include <unordered_map> 
#include <fstream> //manejo de archivos
#include <sstream> //sstring para separar strings
#include <algorithm> //sort
#include <chrono>

void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
    for (const auto& entrada : indiceInvertido) {
        cout << "Clave: " << entrada.first << endl;
        
        for (const auto& par : entrada.second) {
            cout << "  Subclave: " << par.first << ", Valor: " << par.second << endl;
        }
    }
}
void imprimirHash1(const unordered_map<string, int>& indiceInvertido){
    for (const auto& entrada : indiceInvertido) {
        cout << "Clave: " << entrada.first << endl;
        cout << "Valor: " << entrada.second << endl;
    }
}

void crearHash (unordered_map<string, vector<pair<string, int>>>& indiceInvertido, const string& idxFile){
    ifstream archivo(idxFile);
    if(!archivo.is_open()){
        cerr << "\n- El archivo '" << idxFile << "' no existe!\n\n";
        exit(EXIT_FAILURE);
    }
    string linea, pal, aux;
    int pos;

    while (getline(archivo, linea)) {
        // ecosistema:(texto16.txt;1);(texto17.txt;1);(texto19.txt;1);
        pos = linea.find(":");
        pal = linea.substr(0,pos);
        // pal es cada palabra, ecosistema
        linea = linea.substr(pos+1);
        vector<string> separados;
        stringstream ss(linea);
        string aux;
        while(getline(ss, aux, '(')){
            aux = aux.substr(0, aux.find(")"));
            if(!aux.empty()) separados.push_back(aux);
        }

        for (string &str : separados) {
            int n = str.find(";");
            string nombreTexto = str.substr(0,n);
            string asd = str.substr(n+1);
            int rep = stoi(str.substr(n+1));
            pair<string, int> res (nombreTexto,rep);
            indiceInvertido[pal].push_back(res);  
        }   
    } // termina la creacion del hash
}

void obtenerPalabras(const string &frase, vector<string> &palabras) {
    istringstream ss(frase);
    string palabra;

    while (ss >> palabra) {
        palabras.push_back(palabra);
    }
}

void verificarCantidad (unordered_map<string, int>& interseccion, const int &cantPalabras, vector<string>& textosAceptados){
    for (const auto& elemento : interseccion){
        if(cantPalabras == elemento.second)  textosAceptados.push_back(elemento.first);
    }
}

void buscarEnIdx(const vector<string> &palabras, int topk, unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
    auto start = chrono::high_resolution_clock::now();
    unordered_map<string, int> documentosContador; // texto01,sumRep
    unordered_map<string, int> interseccion;
    int cantPalabras = palabras.size();

    for (const auto &palabra : palabras){
        if(indiceInvertido.find(palabra) != indiceInvertido.end()){
            for (const auto &documento : indiceInvertido[palabra]){
                documentosContador[documento.first] += documento.second;
                interseccion[documento.first] += 1;
            }
        }
    }

    // Convertir hashmap en vector para ordernarlo
    vector<pair<string,int>> documentosOrdenados;
    for (const auto &elemento : documentosContador) documentosOrdenados.push_back(elemento);
    // ordenar el vector segun el int del pair
    sort(documentosOrdenados.begin(), documentosOrdenados.end(), [](const auto &a, const auto &b) { // Se implementa una funcion lambda para comparar el INT del par
        return a.second > b.second;
    }); // es la misma lógica que usé para ordenar el conteo de palabras (funciones/archivos.cpp)

    vector<string> textosAceptados;
    verificarCantidad(interseccion, cantPalabras, textosAceptados);

    auto end = chrono::high_resolution_clock::now();
    auto tiempo = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "\n- Respuesta (tiempo de ejecución = " << tiempo.count() << " nano segundos): \n";
    if (documentosContador.empty() || textosAceptados.empty()) cout << "0) Ninguna coincidencia encontrada!\n";
    

    int cont = 1;
    for (const auto &documento : documentosOrdenados){
        if(find(textosAceptados.begin(), textosAceptados.end(), documento.first) != textosAceptados.end()){
            cout << cont << ") " << documento.first << ", " << documento.second << endl;
            cont ++;
            if (cont > topk) break;
        }
    }
}