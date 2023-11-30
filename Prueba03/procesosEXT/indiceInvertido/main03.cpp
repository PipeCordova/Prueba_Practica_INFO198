#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <unordered_map>
#include "funciones/funciones.h"

using namespace std;

int main(int argc, char* argv[]){
    string idxFile = argv[1];
    string pathOut = argv[2];
    
    vector<string> archivosOut;
    listaArchivos(pathOut, archivosOut);

    // palabra:(file01.txt;3)
    unordered_map<string, vector<pair<string, int>> > indiceInvertido;

    for (int i = 0 ; i < archivosOut.size() ; i++){
        indexa(pathOut, archivosOut[i], indiceInvertido);
    }
    //cout << endl;

    //imprimirHash(indiceInvertido);
    escribirHash(indiceInvertido, idxFile);

    cout << "- El proceso externo pid = " << getpid() << " generó el archivo '" << idxFile << "'\n\n";
}

