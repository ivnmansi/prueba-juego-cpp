#include "../inc/Entity.h"
#include "../inc/TileMap.h"
#include <iostream>

EntityManager* EntityManager::instance = nullptr;

void EntityManager::addEntity(Entity& entity) {
    int id = entity.getId();
    if (entityMap.find(id) == entityMap.end()) {
        entityMap[id] = &entity;
    }
	else {
        id = entityMap.size() + 1; // Generar un nuevo ID si ya existe
        entity.setId(id);
        entityMap[id] = &entity;
    }
}

Entity* EntityManager::getEntity(int id) {
    if (entityMap.find(id) != entityMap.end()) {
        return entityMap[id];
    }
    return nullptr; // Retorna nullptr si no se encuentra la entidad
}

void EntityManager::removeEntity(int id) {
    entityMap.erase(id);
}

void EntityManager::updateEntities(float deltaTime, const TileMap& tileMap) {
    for (auto& pair : entityMap) {
        // do something
    }
}

void EntityManager::renderEntities(SDL_Renderer* renderer) {
    for (auto& pair : entityMap) {
        if (pair.second != nullptr) {
            pair.second->render(renderer);
        }
    }
}

void Entity::render(SDL_Renderer* renderer) {
    if(!textureID.empty()){
        TextureManager::getInstance()->drawTexture(getTextureID(), renderer, getPosition(), getSize());
    }
}

void EntityManager::clearEntities() {
    entityMap.clear();
}

void EntityManager::printEntities() {
    for (auto& pair : entityMap) {
        if (pair.second != nullptr) {
            std::cout << "Entity ID: " << pair.first << ", Name: " << pair.second->getName() << std::endl;
        }
    }
}

 void Entity::move(Vector2D& direction, float speed, const TileMap& tileMap) {
	Vector2D newPosition = getPosition() + direction.normalize() * speed;

	Hitbox newHitbox = getHitbox();
	newHitbox.setPosition(newPosition);

	if (direction.magnitude() > 0.0f && !checkMapEntityCollision(newHitbox, tileMap)) {
		setPosition(newPosition);
	}
}