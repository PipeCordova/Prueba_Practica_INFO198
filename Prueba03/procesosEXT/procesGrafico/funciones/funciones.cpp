#include "funciones.h"


/*
En esta funcion validamos que la primera linea sea de la forma:
    titulo:texto

Entonces si o si debe decir 'titulo' antes de los dos puntos.
Validamos que lo que viene acontinuacion de los dos puntos no sea vacio, ya que un titulo vacio no tiene
sentido. Aprovechamos de retornar una funcion par para que devuelva el string titulo tambien.

El titulo de datos.gra, dejalo sin comillas
*/
pair<bool, string> validarPrimeraLinea(const string& archivo) {
    ifstream file(archivo);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return {false, ""};
    }

    string primeraLinea;
    getline(file, primeraLinea);

    size_t pos = primeraLinea.find(':');
    if (pos != string::npos) {
        string antesDosPuntos = primeraLinea.substr(0, pos);
        string titulo = primeraLinea.substr(pos + 1);
        if (antesDosPuntos == "titulo" && !titulo.empty()) {
            return {true, titulo};
        }
    }
    file.close();
    return {false, ""};
}




/*
funcion creada manualmente para ver si cada linea desde la 2, cumple con el formato: x:int,y:int
*/
bool validarFormato(const string& linea) {
    size_t posX = linea.find("x:");
    size_t posY = linea.find("y:");

    if (posX != string::npos && posY != string::npos && posX < posY) {
        size_t posXDigit = posX + 2;
        size_t posYDigit = posY + 2;

        while (posXDigit < linea.length() && isdigit(linea[posXDigit])) {
            ++posXDigit;
        }

        while (posYDigit < linea.length() && (isdigit(linea[posYDigit]) || isspace(linea[posYDigit]) || linea[posYDigit] == ',')) {
            ++posYDigit;
        }

        // Verificar si llegamos al final de la línea después de 'y:'
        return posXDigit > posX + 2 && posYDigit > posY + 2 && (posYDigit == linea.length() || isspace(linea[posYDigit]));
    }

    return false;
}

bool validarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    string linea;
    bool formatoValido = true;
    int numeroLinea = 1;

    while (getline(archivo, linea)) {
        if (numeroLinea >= 2 && !validarFormato(linea)) {
            formatoValido = false;
            //cout << "Formato no válido en la línea " << numeroLinea << ": " << linea << endl;
        }
        ++numeroLinea;
    }

    archivo.close();

    // if (formatoValido) {
    //     cout << "El formato es válido en todas las líneas." << endl;
    // } else {
    //     cout << "El formato no es válido en al menos una línea." << endl;
    // }

    return formatoValido;
}

