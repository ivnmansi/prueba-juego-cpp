#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "Player.h"
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

        void render(SDL_Renderer* renderer, Map& map, Player* player, bool debugMode) {
            // Limpiar pantalla y establecer el color del fondo (blanco)
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color blanco
            SDL_RenderClear(renderer);

            // Renderizar el mapa
            map.renderBackground(renderer);
            map.renderLayersBelowPlayer(renderer, debugMode);
            player->render(renderer);
            map.renderLayersAbovePlayer(renderer);
        }
};

#endif