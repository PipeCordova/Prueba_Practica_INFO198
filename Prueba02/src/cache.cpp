#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

using namespace std;

vector<int> clientSockets;

void handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        cout << "handleClient: " << buffer << endl;

        // Retransmitir el mensaje a todos los demás clientes
        for (int otherSocket : clientSockets) {
            if (otherSocket != clientSocket) {
                send(otherSocket, buffer, bytesRead, 0);
            }
        }
    }

    close(clientSocket);
}

int startServer(int& serverSocket, sockaddr_in& serverAddr, sockaddr_in& clientAddr) {
    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Puerto del servidor
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket a la dirección del servidor
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error al enlazar el socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        perror("Error al escuchar");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    cout << "Esperando conexiones entrantes..." << endl;
    return 1;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    startServer(serverSocket, serverAddr, clientAddr);

    while (true) {
        // Aceptar la conexión entrante
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error al aceptar la conexión");
            continue; // Continuar esperando conexiones
        }

        cout << "Cliente conectado" << endl;

        // Agregar el nuevo cliente a la lista de sockets de clientes
        clientSockets.push_back(clientSocket);

        // Crear un nuevo hilo para manejar la conexión del cliente
        thread(handleClient, clientSocket).detach();

        if(clientSockets.size() == 2){
            char msg0[1024];
            char msg1[1024];
            ssize_t bytesRead;
            bool success = true;

            while (success) {
                cout << "Entre aqui"<< endl;

                ssize_t msgRead0 = recv(clientSockets[0], msg0, sizeof(msg0), 0);
                msg0[msgRead0] = '\0';
                ssize_t msgRead1 = recv(clientSockets[1], msg1, sizeof(msg1), 0);
                msg1[msgRead1] = '\0';
                //if(!string(msg0).empty())cout << "msg0 = " << string(msg0) << "\n\n";
                //if(!string(msg1).empty())cout << "msg1 = " << string(msg1) << "\n\n";

                success = false;


                /*
                ssize_t msgRead0 = recv(clientSockets[0], msg0, sizeof(msg0), 0);
                msg[msgRead] = '\0';
                cout << "Mensaje recibido: " << msg << endl;
                string responseMsg = "El mensaje recibido fue: " + string(msg);
                if (string(msg) == "Salir") {
                    send(clientSocket, responseMsg.c_str(), responseMsg.length(), 0);
                    close(clientSocket);
                    cout << "Cliente desconectado" << endl;
                    break;
                }
                else {
                    send(clientSocket, responseMsg.c_str(), responseMsg.length(), 0);
                }*/
            }
        }
    }

    // El servidor seguirá esperando nuevas conexiones sin terminar

    return EXIT_SUCCESS;
}
