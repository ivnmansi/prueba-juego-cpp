#include "../inc/Game.h"

Game* Game::instance = nullptr;

Game* Game::getInstance(){
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::HandleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            running = false;
    }

    inputManager->update();
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
    this->renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void Game::Update(float dt)
{
    entityManager->updateEntities(dt, Scene::getInstance()->getMap().getTileMap(0));

    if (inputManager->isKeyPressed(SDL_SCANCODE_M))
        debugMode = !debugMode;
}

void Game::Render()
{
    // Renderizar el mapa y las entidades
    scene->render(renderer, entityManager, debugMode);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);
}

/**
 * @brief runs the main game loop
 * 
 */
void Game::run(){
    /* LOAD MAP */
    Map map;
    map.loadMapFromFile("res/levels/testmap.map", renderer);
    Scene::getInstance()->setMap(&map);

    entityManager->printEntities();

    Uint64 last = SDL_GetPerformanceCounter();
    while (this->running) {
        // delta time calculation
        Uint64 now = SDL_GetPerformanceCounter();
        deltaTime = (float)(now - last) / SDL_GetPerformanceFrequency();
        last = now;

        // Manejar eventos
        HandleEvents();

        // Actualizar el juego
        Update(deltaTime);

        // Renderizar el juego
        Render();
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