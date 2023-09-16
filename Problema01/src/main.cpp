#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include "../include/funciones.h"
#include <chrono>
#include <thread>  

using namespace std;

int main(int argc, char *argv[]) {
    string u, p, v;
    int c;
    while ((c = getopt(argc, argv, "u:p:v:")) != -1) {
        switch (c) {
            case 'u':
                u = optarg;
                break;
            case 'p':
                p = optarg;
                break;
            case 'v':
                v = optarg;
                break;
        }
    }
    
    if (algunParametroVacio(u, "-u") ||
        algunParametroVacio(p, "-p") ||
        algunParametroVacio(v, "-v")){
        exit(EXIT_FAILURE);
    }

    string rutaUsuarios;
    leerConfiguracion(rutaUsuarios);

    cout << endl;
    
    if (u == "admin" && p == "admin"){

    } else {
        bool L = usuarioExiste(u, p, rutaUsuarios);
        if (L){
            cout << "El usuario existe y contraseña igual";
        }
        else{
            cout << "El usuario no existe";
        }
        cout << endl;
    }



    
    cout << "\nFin prueba 1 practica!!" << endl;
    return EXIT_SUCCESS;
}