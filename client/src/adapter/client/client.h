#pragma once
#include <quiche.h>
#include <iostream>
#include <string>

class QuicheClient {
public:
    QuicheClient(const std::string& serverIP, uint16_t port);
    ~QuicheClient();
    
    void connect() const;
    void send_message(const std::string& message) const;
    void receive_message() const;

private:
    std::string ip_server_;
    uint16_t port_;
    int sock_fd_;
    
    void setup();
};
