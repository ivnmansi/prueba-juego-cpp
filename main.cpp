#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "inc/Entity.h"
#include "inc/Player.h"
#include "inc/Object.h"
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
    // Cargar textura del jugador (prueba)
    // * Hacer menos tediosa la carga de texturas después
    // * Ver como usar spritesheets
    TextureManager* textureManager = TextureManager::getInstance();
    if (
        !textureManager->loadTexture("player_down", "img/player_down.bmp", renderer)
        || !textureManager->loadTexture("player_up", "img/player_up.bmp", renderer)
        || !textureManager->loadTexture("player_left", "img/player_left.bmp", renderer)
        || !textureManager->loadTexture("player_right", "img/player_right.bmp", renderer)
        || !textureManager->loadTexture("player_down_left", "img/player_down_left.bmp", renderer)
        || !textureManager->loadTexture("player_down_right", "img/player_down_right.bmp", renderer)
        || !textureManager->loadTexture("player_up_left", "img/player_up_left.bmp", renderer)
        || !textureManager->loadTexture("player_up_right", "img/player_up_right.bmp", renderer)
        || !textureManager->loadTexture("tile_texture1", "img/tilemaptest.bmp", renderer)
    ) {
        printf("Error: Failed to load texture\nSDL Error: '%s'\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Cargar tilemap (prueba)
    TileMap* tileMap = TileMap::getInstance();
    // tiles de prueba aleatorios
    for(int i=0; i < GRID_WIDTH; i++){
        for(int j=0; j < GRID_HEIGHT; j++){
            int random = rand() % TILE_TYPE_NUM;
            tileMap->setTile(i, j, random);
        }
    }

    // cargar jugador
    Player* player = Player::getInstance();

    // prueba objeto (rectangulo)
    Object* object = new Object(1, "Test Object", 100, 100, 50, 50, "player_down");


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
        }

        // Obtener el estado del teclado
        keyState = SDL_GetKeyboardState(NULL);

        // actualizar estado del jugador
        int dx = 0, dy = 0;

        // Movimiento del sprite con el teclado
        if (keyState[SDL_SCANCODE_UP]) {
            dy -= 1;
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            dy += 1;
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            dx -= 1;
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            dx += 1;
        }

        // Mover el jugador
        player->move(dx, dy);



       // Limpiar pantalla y establecer el color del fondo (blanco)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color blanco
        SDL_RenderClear(renderer);

        // Renderizar el tilemap
        tileMap->render(renderer);

        // Renderizar la textura en la posición del sprite
        player->render(renderer);
        // Renderizar el objeto
        object->render(renderer);

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
        // Retraso para no consumir mucho CPU
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // Limpiar y cerrar SDL
    // Revisar después si hay leakeos de memoria
    Player::getInstance()->~Player();
    delete Player::getInstance();
    textureManager->clearAllTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}