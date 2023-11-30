#include "funciones.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

// Función para crear directorios y archivos recursivamente
void crearObjetos(const json& objeto, const string& rutaBase) {
    // Verificar el tipo del objeto
    if (objeto["tipo"] == "directorio") {
        // Crear el directorio
        string nombreDirectorio = rutaBase + "/" + objeto["nombre"].get<string>();
        fs::create_directory(nombreDirectorio);
        //cout << "Directorio creado: " << nombreDirectorio << endl;

        // Recursión para crear objetos anidados
        for (const auto& objAnidado : objeto["objetos"]) {
            crearObjetos(objAnidado, nombreDirectorio);
        }
    } else if (objeto["tipo"] == "archivo") {
        // Crear el archivo
        string nombreArchivo = rutaBase + "/" + objeto["nombre"].get<string>();
        ofstream archivo(nombreArchivo);
        archivo << objeto["contenido"].get<string>();
        archivo.close();
        //cout << "Archivo creado: " << nombreArchivo << " con contenido:\n" << objeto["contenido"].get<string>() << endl;

        // Ver permisos
        if (objeto.contains("permisos")) {
            cout << "Permisos '" << nombreArchivo << "': ";
            for (const auto& permiso : objeto["permisos"]) {
                cout << permiso << " ";
            }
            cout << endl;
            // no se que hacer con los permisos, solo los imprimí
        }
    }
}