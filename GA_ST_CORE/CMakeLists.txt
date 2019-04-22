cmake_minimum_required(VERSION 3.9)
project(GA_ST_CORE)

set(CMAKE_CXX_STANDARD 11)

add_executable(GA_ST_CORE
        Aux.cpp
        Aux.h
        GA.cpp
        GA.h
        GAAGM.cpp
        GAAGM.h
        Grafo.cpp
        Grafo.h
        Individuo.cpp
        Individuo.h
        main.cpp
        Populacao.cpp
        Populacao.h
        Vertice.cpp
        Vertice.h)
