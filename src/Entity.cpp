#include "../inc/Entity.h"
#include "../inc/TileMap.h"
#include "../inc/Player.h"
#include <iostream>

EntityManager* EntityManager::instance = nullptr;

/**
 * @brief Adds an entity to the entity manager. If the entity's ID already exists, it generates a new ID for the entity and adds it to the map.
 * 
 * @param entity 
 */
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

/**
 * @brief Returns the entity with the given ID. If the entity doesn't exist, it returns nullptr.
 * 
 * @param id Id of the entity to get
 * @return Entity* Pointer to the entity with the given ID, or nullptr if it doesn't exist
 */
Entity* EntityManager::getEntity(int id) {
    if (entityMap.find(id) != entityMap.end()) {
        return entityMap[id];
    }
    return nullptr; // Retorna nullptr si no se encuentra la entidad
}

/**
 * @brief Removes an entity from the entity manager by its ID. If the entity doesn't exist, it does nothing.
 * 
 * @param id Id of the entity to remove
 */
void EntityManager::removeEntity(int id) {
    entityMap.erase(id);
}

Entity* EntityManager::createEntity(EntityType type, Vector2D position) {
    if(type == ENTITY_PLAYER){
        Player* player = Player::getInstance();
        player->setPosition(position);
        // Ensure player is registered in the manager
        if (entityMap.find(player->getId()) == entityMap.end()) {
            addEntity(*player);
        }
        return player;
    }

    if(type == ENTITY_TEST){
        Entity* e = new Entity(0, std::string("TestEntity"), position, Vector2D(16,16), std::string("test"));
        addEntity(*e);
        return e;
    }

    return nullptr;
}

/**
 * @brief Will update all entities in the entity manager
 * 
 * @param deltaTime  Time elapsed since the last update, in seconds
 * @param tileMap 
 */
void EntityManager::updateEntities(float deltaTime, const TileMap& tileMap) {
    for (auto& pair : entityMap) {
        if (pair.second != nullptr) {
            pair.second->update(deltaTime, tileMap);
        }
    }
}

/**
 * @brief Renders all entities in the entity manager using the provided SDL_Renderer.
 * 
 * @param renderer 
 */
void EntityManager::renderEntities(SDL_Renderer* renderer, const Camera& camera) {
    for (auto& pair : entityMap) {
        if (pair.second != nullptr) {
            pair.second->render(renderer, camera);
        }
    }
}

/**
 * @brief Renders the entity using the provided SDL_Renderer. If the entity has a valid texture ID, it draws the texture at the entity's position and size.
 * 
 * @param renderer 
 * @param camera 
 */
void Entity::render(SDL_Renderer* renderer, const Camera& camera) {
    if(!textureID.empty()){
        TextureManager::getInstance()->drawTexture(getTextureID(), renderer, camera.worldToScreen(getPosition()), getSize());
    }
}

/**
 * @brief Clears all entities from the entity manager. This function removes all entities from the internal map, effectively resetting the entity manager.
 * 
 */
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

/**
 * @brief Moves the entity in the specified direction with the given speed, checking for collisions with the tile map. If there is no collision, it updates the entity's position.
 * 
 * @param direction 
 * @param speed 
 * @param tileMap 
 */
void Entity::move(Vector2D& direction, float speed, float dt, const TileMap& tileMap){
    if (direction.magnitude() == 0.0f)
        return;

    Vector2D displacement = direction.normalize() * speed * dt;

    Vector2D newPosition = getPosition() + displacement;

    Hitbox newHitbox = getHitbox();
    newHitbox.setPosition(newPosition);

    if (!checkMapEntityCollision(newHitbox, tileMap))
    {
        setPosition(newPosition);
    }
}