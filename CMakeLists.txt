cmake_minimum_required(VERSION 3.16)

project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraires" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES

    "src/main.cpp"

    "src/MainWindow.cpp"
    "src/headers/MainWindow.h"

    "src/Game.cpp"
    "src/headers/Game.h"

    "src/GameWorld.cpp"
    "src/headers/GameWorld.h"

    "src/EntityManager.cpp"
    "src/headers/EntityManager.h"

    "src/GameEngine.cpp"
    "src/headers/GameEngine.h"
)

add_executable(Chess ${SOURCE_FILES})
target_link_libraries(Chess PRIVATE sfml-graphics)
target_compile_features(Chess PRIVATE cxx_std_17)

# add precomplide headers
target_precompile_headers(Chess PRIVATE src/stdafx.h)

# add all files wich must be copyied in build dir
set(COPY_FILES "${CMAKE_SOURCE_DIR}/src/img/ChessPiecesArray.png")

# TODO : copy files in new folder in build files


# COMAND TO COPY DIRECTORY
#add_custom_target(copy_assets
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../assets ${CMAKE_CURRENT_BINARY_DIR}/assets
#)

# Copy font file to build dir
add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${COPY_FILES} $<TARGET_FILE_DIR:Chess>
    COMMENT "Copying files to output directory"
)


if(WIN32)
    add_custom_command(
        TARGET Chess
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Chess>
        VERBATIM)
endif()