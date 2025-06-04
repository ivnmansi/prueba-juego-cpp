#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#include "inc/Entity.h"
#include "inc/Player.h"
#include "inc/TextureManager.h"
#include "inc/TileMap.h"
#include "inc/Config.h"


TextureManager* TextureManager::instance = nullptr;

int main(int argc, char** argv){

    srand(time(NULL));

    /* INIT VIDEO SYSTEM */
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        printf("Error: SDL_image failed to initialize\nSDL Error: '%s'\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    /* CREATE WINDOW */
    SDL_Window *window = SDL_CreateWindow(
        "PRUEBA",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    /*CREATE RENDER*/
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    /*------------------*/
    // Cargar todas las texturas
    TextureManager* textureManager = TextureManager::getInstance();
    if (!textureManager->loadTexturesFromDirectory("img", renderer)) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Cargar tilemap
    TileMap* tileMap = TileMap::getInstance();
    bool debug_mode = false;
    // mapa de prueba
    tileMap->loadMapFromFile("data/testmap.map", renderer);
    SDL_Log("nombre del mapa: %s", tileMap->getMapName().c_str());

    // cargar jugador
    Player* player = Player::getInstance();



    /*-------------------*/

    // Bucle principal
    int quit = 0;
    SDL_Event e;
    // Obtener el estado del teclado
    const Uint8* keyState;

    while (!quit) {
        // Manejar eventos
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN && keyState[SDL_SCANCODE_M]) {
                debug_mode = !debug_mode;
            }
        }

        // Obtener el estado del teclado
        keyState = SDL_GetKeyboardState(NULL);

        // actualizar estado del jugador
        Vector2D direction(0, 0);

        // Movimiento del sprite con el teclado
        if (keyState[SDL_SCANCODE_UP]) {
            direction += Vector2D(0, -1);
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            direction += Vector2D(0, 1);
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            direction += Vector2D(-1, 0);
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            direction += Vector2D(1, 0);
        }

        // Mover el jugador
        player->move(direction);

        


       // Limpiar pantalla y establecer el color del fondo (blanco)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color blanco
        SDL_RenderClear(renderer);

        if(debug_mode){
            tileMap->render(renderer);
        }

        // Renderizar la textura en la posición del sprite
        player->render(renderer);

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
        // Retraso para no consumir mucho CPU
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // Limpiar y cerrar SDL
    // Revisar después si hay leakeos de memoria
    textureManager->clearAllTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    

    return 0;
}