#include "adapter/client/client.h"
#include <thread>

int main() {
    QuicheClient client("127.0.0.1", 6666);
    client.connect();
    
    std::string message = "Hello, from client";
    client.send_message(message);
    client.receive_message();

    return 0;
}
