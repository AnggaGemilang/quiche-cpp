cmake_minimum_required(VERSION 3.14)
project(quiche-client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QUICHE_DIR "/opt/quiche")

include_directories(${QUICHE_DIR}/quiche/include)
link_directories(${QUICHE_DIR}/target/release)

add_executable(main src/app.cpp src/adapter/client/client.cpp)

target_link_libraries(main quiche)
