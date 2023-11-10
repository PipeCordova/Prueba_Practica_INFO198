#include "../include/funcionesFrontend.h"

struct Mensaje {
    string origen;
    string destino;
    string txtToSearch;
    vector<pair<string, int>> data;
};

Mensaje msg;

void printData(Mensaje &msg) {
    int cont = 1;
    cout << "Origen: " << msg.origen << endl;
    cout << "Data: " << endl;
    if(msg.data.empty()) cout << "  No hay nada" << endl;
    else for (const auto &dataPair : msg.data) {
        cout << "  " << cont << ") " << dataPair.first << ": " << dataPair.second << endl;
        cont += 1;
    }
    msg.data.clear();
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

void receiveMessages(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        unpackMessage(buffer, msg);
        printData(msg);
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
        msg.origen = "./searcher";
        msg.destino = "./memcache";
        msg.txtToSearch = message;
        //msg.data = {{"example1", 1}, {"example2", 2}, {"example3", 3}};
        sendMensaje(clientSocket, msg);

        // Para que se imprima bien
        this_thread::sleep_for(std::chrono::milliseconds(500));

        cout << "\n\n## Desea continuar (si/no)?\n";
        getline(cin, seguir);
        if(seguir == "n" || seguir == "no") flg = false;
    }

    // Cerrar el socket del cliente
    close(clientSocket);

    return EXIT_SUCCESS;
}
