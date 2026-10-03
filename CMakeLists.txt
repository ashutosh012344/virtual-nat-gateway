cmake_minimum_required(VERSION 3.20)

project(VirtualNATGateway
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vnat-gateway
    src/main.cpp
    src/packet.cpp
    src/connection_table.cpp
    src/nat_engine.cpp
)

target_include_directories(vnat-gateway
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
