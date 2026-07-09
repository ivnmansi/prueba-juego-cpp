#include "../inc/Scene.h"

Scene* Scene::instance = nullptr;

void Scene::render(SDL_Renderer* renderer, EntityManager* entityManager, bool debugMode) {
    // Limpiar pantalla y establecer el color del fondo (blanco)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color blanco
    SDL_RenderClear(renderer);

    // Renderizar el mapa
    currentMap->renderBackground(renderer);
    currentMap->renderLayersBelowPlayer(renderer, debugMode);
    entityManager->renderEntities(renderer);
    currentMap->renderLayersAbovePlayer(renderer);
}