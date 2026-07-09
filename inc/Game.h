#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <algorithm>

#include "../inc/InputManager.h"
#include "../inc/Entity.h"
#include "../inc/Player.h"
#include "../inc/Scene.h"
#include "../inc/Config.h"

class Game {
    public:
        static Game* getInstance();

        bool init();
        void run();
        void shutdown();
    
    private:
        Game() = default;
        static Game* instance;

        // SDL variables
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event;

        // Managers
        InputManager* inputManager = InputManager::getInstance();
        TextureManager* textureManager = TextureManager::getInstance();
        EntityManager* entityManager = EntityManager::getInstance();
        Scene* scene = Scene::getInstance();

        // Game variables
        float deltaTime;
        bool running = true;
        bool debugMode = false;

        // Game loop methods
        void HandleEvents();
        void Update(float deltaTime);
        void Render();

        void updateCamera();
};

#endif