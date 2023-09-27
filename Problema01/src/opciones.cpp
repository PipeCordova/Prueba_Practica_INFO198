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


/* cuando se hace el primer fork se crean 2 procesos, el hijo es 0 y el otro != */
void mostrarMensaje (const string &usuario) {
    pid_t pid = fork(); // fork --> proceso hijo
    if (pid == 0){ // el proceso hijo es 0
        pid_t pidd = getpid(); // pid del proceso hijo
        cout << "HOLA, COMO ESTAS " << usuario << "!!, PID = " << pidd << endl;
        exit(0); // esto finaliza el proceso hijo
    } else {
        wait(NULL); // proceso padre espera hasta que se termine el proceso hijo
    }
}

/* El proceso padre espera a que el proceso hijo termine antes de continuar su ejecución, lo que garantiza 
que el vector/mensaje se ordene en el proceso hijo antes de que el proceso padre imprima el resultado.*/


void ordenarVector(vector<int>& vectorEntrada) {
    pid_t pid = fork();
    if (pid == 0) {
        pid_t pidd = getpid();
        sort(vectorEntrada.begin(),vectorEntrada.end());
        cout << "VECTOR ORDENADO: ";
        for (int u : vectorEntrada){
            cout << u << " ";
        }
        cout << ", PID = " << pidd << endl;
        exit(0);
    } else {
        wait(NULL);
    }
}