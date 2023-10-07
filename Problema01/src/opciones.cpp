#include "../include/funciones.h"

void agregarElementosBD(const string &ruta) {
    ofstream archivo(ruta, ios::app);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }
    string nuevoElemento;
    cin.ignore(); // Limpiar el buffer antes de getline
    cout << "Ingrese nuevo userName y pass (userName=Password): ";
    getline(cin, nuevoElemento);
    archivo << nuevoElemento << endl;
    cout << "Agregado!!\n" << endl;
    archivo.close();
}
