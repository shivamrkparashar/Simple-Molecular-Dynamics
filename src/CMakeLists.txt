cmake_minimum_required(VERSION 3.27)
project(SMD)

set(CMAKE_CXX_STANDARD 17)

add_executable(SMD main.cpp
        Vector.cpp
        energy.cpp
        atom.cpp
        atom.h
        energy.h
        global.h
        movies.cpp
        movies.h
        integrate.cpp
        integrate.h
        intialize.cpp
        intialize.h)
