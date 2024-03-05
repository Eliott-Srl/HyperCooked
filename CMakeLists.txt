cmake_minimum_required(VERSION 3.27)
project(HyperCooked C)

set(CMAKE_C_STANDARD 11)

add_executable(HyperCooked main.c
        types.h
        Recettes/Recettes.c
        Recettes/Recettes.h
        Commandes/Commandes.c
        Commandes/Commandes.h)