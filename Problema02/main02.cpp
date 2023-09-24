#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "funciones/funciones.h"

using namespace std;

void miFuncion(int id) {
    cout << "Hilo " << id << " ejecutando" << endl;
}

int main(int argc, char* argv[]){
    string ext = getenv("EXTENSION"); 
    string rutaIn = getenv("PATH_FILES_IN");
    string rutaOut = getenv("PATH_FILES_OUT");
    int nThreads = stoi(getenv("AMOUNT_THREADS"));

    mutex mtx;    
    
    vector<string> archivos;
    listaArchivos(rutaIn, archivos);

    int archivosPorThread = archivos.size() / nThreads;
    vector<thread> hilos;
    for (int i = 0; i < nThreads; ++i) {
        // Define el rango de archivos para este hilo
        int inicio = i * archivosPorThread;
        int fin;
        if (i == (nThreads - 1)) {
            fin = archivos.size(); // El último hilo procesa todos los archivos restantes
        } else {
            fin = (i + 1) * archivosPorThread; // Los hilos anteriores procesan un rango específico de archivos
        }

        // Crea un hilo para procesar el grupo de archivos
        thread hilo([inicio, fin, i, rutaIn, rutaOut, archivos, &mtx]() {
            for (int j = inicio; j < fin; ++j) {
                cuentaPalabras(rutaIn + "/" + archivos[j], rutaOut + "/" + archivos[j]);
                mtx.lock();
                cout << "archivo " << rutaIn + "/" + archivos[j] << ", procesado por el thread " << i << endl;
                mtx.unlock();
            }
        });

        // Agrega el hilo al vector de hilos
        hilos.push_back(move(hilo));
    }
    // Espera a que todos los hilos terminen
    for (thread& hilo : hilos) {
        hilo.join();
    }

    cout << "Todos los hilos han terminado." << endl;
    
    
}