#include "funciones.h"

/*
Creamos una expresion regular exactamente igual a como se ve en la primera linea del archivo "datos.gra".
Seguido de los dos puntos : verificamos que sean cualquier cosa, osea, caracteres, numeros, etc. Lo que interesa
validar es que la primera palabra sea "titulo:". y que a continuacion no sea un texto vacío. 
Aprovechamos de crear una funcion pair para retornar el texto que es el nombre del titulo.

por ejemplo:
    titulo:"" --> falso
    tituloo:"Grafico de lineas" --> falso, ya que dice no dice "titulo"
*/

pair<bool, string> validarTitulo(const string& linea) {
    // Definir el patrón regex para el título
    regex patron("titulo:\"([^\"]+)\"");

    // Objeto para almacenar los resultados del match
    smatch matches;

    // Validar el título con el patrón regex
    if (regex_match(linea, matches, patron)) {
        // El título coincide con el patrón, devolver el título encontrado
        return make_pair(true, matches[1]);
    } else {
        // El título no coincide con el patrón
        return make_pair(false, "");
    }
}


/*
Creamos la expresion regular. Notemos que la forma es exacta al formato de "datos.gra", solo que los \\d+
significa que seguido de los dos puntos : despues de la x o y, debe ir un digito o mas entre 0 y 9. Por ejemplo si 
se llegara a poner una letra en vez de un numero devuelve falso. Tambien devuelve falso si se
llegará a colocar una coordenada z:10
*/
bool validarFormato(const string& linea) {
    // Definir el patrón regex para la línea esperada
    regex patron("x:\\d+,y:\\d+");

    // Validar la línea con el patrón regex
    return regex_match(linea, patron);
}



/* Quizas se pudo haber hecho de otra manera, ya que estoy repitiendo el patron con la expresion regular de la
funcion validarFormato... Pero esta funcion lo que hace es retornar 2 vectores con cada valor de x y
correspondiente... es necesario repetir el patron para leer el valor. Pensé en hacerlo en la funcion validarFormato,
pero ya hubiera sido muy complicado retornar los 2 vectores y el booleano, ademas hubiera tenido que modificar
el main que ya esta funcionando bien...
*/
pair<vector<int>, vector<int>> extraerValoresDesdeArchivo(const string& nombreArchivo) {
    vector<int> valoresX, valoresY;

    // Definir el patrón regex para las líneas esperadas
    regex patron("x:(\\d+),y:(\\d+)");

    // Abrir el archivo
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        // Ignorar la primera línea (presumiblemente el título)
        string titulo;
        getline(archivo, titulo);

        // Leer las líneas restantes y extraer los valores de 'x' e 'y'
        string linea;
        while (getline(archivo, linea)) {
            // Obtener los resultados del regex
            smatch resultados;

            // Validar la línea con el patrón regex
            if (regex_match(linea, resultados, patron)) {
                // Obtener los números encontrados en 'x' e 'y'
                int numeroX = stoi(resultados[1].str());
                int numeroY = stoi(resultados[2].str());

                // Agregar los números a los vectores correspondientes
                valoresX.push_back(numeroX);
                valoresY.push_back(numeroY);
            }
        }

        // Cerrar el archivo
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    // Devolver los vectores con los valores de 'x' e 'y'
    return {valoresX, valoresY};
}



