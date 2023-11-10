#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

using namespace std;

struct Mensaje{
    string origen;
    string destino;
    string txtToSearch;
    vector<pair<string, int>> data;
};

//struct mensaje {}

void receiveMessages(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        cout << "mensaje de vuelta: '" << buffer << "'\n";
    }
}

void sendMensaje(int clientSocket, const Mensaje& msg) {
    string message = msg.origen + "|" + msg.destino + "|" + msg.txtToSearch + "|";

    for (const auto& p : msg.data) {
        message += p.first + ":" + to_string(p.second) + ",";
    }

    send(clientSocket, message.c_str(), message.length(), 0);
}

int main(int argc, char *argv[]) {

    string username = "Frontend";

    int clientSocket;
    struct sockaddr_in serverAddr;

    // Crear el socket del cliente
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Puerto del servidor
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor

    // Conectar al servidor
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error al conectar al servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    cout << "Conectado al servidor." << endl;

    // Crear un nuevo hilo para recibir mensajes del servidor
    thread(receiveMessages, clientSocket).detach();


    
    // Enviar mensajes al servidor
    int topk = 5;
    bool flg = true;
    string seguir;
    int clearResult = system("clear");

    char message[1024];
    while (flg) {
        clearResult = system("clear");
        cout << "BUSCADOR BASADO EN INDICE INVERTIDO (pid = " << getpid() << ")\n\n";
        cout << "Los topk documentos serán = " << topk<< "\n\n";
        cout << "Escriba texto a buscar: ";
        cin.getline(message, sizeof(message));
        Mensaje msg;
        msg.origen = "./searcher";
        msg.destino = "./memcache";
        msg.txtToSearch = message;
        //msg.data = {{"example1", 1}, {"example2", 2}, {"example3", 3}};
        sendMensaje(clientSocket, msg);

        cout << "\n\n## Desea continuar (si/no)?\n";
        getline(cin, seguir);
        if(seguir == "n" || seguir == "no") flg = false;
    }

    // Cerrar el socket del cliente
    close(clientSocket);

    return 0;
}
