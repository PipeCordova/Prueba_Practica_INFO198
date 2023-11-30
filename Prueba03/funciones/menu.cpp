#include "menu.h"
#include <iostream>
#include <fstream>

using namespace std;

void desplegarMenu(const string& u, const string& rango, const string& path){
    ifstream archivoMenu;
    string l;
    cout << "\t###### MENÚ ######\n";
    cout << "Usuario: " << u << "\t\tNivel: " << rango << "\n";
    archivoMenu.open(path);
    while (getline(archivoMenu, l,'\n')){
        int pos = l.find(",");
        cout << l.substr(0,pos) << ") " << l.substr(pos+1) << endl;
    }
    archivoMenu.close();
    cout << "Ingrese opción: ";
}