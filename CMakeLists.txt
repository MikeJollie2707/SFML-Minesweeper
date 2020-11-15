cmake_minimum_required(VERSION 3.16)
project(Minesweeper
    VERSION 1.0
    DESCRIPTION "Minesweeper written in SFML"
    LANGUAGES CXX
)

add_executable(play
    src/game.cpp
    src/main.cpp
    src/tile.cpp
)

# Link SFML
#set(SFML_DIR /home/mikengo/Documents/Coding/C\(\+\+\)/C\+\+/SFML/SFML-2.5.1/build/)
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
target_link_libraries(play
    PUBLIC sfml-graphics
)

target_include_directories(play
    PUBLIC include
)
