#include "../include/funciones.h"

int obtenerEleccion() {
    int eleccion;
    cout << "INGRESE OPCIÓN: ";
    cin >> eleccion;
    cout << endl;
    return eleccion;
}

void mostrarMenu(ifstream& archivoMenu){
    pid_t padrePID = getpid();
    cout << "SISTEMA 1 (PID = " << padrePID << ")" << endl;
    string linea;
    while (getline(archivoMenu, linea)) {
        cout << linea << endl; // aqui leemos el menu.txt
    }
}

void ejecutarOpcion(int eleccion, const vector<int>& vectorPermisos, const string& nombreArchivo, const string& usuario, string& vectorEntrada) {
    string comando;
    if (find(vectorPermisos.begin(), vectorPermisos.end(), eleccion) != vectorPermisos.end()) {
        switch (eleccion) {
            case 1:
                agregarElementosBD(nombreArchivo);
                break;
            case 2:
                comando = "./progs_externos/executable/mensaje " + usuario;
                // llamar a proceso externo
                system(comando.c_str());
                break;
            case 3:
                comando = "./progs_externos/executable/ordena " + vectorEntrada; 
                // llamar a proceso externo
                system(comando.c_str());
                break;
        }
    } else {
        cout << "No tiene permiso para escoger la opcion " << eleccion << endl << endl;
    }
}

