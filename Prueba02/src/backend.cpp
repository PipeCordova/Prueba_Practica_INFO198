#include <iostream>
#include <cstring>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int startServer(int& invIndexSocket, sockaddr_in& invIndexAddr, sockaddr_in& memcacheAddr) {
    // Crear el socket del servidor
    invIndexSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (invIndexSocket == -1) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&invIndexAddr, 0, sizeof(invIndexAddr));
    invIndexAddr.sin_family = AF_INET;
    invIndexAddr.sin_port = htons(12346);
    invIndexAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket a la dirección del servidor
    if (bind(invIndexSocket, (struct sockaddr*)&invIndexAddr, sizeof(invIndexAddr)) == -1) {
        perror("Error al enlazar el socket");
        close(invIndexSocket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(invIndexSocket, 5) == -1) {
        perror("Error al escuchar");
        close(invIndexSocket);
        exit(EXIT_FAILURE);
    }
    cout << "Esperando conexiones entrantes..." << endl;
    return 1;
}


// imprime el hash, solo para ver que se creó bien
void imprimirHash(const unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
    for (const auto& entrada : indiceInvertido) {
        cout << "Clave: " << entrada.first << endl;
        
        for (const auto& par : entrada.second) {
            cout << "  Subclave: " << par.first << ", Valor: " << par.second << endl;
        }
    }
}

// Crea el hash a partir del idxFile 
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

// Verifica que textos tienen todas las palabras de la frase ingresada
void verificarCantidad (unordered_map<string, int>& interseccion, const int &cantPalabras, vector<string>& textosAceptados){
    for (const auto& elemento : interseccion){
        if(cantPalabras == elemento.second)  textosAceptados.push_back(elemento.first);
    }
}

// busca las palabras dentro del vector palabras en el hash del indice invertido
// muestra solo <topk> textos
void buscarEnIdx(const vector<string> &palabras, int topk, unordered_map<string, vector<pair<string, int>>>& indiceInvertido){
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

// a partir de una frase, guarda cada palabra dentro del vector "palabras"
void obtenerPalabras(const string &frase, vector<string> &palabras) {
    istringstream ss(frase);
    string palabra;

    while (ss >> palabra) {
        palabras.push_back(palabra);
    }
}

int main(int argc, char const *argv[]){
    // hay que hacer que se comunique con el cache.cpp
    // el cache debe traer un mensaje útil
    // AGREGAR VARIABLES DE ENTORNO AL FINAL
    string idxFile = getenv("INDICE_INVERTIDO");
    unordered_map<string, vector<pair<string, int>>> indiceInvertido;
    crearHash(indiceInvertido, idxFile);

    int topk = 5;
    vector<string> palabras;
    cout << "Ingrese una frase a buscar: ";
    string frase;
    getline(cin, frase);
    obtenerPalabras(frase, palabras);
    buscarEnIdx(palabras,topk,indiceInvertido);

}

// int main() {
//     int invIndexSocket, memcacheSocket;
//     struct sockaddr_in invIndexAddr, memcacheAddr;
//     socklen_t clientAddrLen = sizeof(memcacheAddr);

//     startServer(invIndexSocket, invIndexAddr, memcacheAddr);

//     while (true) {
//         // Aceptar la conexión entrante
//         memcacheSocket = accept(invIndexSocket, (struct sockaddr*)&memcacheAddr, &clientAddrLen);
//         if (memcacheSocket == -1) {
//             perror("Error al aceptar la conexión");
//             continue; // Continuar esperando conexiones
//         }

//         cout << "Cliente conectado" << endl;
//         char msg[1024];
//         bool success = true;

//         while (success) {
//             ssize_t msgRead = recv(memcacheSocket, msg, sizeof(msg), 0);
//             msg[msgRead] = '\0';
//             cout << "Mensaje recibido: " << msg << endl;
//             string responseMsg = "El mensaje recibido fue: " + string(msg);
//             send(memcacheSocket, responseMsg.c_str(), responseMsg.length(), 0);
//             close(memcacheSocket);
//             cout << "Cliente desconectado" << endl;
//             break; // Salir del bucle interior
//         }
//     }

//     // El servidor seguirá esperando nuevas conexiones sin terminar

//     return 0;
// }