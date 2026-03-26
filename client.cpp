#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

void receive_messages(int sock) {
    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);

        if (bytes <= 0) {
            cout << "Disconnected from server\n";
            break;
        }

        cout << buffer << endl;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Connection failed\n";
        return -1;
    }

    thread(receive_messages, sock).detach();

    char msg[1024];

    while (true) {
        cin.getline(msg, 1024);
        send(sock, msg, strlen(msg), 0);
    }

    close(sock);
    return 0;
}