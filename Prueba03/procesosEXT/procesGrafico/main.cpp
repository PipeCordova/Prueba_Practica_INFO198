#include "funciones/funciones.h"
#include "funciones/funciones.cpp"


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

    //cout << "Path del archivo: " << path << endl;


    // Parte Pipe, Iniciando validacion formato 


    ifstream archivo(path); // abrimos el archivo datos.gra

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    string linea;

    // Variable para indicar si el formato es válido o no
    bool formatoValido = true;

    string titulo;
    // Validar la primera línea como título
    if (getline(archivo, linea)) {
        auto resultadoTitulo = validarTitulo(linea);

        if (!resultadoTitulo.first) {
            formatoValido = false;
        } else {
            titulo = resultadoTitulo.second;
        }
    } else {
        formatoValido = false; // El archivo está vacío
    }

    // cout << titulo << endl;;


    // Validar el formato de las líneas restantes
    while (getline(archivo, linea)) {
        // Validar el formato de la línea actual
        if (!validarFormato(linea)) {
            formatoValido = false;
            break; // Salir del bucle si se encuentra una línea con formato incorrecto
        }
    }


    // Imprimir el resultado final
    if (!formatoValido) {
        cout << "El formato del archivo NO es válido!." << endl;
        exit(EXIT_FAILURE);
    }




    vector<int> valoresX, valoresY;
    auto valores = extraerValoresDesdeArchivo(path);

    valoresX = valores.first;
    valoresY = valores.second;

    // for (size_t i = 0; i < numerosX.size(); i++){
    //     cout << "x:" << posX[i] << " y:" << posY[i] << endl;
    // }

    // cout << endl;

    

    return EXIT_SUCCESS;
}


