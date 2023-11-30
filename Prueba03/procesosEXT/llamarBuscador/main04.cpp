#include <iostream>
#include <vector>
#include <unordered_map> 
#include <cctype> //toupper
#include <unistd.h> //getpid
#include "funciones/funciones.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr << "- El programa debe ejuctarse como ./app INVERTED_INDEX_FILE TOPK\n";
        exit(EXIT_FAILURE);
    }
    string idxFile = argv[1];
    int topk = stoi(argv[2]);

    // Crear hashmap de file.idx
    unordered_map<string, vector<pair<string, int>>> indiceInvertido;
    crearHash(indiceInvertido, idxFile);
    //imprimirHash(indiceInvertido);

    bool flg = true;
    char flg1;
    vector<string> palabras;
    while (flg){
        int clearResult = system("clear");
        cout << "### Buscador de indice invertido (pid = "<< getpid() << ") ###\n\n";
        cout << "- Los topk documentos serán = " << topk << "\n";
        cout << "- Escriba texto a buscar: ";
        string frase;
        getline(cin, frase);
        obtenerPalabras(frase, palabras);
        //for (string x : palabras) cout << x << endl;
        buscarEnIdx(palabras,topk,indiceInvertido);
        cout << "\n- Desea Salir? (S/N): ";
        cin >> flg1;
        flg1 = toupper(flg1);
        if(flg1 == 'S') flg = false;
        else {
            cin.ignore(); // para que funcione el getline(cin,frase) todo el rato
            frase.clear();
            palabras.clear();
        }
    }
}