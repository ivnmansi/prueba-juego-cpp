#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "Map.h"

class Scene {
    private:
        static Scene* instance;

        Map* currentMap;

        Scene() = default;
        ~Scene() = default;
    public:
        static Scene* getInstance() {
            if (instance == nullptr) {
                instance = new Scene();
            }
            return instance;
        }

        void setMap(Map* map) {
            currentMap = map;
        }

        Map& getMap() {
            return *currentMap;
        }

        void render(SDL_Renderer* renderer, EntityManager* entityManager, bool debugMode);
};

#endif