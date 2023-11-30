#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
//#include "funciones/funciones.h"

using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "\n### Error al llamar la función ###\nDebe ejecutarse como ./app <path_archivo>\n\n";
        exit(EXIT_FAILURE);
    }
    
    cout << endl;
    string path = argv[1];

    // Verificar la existencia y extension del archivo
    if (!fs::exists(path)) { cerr << "El archivo no existe.\n\n"; exit(EXIT_FAILURE); }
    string ext = path.substr(path.length() - 4);
    if (ext != ".gra"){ cerr << "Error!!! Debe ingresar un archivo '.gra'\n\n"; exit(EXIT_FAILURE); }

    cout << "Path del archivo: " << path << endl;
}

