cmake_minimum_required(VERSION 3.28)
project(BufferManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(BufferManager main.cpp
        Interfaz.cpp
        Interfaz.h
        Bloque.cpp
        Bloque.h
        bufferManager.cpp
        bufferManager.h
        bufferPool.cpp
        bufferPool.h)
