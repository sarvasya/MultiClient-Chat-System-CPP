#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

vector<int> clients;
mutex mtx;

void broadcast(const char* msg, int sender) {
    lock_guard<mutex> lock(mtx);
    for (int client : clients) {
        if (client != sender) {
            send(client, msg, strlen(msg), 0);
        }
    }
}

void handle_client(int client_socket) {
    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes <= 0) {
            lock_guard<mutex> lock(mtx);
            clients.erase(remove(clients.begin(), clients.end(), client_socket), clients.end());
            close(client_socket);
            break;
        }

        broadcast(buffer, client_socket);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    cout << "Server started on port 8080...\n";

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);

        {
            lock_guard<mutex> lock(mtx);
            clients.push_back(client_socket);
        }

        thread(handle_client, client_socket).detach();
    }

    close(server_fd);
    return 0;
}