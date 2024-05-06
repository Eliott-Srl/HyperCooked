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
        backend/Utils/Utils.h
        backend/Game/Actions.c
        backend/Game/Actions.h
        backend/Game/Oncers.c
        backend/Game/Oncers.h
        backend/Son/song.c
        backend/Son/song.h
        backend/Commandes/Ingredients.c
        backend/Commandes/Ingredients.h
        backend/Game/Players.c
        backend/Game/Players.h
        backend/Game/Objects.c
        backend/Game/Objects.h
        backend/Game/Progress.c
        backend/Game/Progress.h)

target_link_libraries(${PROJECT_NAME} -lalleg44)
