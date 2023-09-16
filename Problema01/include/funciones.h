#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

using namespace std;

bool algunParametroVacio(const string &param, const string &nombreParametro);
void leerConfiguracion(string& rutaUsers);
bool usuarioExiste(const string& usuario, const string& contraseña, const string& nombreArchivo) ;

#endif 