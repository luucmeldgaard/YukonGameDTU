//
// Created by LuucM on 28-04-2023.
//

#include "sdlwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

int closeSDLWindow(SDL_Window* window) {

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

}