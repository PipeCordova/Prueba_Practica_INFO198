#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<pair<string, int>>> cacheData;
vector<int> clientSockets;

struct Mensaje{
    string origen;
    string destino;
    string txtToSearch;
    vector<pair<string, int>> data;
};

void printMessage(const Mensaje &msg) {
    cout << "Origen: " << msg.origen << endl;
    cout << "Destino: " << msg.destino << endl;
    cout << "Texto a buscar: " << msg.txtToSearch << endl;

    cout << "Data: " << endl;
    if(msg.data.empty()) cout << "  No hay nada" << endl;
    else for (const auto &dataPair : msg.data) cout << "  " << dataPair.first << ": " << dataPair.second << endl;
}

void sendMensaje(int backSocket, const Mensaje& msg) {
    string message = msg.origen + "|" + msg.destino + "|" + msg.txtToSearch + "|";

    for (const auto& p : msg.data) {
        message += p.first + ":" + to_string(p.second) + ",";
    }

    send(backSocket, message.c_str(), message.length(), 0);
}

void unpackMessage(const string &message, Mensaje &msg) {
    istringstream ss(message);
    string token;
    vector<string> parts;

    while (getline(ss, token, '|')) parts.push_back(token);

    if (parts.size() >= 3) {
        msg.origen = parts[0];
        msg.destino = parts[1];
        msg.txtToSearch = parts[2];

        if (parts.size() > 3) {
            for (size_t i = 3; i < parts.size(); i++) {
                istringstream ssPair(parts[i]);
                string pairToken;
                pair<string, int> dataPair;
                while (getline(ssPair, pairToken, ':')) {
                    string key = pairToken;
                    if (getline(ssPair, pairToken, ',')) {
                        int value = stoi(pairToken);
                        dataPair = make_pair(key, value);
                        msg.data.push_back(dataPair);
                    }
                }
            }
        }
    }
}

void handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;
    int backSocket;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        // obtener el socket el backend
        for (int otherSocket : clientSockets) {
            if (otherSocket != clientSocket) {
                backSocket = otherSocket;
            }
        }

        buffer[bytesRead] = '\0';
        cout << buffer << endl;

        Mensaje msg;
        unpackMessage(buffer, msg);
        //printMessage(msg);

        // Buscar si existe la clave msg.txtToSearch
        if (cacheData.find(msg.txtToSearch) != cacheData.end()) {
            // Si existe, enviar el valor como mensaje al frontend
            string responseMessage = "El valor de " + msg.txtToSearch + " es: ";
            for (auto &pair : cacheData[msg.txtToSearch]) {
                responseMessage += "(" + pair.first + "," + to_string(pair.second) + ") ";
            }
            send(backSocket, responseMessage.c_str(), responseMessage.length(), 0);
        } else {
            // Si no existe, enviar un mensaje al backend con la estructura msg
            // MENSAJE NO ENCONTRADO EN LA CACHE, BUSCAREMOS EN BACKEND
            if(msg.origen == "./invertedIndex") {
                //cout << "ENTRE AQUI!!!" << endl;
                sendMensaje(backSocket, msg);
            }
            else{
                cout << "ENTRE AQUI!!!" << endl;
                msg.origen = "./memcache";
                msg.destino = "./invertedIndex";
                sendMensaje(backSocket, msg);
            }
        }
    }

    close(clientSocket);
}

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

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
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
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

    while (true) {
        // Aceptar la conexión entrante
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error al aceptar la conexión");
            continue; // Continuar esperando conexiones
        }

        cout << "Cliente conectado" << endl;

        // Agregar el nuevo cliente a la lista de sockets de clientes
        clientSockets.push_back(clientSocket);

        // Crear un nuevo hilo para manejar la conexión del cliente
        thread(handleClient, clientSocket).detach();
    }

    return 0;
}
