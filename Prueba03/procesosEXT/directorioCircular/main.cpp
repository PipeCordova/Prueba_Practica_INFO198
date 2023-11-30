#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "funciones/funciones.h"

#include <algorithm>

using namespace std;
namespace fs = filesystem;

// Falta validar el formato no mas
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
    if (ext != ".dre"){ cerr << "Error!!! Debe ingresar un archivo '.dre'\n\n"; exit(EXIT_FAILURE); }

    ifstream archivo(path);
    string linea, dirBase;
    vector<string> directorios, archivos;


    while(getline(archivo, linea)){
        istringstream iss(linea);
        string key;
        if(getline(iss, key, '=')){
            if(key == "dirBase"){ // key=dirBase --> dirBase=./dirBase
                getline(iss, dirBase);
                dirBase.erase(remove_if(dirBase.begin(), dirBase.end(), ::isspace), dirBase.end()); // Borra los espacios, no se porque se crea con un espacio al final, pasa lo mismo con los files y los dirs
                if(!fs::exists(dirBase)) fs::create_directory(dirBase);
                else { // si existe, lo borra y despues lo crea
                    string comandoBorrar = "rm -r " + dirBase; 
                    basura = system(comandoBorrar.c_str());
                    fs::create_directory(dirBase);
                }
            } else if(key == "dirs"){ // key=dirs --> dirs=dir1;dir2;dir3;dir4;dir5
                string dirs;
                getline(iss, dirs);
                istringstream lineaDirs(dirs);
                string dir;
                while(getline(lineaDirs, dir, ';')) directorios.push_back(dir);
                // Crear directorios (dirs)
                for (string d : directorios) {
                    d.erase(remove_if(d.begin(), d.end(), ::isspace), d.end());
                    fs::create_directory(dirBase + "/" + d);
                }
                //llenarDirectorios(dirBase, directorios);
            } else { // key=dir1 --> files=file1.txt;file2.txt
                string files;
                getline(iss, files);
                istringstream lineaFiles(files);
                string file;
                while(getline(lineaFiles, file, ';')) archivos.push_back(file);
                for(string f : archivos){
                    // Crear el archivo
                    f.erase(remove_if(f.begin(), f.end(), ::isspace), f.end());
                    string nombreArchivo = dirBase + "/" + key + "/" + f;
                    ofstream archivo(nombreArchivo);
                    archivo.close();
                }
                archivos.clear();
            }
        }
    }

    string ultimoDir = directorios.back();
    ultimoDir.erase(remove_if(ultimoDir.begin(), ultimoDir.end(), ::isspace), ultimoDir.end());
    // La única forma que me funciono fue entrar en la carpeta dirBase y crear el link desde ahi dentro
    string comandoEnlace = "cd " + dirBase + " && " + "ln -s ." + dirBase + " " + ultimoDir;
    string comandoBorrarDir = "cd " + dirBase + " && rm -r " + ultimoDir;
    basura = system(comandoBorrarDir.c_str());
    basura = system(comandoEnlace.c_str());

    // Mostrar el árbol utilizando el comando "tree"
    cout << "Árbol del directorio '" << dirBase << "'\n";
    string comandoTree = "tree " + dirBase;
    basura = system(comandoTree.c_str());
    cout << endl;
}

