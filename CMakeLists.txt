cmake_minimum_required(VERSION 3.27)
project(HyperCooked C)

set(CMAKE_C_STANDARD 11)

add_executable(HyperCooked main.c
        resource.rc
        types.h
        Recettes/Recettes.c
        Recettes/Recettes.h
        Game/Game.c
        Game/Game.h
        Commandes/Commandes.c
        Commandes/Commandes.h
        Matrice/Meubles.c
        Matrice/Meubles.h)

target_link_libraries(${PROJECT_NAME} -lalleg44)