#include <iostream>
#include <unistd.h> //getpid

using namespace std;

int main(int argc, char const *argv[]){
    bool flg = true;
    int topk = 5;
    while (flg){
        int clearResult = system("clear");
        cout << "### Buscador de indice invertido (pid = "<< getpid() << ") ###\n\n";
        cout << "- Los topk documentos serán = " << topk << "\n";
        cout << "- Escriba texto a buscar: ";
        string frase;
        getline(cin, frase);
    }
}
