#include <iostream>
#include <cstdlib>  // exit
#include <vector>
#include <thread>
#include <unistd.h>
#include <mutex>    // biblioteca para utilizar objetos mutex, que se utilizan para sincronizar el acceso a datos compartidos entre hilos.
#include "funciones/funciones.h"

using namespace std;

int main(int argc, char* argv[]){
    string ext = argv[1]; 
    string rutaIn = argv[2];
    string rutaOut = argv[3];
    int nThreads = stoi(argv[4]);

    if(nThreads <= 0 || nThreads > 10){
        cerr << "\n- Numero de threads invalido!\n- nThreads debe ser mayor o igual a 1 y menor o igual que 10!\n- nThreads actual = " << nThreads << "\n\n";
        exit(EXIT_FAILURE);
    }
    if(rutaIn == rutaOut){
        cerr << "\n- PATH_FILES_IN y PATH_FILES_OUT no pueden ser iguales!!!\n- Debe modificar variable de entorno\n";
        exit(EXIT_FAILURE);
    }

    //Los mutex se utilizan para asegurarse de que solo un hilo pueda acceder 
    //a ciertas secciones críticas del código a la vez. En este caso, se utilizará 
    //para proteger la salida en la consola para evitar la mezcla de mensajes entre hilos concurrentes.
    mutex mtx;    
    
    vector<string> archivos;
    listaArchivos(rutaIn, ext, archivos);

    if(archivos.size() < 20){
        cerr << "\n- Debe tener por lo menos 20 archivos del mismo tipo en la carpeta 'in'!\n\n";
        exit(EXIT_FAILURE);
    }

    int archivosPorThread = archivos.size() / nThreads; 

    // Si se detectan mas threads que archivos, se ajusta para que cada thread ejecute un archivo, si no da error
    if(nThreads > archivos.size()) {
        archivosPorThread = 1;
        nThreads = archivos.size();
    }

   // int clearResult = system("clear");
    cout << "\n- Comenzando la creación de hilos...\n\n";
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
            for (int j = inicio; j < fin; j++) {
                cuentaPalabras(rutaIn + "/" + archivos[j], rutaOut + "/" + archivos[j]);
                mtx.lock();
                cout << " -> proceso pid= "<< getpid() <<" - archivo " << rutaIn + "/" + archivos[j] << ", procesado por el thread " << i << endl;
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

    cout << "\n- Todos los hilos han terminado.\n" << endl;
    
    
}