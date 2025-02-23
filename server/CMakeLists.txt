cmake_minimum_required(VERSION 3.14)
project(QuicheExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path ke Quiche (ubah jika perlu)
set(QUICHE_DIR "/opt/quiche")

include_directories(${QUICHE_DIR}/quiche/include)
link_directories(${QUICHE_DIR}/target/release)

# Tambahkan executable
add_executable(main src/app.cpp src/adapter/server/server.cpp)

# Link dengan Quiche
target_link_libraries(main quiche)
