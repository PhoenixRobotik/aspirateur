####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project (PhoenixAspirateur)
set     (PhoenixAspirateur_VERSION_MAJOR 0)
set     (PhoenixAspirateur_VERSION_MINOR 1)

include(${GenericCmakeLists})

####################################################################
#   Library modules
####################################################################
# "Double syntax" nécessaire pour les projets en-dehors de ce dossier
# La source est à l'extérieur de ce dossier, mais la compilation s'effectue ici.
# EXCLUDE_FROM_ALL : ne pas compiler les targets des sous-projets par défaut
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../board-carte_kiwi
    ${CMAKE_CURRENT_BINARY_DIR}/board-carte_kiwi
    EXCLUDE_FROM_ALL)

####################################################################
#   Source
####################################################################
## Déclaration de la librairie aux projets qui utilisent celui-ci
# Déclaration des sources de la librairie
add_library(${PROJECT_NAME}Lib STATIC
    bumper.cpp
    fake_remote.cpp
    funny_action.cpp
    pilot.cpp
    reception.cpp
)

# Includes publics
target_include_directories(${PROJECT_NAME}Lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
target_link_libraries(${PROJECT_NAME}Lib INTERFACE
    m
)

# Librairie à linker
export(TARGETS ${PROJECT_NAME}Lib FILE Librairie.cmake)

include_directories(..
    $<TARGET_PROPERTY:PhoenixBoard_CarteKiwiLib,INTERFACE_INCLUDE_DIRECTORIES>
    )

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
add_executable(main_binary ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}Lib
    PhoenixBoard_CarteKiwiLib
    ${Toolchain_LFlags}
)
