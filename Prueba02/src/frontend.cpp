#include <iostream>
#include <unistd.h> //getpid

using namespace std;

int main(int argc, char const *argv[]){
    bool flg = true;
    int topk = 5;
    while (flg){
        int clearResult = system("clear");
        cout << "\tBUSCADOR BASADO EN INDICE INVERTIDO (pid = " << getpid() << ")\n\n";
        cout << "\tLos topk documentos serán = " << topk << "\n\n";
        cout << "\tEscriba texto a buscar: " << "\n\n";
        string frase;
        getline(cin, frase);
    }
}
