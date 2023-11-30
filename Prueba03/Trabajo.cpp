#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>     // getopt
#include <algorithm>    // find
#include "funciones/archivos.h"
#include "funciones/menu.h"
#include "funciones/vectores.h"

using namespace std;

int main(int argc, char* argv[]){
    // Declaración de variables
    int c;
    bool flg = true, flg1 = false, flg2 = false;
    string u, v, f, t, i, o, rango;

    while((c = getopt(argc, argv, "u:v:f:t:i:o:")) != -1){
        switch(c) {
            case 'u':
                u = optarg;
                break;
            case 'v':
                v = optarg;
                break;
            case 'f':
                f = optarg;
                break;
            case 't':
                t = optarg;
                break;
            case 'i':
                i = optarg;
                break;
            case 'o':
                o = optarg;
                break;
        }
    }
    if(u.empty()){
        cerr << "El parametro -u es OBLIGATORIO\n";
        exit(EXIT_FAILURE);
    } if(v.empty()){
        cerr << "El parametro -v es OBLIGATORIO\n";
        exit(EXIT_FAILURE);
    } if(f.empty()){
        cerr << "El parametro -f es OBLIGATORIO\n";
        exit(EXIT_FAILURE);
    } if(t.empty()){
        cerr << "El parametro -t es OBLIGATORIO\n";
        exit(EXIT_FAILURE);
    } if(i.empty()){
        cerr << "El parametro -i es OBLIGATORIO\n"; // path + nombre_archivo de un archivo de texto de mas de 1MB
        exit(EXIT_FAILURE);
    } if(o.empty()){
        cerr << "El parametro -o es OBLIGATORIO\n"; // path + nombre_archivo de un archivo de texto nuevo, donde se guarda el resultado de la funcion 7
        exit(EXIT_FAILURE);
    }

    // Leer bases de datos y verificar si existen
    string rutaPerfiles = getenv("BD_PERFILES"), rutaMenu = getenv("BD_MENU"), rutaUsuarios = getenv("BD_USUARIOS");
    if(!archivoExiste(rutaMenu)) {
        cerr << "\n- La base de datos '" << rutaMenu << "' NO fue encontrada!\n\n";
        exit(EXIT_FAILURE);
    } if(!archivoExiste(rutaPerfiles)) {
        cerr << "\n- La base de datos '" << rutaPerfiles << "' NO fue encontrada!\n\n";
        exit(EXIT_FAILURE);
    } if(!archivoExiste(rutaUsuarios)) {
        cerr << "\n- La base de datos '" << rutaUsuarios<< "' NO fue encontrada!\n\n";
        exit(EXIT_FAILURE);
    }

    // Crear comandos para ejecutar procesos externos
    string ext = getenv("EXTENSION"), pathIn = getenv("PATH_FILES_IN"), pathOut = getenv("PATH_FILES_OUT"), nThreads = getenv("AMOUNT_THREADS"), invIdxFile = getenv("INVERTED_INDEX_FILE");
    string preCom8 = getenv("PRECOM8"), preCom9 = getenv("PRECOM9"), preCom10 = getenv("PRECOM10");
    string comandoOP8 = preCom8 + " " + ext + " " + pathIn + " " + pathOut + " " + nThreads;
    string comandoOP9 = preCom9 + " " + invIdxFile + " " + pathOut;

    string topk = getenv("TOPK");
    if (stoi(topk) <= 4){
        cerr << "\n- La variable TOPK debe ser mayor que 4\n- Valor actual TOPK = " << topk << "\n\n";
        exit(EXIT_FAILURE);
    }
    string comandoOP10 = preCom10 + " " + invIdxFile + " " + topk;

    // Extraigo el rango del usuario u
    rango = obtenerRango(u,rutaUsuarios);

    // Crear el vector V (De string a vector de enteros -> "1,2,3,4" => [1,2,3,4])
    vector<int> vectorV = stringToVector(v);

    // Crear vector con las opciones disponibles segun su rango
    // Vinculado con la base de datos perfiles.txt
    vector<int> opValidas = verificarOpValidas(rango, rutaPerfiles);

    int opcion, basura;
    int clearResult = system("clear");
    while(flg){
        desplegarMenu(u,rango,rutaMenu);
        cin >> opcion;
        cout << endl;

        clearResult = system("clear");
        
        cout << "\t###### RESPUESTA ######\n";                    

        bool tienePermisos = find(opValidas.begin(), opValidas.end(), opcion) != opValidas.end();

        if (tienePermisos) {
            if (opcion == 1) {
                int suma = sumatoria(vectorV);
                cout << "- La suma de los elementos de su vector es = " << suma << "\n\n";
            } else if (opcion == 2) {
                double prom = promedio(vectorV);
                cout << "- El promedio se los elementos de su vector es = "<< prom << "\n\n";
            } else if (opcion == 3) {
                cout << "- La moda de su vector es " << moda(vectorV) << "\n\n";
            } else if (opcion == 4) {
                cout << "- Su vector tiene " << vectorV.size() << " elementos\n\n";
            } else if(opcion == 5){
                if(!archivoExiste(f)) crearArchivo(f);
                else cout << "- Ya existe el archivo '" << f << "'\n\n";
            } else if(opcion == 6){
                if(archivoExiste(f)) agregarAlArchivo(f,t);
                else cout << "- El archivo '" << f << "' de abrir no existe!\n\n";
            } else if(opcion == 7){
                cout << "- Contando palabras... \n";
                cuentaPalabras(i,o);
            } else if(opcion == 8){
                basura = system(comandoOP8.c_str()); // Lo declaro int para evitar warnings
                flg1 = true;
            } else if(opcion == 9){
                if(flg1){
                    cout << endl;
                    basura = system(comandoOP9.c_str());
                    flg2 = true;
                } else cout << "- Para ejecutar la opcion 9, debe haber ejecutado la opcion 8 primero!\n\n";
            } else if(opcion == 10){
                if(flg2){
                    cout << endl;
                    basura = system(comandoOP10.c_str());
                    clearResult = system("clear");
                } else cout << "- Para ejecutar la opcion 10, debe haber ejecutado la opcion 9 primero\n\n";
            } else if(opcion == 11){
                string path11;
                cout << "Ingrese archivo a procesar: "; // jsons/arbol.dit
                cin >> path11;
                string comandoOP11 = "./procesosEXT/directorioArbol/app " + path11;
                basura = system(comandoOP11.c_str());
            } else if(opcion == 12){
                string path12;
                cout << "Ingrese archivo a procesar: "; // jsons/datos.dre
                cin >> path12;
                string comandoOP12 = "./procesosEXT/directorioCircular/app " + path12;
                basura = system(comandoOP12.c_str());
            } else if(opcion == 13){
                string path13;
                cout << "Ingrese archivo a procesar: "; // jsons/datos.gra
                cin >> path13;
                string comandoOP13 = "./procesosEXT/procesGrafico/app " + path13;
                basura = system(comandoOP13.c_str());
            }
        } else {
            if (opcion == 0) {
                flg = !flg;
                cout << "Programa Finalizado\n";
            } else if(opcion > 13 || opcion < 0) cout << "- La opcion " << opcion << " no ha sido creada aún!\n\n";
            else cout << "- El usuario no tiene permisos para ese comando!\n\n";
        }
    }
}