cmake_minimum_required(VERSION 3.23)
project(YukonGameDTU C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR libs/SDL/include)
set(SDL2_LIB_DIR libs/SDL/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR libs/SDL_Image/include)
set(SDL2_IMAGE_LIB_DIR libs/SDL_Image/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

# Create an executable target for your main program and link it to your library
add_executable(YukonGameDTU main.c card.h logic.c logic.h card.c
        sdlwindow.c sdlwindow.h printText.h printText.c
        inputChecks.h inputChecks.c undoRedo.h undoRedo.c)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)