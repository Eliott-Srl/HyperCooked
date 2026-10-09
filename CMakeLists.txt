cmake_minimum_required(VERSION 3.21)
project(HyperCooked C)

set(CMAKE_C_STANDARD 11)

add_executable(HyperCooked main.c
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
        backend/Son/Song.c
        backend/Son/Song.h
        backend/Commandes/Ingredients.c
        backend/Commandes/Ingredients.h
        backend/Game/Players.c
        backend/Game/Players.h
        backend/Game/Objects.c
        backend/Game/Objects.h
        backend/Game/Progress.c
        backend/Game/Progress.h)

if(WIN32)
    # Icône / ressources Windows
    target_sources(HyperCooked PRIVATE resource.rc)
    target_link_libraries(HyperCooked PRIVATE alleg44)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALLEGRO4 REQUIRED allegro)
    target_include_directories(HyperCooked PRIVATE ${ALLEGRO4_INCLUDE_DIRS})
    target_link_libraries(HyperCooked PRIVATE ${ALLEGRO4_LIBRARIES} m)
endif()

# Ressources chargées en chemins relatifs : on les place à côté de l'exécutable
add_custom_command(TARGET HyperCooked POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:HyperCooked>/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/maps $<TARGET_FILE_DIR:HyperCooked>/maps)

# data/ contient les scores : copié une seule fois pour ne pas les écraser
if(NOT EXISTS ${CMAKE_BINARY_DIR}/data)
    file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
endif()
