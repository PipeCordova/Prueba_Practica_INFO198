#ifndef VECTORES_H
#define VECTORES_H

#include <vector>
#include <string>

using namespace std;

vector<int> verificarOpValidas(const string& rango, const string& path);
vector<int> stringToVector(const string& cadena);
int sumatoria(const vector<int>& vec);
double promedio(const vector<int>& vec);
int moda(const vector<int>& numeros);

#endif