#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

using namespace std;

void receiveMessages(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        cout << "mensaje de vuelta: '" << buffer << "'\n";
    }
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
        string fullMessage = username + " busca: " + message;
        send(clientSocket, fullMessage.c_str(), fullMessage.length(), 0);

        cout << "\n\n## Desea continuar (s/n)?\n";
        getline(cin, seguir);
        if(seguir == "n" || seguir == "no") flg = false;
    }

    // Cerrar el socket del cliente
    close(clientSocket);

    return 0;
}
