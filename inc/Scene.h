#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "Map.h"
#include "Camera.h"

class Scene {
    private:
        static Scene* instance;

        Camera camera;
        Map* currentMap;

        Scene() : camera(Vector2D(0, 0), Vector2D(SCREEN_WIDTH, SCREEN_HEIGHT)), currentMap(nullptr) {}
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

        Camera& getCamera() {
            return camera;
        }

        void render(SDL_Renderer* renderer, Camera& camera, EntityManager* entityManager, bool debugMode);
};

#endif