#pragma once
#include <quiche.h>
#include <string>

class QuicheServer {
public:
    explicit QuicheServer(uint16_t port);
    ~QuicheServer();

    [[noreturn]] void run();
private:
    int sock_fd_;
    uint16_t port_;

    void setup();
    void receive_message();
    void send_message(const std::string& message, struct sockaddr_in* clientAddr, socklen_t clientLen) const;
};
