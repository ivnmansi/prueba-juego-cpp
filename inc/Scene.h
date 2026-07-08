#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "Map.h"

class Scene {
    private:
        static Scene* instance;
        Scene() = default;
        ~Scene() = default;
    public:
        static Scene* getInstance() {
            if (instance == nullptr) {
                instance = new Scene();
            }
            return instance;
        }

        void render(SDL_Renderer* renderer, Map& map, EntityManager* entityManager, bool debugMode);
};

#endif