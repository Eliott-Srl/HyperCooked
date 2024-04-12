cmake_minimum_required(VERSION 3.27)
project(HyperCooked C)

set(CMAKE_C_STANDARD 11)

add_executable(HyperCooked main.c
        resource.rc
        backend/Commandes/Recettes.c
        backend/Commandes/Recettes.h
        backend/Game/Game.c
        backend/Game/Game.h
        backend/Commandes/Commandes.c
        backend/Commandes/Commandes.h
        backend/Matrice/Meubles.c
        backend/Matrice/Meubles.h
        backend/backend.h
        backend/allezgros/Allezgros.c
        backend/allezgros/Allezgros.h
        backend/Utils/Utils.c
        backend/Utils/Utils.h)

target_link_libraries(${PROJECT_NAME} -lalleg44)