cmake_minimum_required(VERSION 3.23)
project(YukonGameDTU C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

# Create an executable target for your main program and link it to your library
add_executable(YukonGameDTU main.c)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)