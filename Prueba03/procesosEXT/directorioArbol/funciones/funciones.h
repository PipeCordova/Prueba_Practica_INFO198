#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void crearObjetos(const json& objeto, const string& rutaBase);

#endif