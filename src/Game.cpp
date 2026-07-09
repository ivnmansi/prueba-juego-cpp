#include "../inc/Game.h"

Game* Game::instance = nullptr;

Game* Game::getInstance(){
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

/**
 * @brief Inits SDL libraries
 * 
 * @return true 
 * @return false 
 */
bool Game::init(){
    /* INIT VIDEO SYSTEM */
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        printf("Error: SDL_image failed to initialize\nSDL Error: '%s'\n", IMG_GetError());
        SDL_Quit();
        return false;
    }

    /* CREATE WINDOW */
    this->window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    /*CREATE RENDER*/
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    /*LOAD TEXTURES*/
    if (!this->textureManager->loadTexturesFromDirectory("res/textures", this->renderer)) {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return false;
    }


    return true;
}

/**
 * @brief runs the main game loop
 * 
 */
void Game::run(){
    /* LOAD MAP */
    Map map;
    map.loadMapFromFile("res/levels/testmap.map", renderer);
    Player* player = Player::getInstance();
    entityManager->printEntities();

    /* HACER INPUTMANAGER */
    const Uint8* keyState;

    while (this->running) {
        // Manejar eventos
        while (SDL_PollEvent(&this->event) != 0) {
            if (this->event.type == SDL_QUIT) {
                this->running = false;
            }
            if (this->event.type == SDL_KEYDOWN && keyState[SDL_SCANCODE_M]) {
                this->debugMode = !this->debugMode;
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

        player->move(direction, map.getTileMap(0));

        scene->render(renderer, map, entityManager, this->debugMode);

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
        // Retraso para no consumir mucho CPU
        SDL_Delay(16); // Aproximadamente 60 FPS
    }
}

/**
 * @brief Shutdowns SDL libraries and cleans up resources
 * 
 */
void Game::shutdown(){
    textureManager->clearAllTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}