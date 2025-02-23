#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

QuicheServer::QuicheServer(uint16_t port) : sock_fd_(-1), port_(port) {
    setup();
}

QuicheServer::~QuicheServer() {
    if (sock_fd_ != -1) {
        close(sock_fd_);
    }
}

void QuicheServer::setup() {
    sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd_ < 0) {
        std::cerr << "Error creating socket\n";
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if (bind(sock_fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Binding failed\n";
        return;
    }

    std::cout << "Server listening on port " << port_ << "...\n";
}

void QuicheServer::receive_message() {
    char buffer[1024];
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    auto recv_len = recvfrom(sock_fd_, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        std::cout << "Received message: " << buffer << std::endl;

        std::string response = "Hello, from server";
        send_message(response, &client_addr, client_len);
    }
}

void QuicheServer::send_message(const std::string& message, struct sockaddr_in* clientAddr, socklen_t clientLen) const {
    sendto(sock_fd_, message.c_str(), message.size(), 0, (struct sockaddr*)clientAddr, clientLen);
    std::cout << "Sent response: " << message << std::endl;
}

[[noreturn]] void QuicheServer::run() {
    while (true) {
        receive_message();
    }
}
