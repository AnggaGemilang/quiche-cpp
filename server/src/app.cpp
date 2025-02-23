#include "adapter/server/server.h"
#include <thread>

int main() {
    std::thread server_thread([]() {
        QuicheServer server(6666);
        server.run();
    });

    server_thread.join();
    return 0;
}
