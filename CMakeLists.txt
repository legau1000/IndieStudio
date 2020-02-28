cmake_minimum_required(VERSION 3.11)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(Errors/)
include_directories(include/)
include_directories(include/block)
include_directories(include/bonus)
include_directories(include/def)
include_directories(include/env)
include_directories(include/graphic)
include_directories(src/)
include_directories(src/save/)
include_directories(include/save/)
include_directories(src/Part/Menu/)
include_directories(src/Part/Game/maps/Block/Bonus)
include_directories(include/Part)
include_directories(include/Part/Game/maps)
include_directories(include/Part/Game/maps/block)
include_directories(include/Part/Game/maps/block/bonus)
include_directories(include/Part/Game/player)
include_directories(include/Part/Game/)
include_directories(include/Part/Menu)
include_directories(include/multiplayer)
include_directories(include/Part)
include_directories(irrlicht)
include_directories(irrlicht/include)
include_directories(src/Part/Menu/PartMenu/)


set(CMAKE_MODULE_PATH "./test/") # le path pour trouver le cmake
include(test/FindIrrlicht.cmake)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
set(Include_part_DIR "./include/Part/")
set(Include_game_DIR "./include/Part/Game/")
set(Include_map_DIR "./include/Part/Game/maps/")
set(Include_mapblock_DIR "./include/Part/Game/maps/block/")
set(Include_mapbonus_DIR "./include/Part/Game/maps/block/bonus/")
set(Include_player_DIR "./include/Part/Game/player/")
set(Include_menu_DIR "./include/Part/Menu/")
set(Include_multiplayer_DIR "./include/multiplayer/")
set(Include_def_DIR "./include/def/")
set(Include_env_DIR "./include/env/")
set(Include_graphic_DIR "./include/graphic/")
set(Include_partMenu_DIR "./include/Part/Menu/")
set(Include_save_DIR "./include/save/")

set(All_DOC
        ${Include_part_DIR}
        ${Include_game_DIR}
        ${Include_map_DIR}
        ${Include_player_DIR}
        ${Include_def_DIR}
        ${Include_bonus_DIR}
        ${Include_block_DIR}
        ${Include_env_DIR}
        ${Include_mapblock_DIR}
        ${Include_menu_DIR}
        ${Include_graphic_DIR}
        ${Include_multiplayer_DIR}
        ${Include_mapbonus_DIR}
        ${Include_partMenu_DIR}
        ${Include_save_DIR}
        )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(bomberman
        Errors/Error.hpp
        ${All_DOC}
        src/save/save.cpp
        src/env/env.cpp
        src/graphic/Graphique.cpp
        src/Part/PreScene.cpp
        src/Part/Game/maps/BasicMap.cpp
        src/Part/Game/maps/Block/Bombe.cpp
        src/Part/Game/maps/Block/Animation.cpp
        src/Part/Game/maps/Block/Breakable.cpp
        src/Part/Game/maps/Block/Ground.cpp
        src/Part/Game/maps/Block/Metal.cpp
        src/Part/Game/maps/Block/Rock.cpp
        src/Part/Game/maps/Block/Bonus/BombeUp.cpp
        src/Part/Game/maps/Block/Bonus/SpeedUp.cpp
        src/Part/Game/maps/Block/Bonus/PowerUp.cpp
        src/Part/Game/player/Human.cpp
        src/Part/Game/player/ComputerAi.cpp
        src/Part/Game/Game.cpp
        src/Part/Menu/Menu.cpp
        src/Part/Menu/PartMenu/ChooseMap.cpp
        src/Part/Menu/PartMenu/Config.cpp
        src/Part/Menu/PartMenu/Credit.cpp
        src/Part/Menu/PartMenu/HowToPlay.cpp
        src/graphic/Sound.cpp
        src/Indie.cpp
        src/main.cpp)
target_link_libraries(bomberman sfml-graphics sfml-audio)

IF(Irrlicht_FOUND)
    include_directories(${Irrlicht_INCLUDE_DIRS})
    target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
ENDIF(Irrlicht_FOUND)

find_package(Threads REQUIRED)
find_library(Irrlicht_lib "./irrlicht/")
target_link_libraries(bomberman Threads::Threads)
