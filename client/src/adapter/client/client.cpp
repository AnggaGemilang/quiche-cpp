#include "client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

QuicheClient::QuicheClient(const std::string& serverIP, uint16_t port)
    : ip_server_(serverIP), port_(port), sock_fd_(-1) {
    setup();
}

QuicheClient::~QuicheClient() {
    if (sock_fd_ != -1) {
        close(sock_fd_);
    }
}

void QuicheClient::setup() {
    sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd_ < 0) {
        std::cerr << "Error creating socket\n";
    }
}

void QuicheClient::connect() const {
    std::cout << "Connecting to server " << ip_server_ << " on port " << port_ << "...\n";
}

void QuicheClient::send_message(const std::string& message) const {
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = inet_addr(ip_server_.c_str());

    sendto(sock_fd_, message.c_str(), message.size(), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    std::cout << "Sent message: " << message << std::endl;
}

void QuicheClient::receive_message() const {
    char buffer[1024];
    sockaddr_in from_addr{};
    socklen_t from_len = sizeof(from_addr);

    auto recv_len = recvfrom(sock_fd_, buffer, sizeof(buffer), 0, (struct sockaddr*)&from_addr, &from_len);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        std::cout << "Received response: " << buffer << std::endl;
    }
}
