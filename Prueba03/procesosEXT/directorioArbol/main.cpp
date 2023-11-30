#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include "funciones/funciones.h"

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

// Solo falta validar el formato
int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "\n### Error al llamar la función ###\nDebe ejecutarse como ./app <path_archivo>\n\n";
        exit(EXIT_FAILURE);
    }
    
    cout << endl;
    int basura;
    string path = argv[1];

    // Verificar la existencia y extension del archivo
    if (!fs::exists(path)) { cerr << "El archivo no existe.\n\n"; exit(EXIT_FAILURE); }
    string ext = path.substr(path.length() - 4);
    if (ext != ".dit"){ cerr << "Error!!! Debe ingresar un archivo '.dit'\n\n"; exit(EXIT_FAILURE); }

    // Leer archivo JSON
    ifstream archivo(path);
    json j;
    archivo >> j;

    // Obtener y crear el directorio base del JSON, antes de crearlo, se borra si es que existe
    string rutaBase = j["dirBase"].get<string>();
    if(fs::exists(rutaBase)){ 
        string comandoBorrar = "rm -r " + rutaBase; 
        basura = system(comandoBorrar.c_str());
    }
    fs::create_directory(rutaBase);

    // Crear objetos del arreglo objetos del JSON
    for (const auto& objeto : j["objetos"]) {
        crearObjetos(objeto, rutaBase);
    }

    // Mostrar el árbol utilizando el comando "tree"
    cout << "\nÁrbol del directorio '" << rutaBase << "'\n";
    string comandoTree = "tree " + rutaBase;
    basura = system(comandoTree.c_str());
    cout << endl;
}
