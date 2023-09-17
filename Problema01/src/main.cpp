#include "../include/funciones.h"

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
        algunParametroVacio(v, "-v")) {
        exit(EXIT_FAILURE);
    }

    vector<int> vectorEntrada = convertirlo(v); // Convertir a vector el "vector" v de la entrada.

    string pathUser = getenv("DB_USERS");
    string pathMenu = getenv("DB_MENU");

    vector <int> permisos;
    
    cout << endl;

    while (true){
        ifstream archivoMenu(pathMenu);

        mostrarMenu(archivoMenu);

        int eleccion = obtenerEleccion();

        if (eleccion == 0) {
            break;
        }

        if (u == "admin" && p == "admin") { // modo admin
            permisos = {1,2,3};
            ejecutarOpcion (eleccion, permisos, pathUser, u, vectorEntrada);
        } else if (!usuarioExiste(u, p, pathUser)) { // si no es admin se verifica que exista en la BD
            cout << "Usuario o contraseña ingresados no registrados en la BD!!" << endl;
            exit(EXIT_FAILURE);
        } else { // si existe en la BD, entonces esto
            permisos = {2,3};
            ejecutarOpcion (eleccion, permisos, pathUser, u, vectorEntrada);
        }

        cout << "\nEspere 5 segundos!!" << endl;
        this_thread::sleep_for(chrono::seconds(5)); // Esperar 5 segundos y se limpia la consola
        system("clear");
    }


    cout << "\nFin prueba 1 practica!!" << endl;
    return EXIT_SUCCESS;
}