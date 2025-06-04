#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <cstring>
#include <string>
#include <map>

#include "Vector2D.h"
#include "TextureManager.h"
#include "Collision.h"
#include "TileMap.h"

/**
 * @brief Class representing a hitbox for collision detection
 * 
 */
class Hitbox{
    public:

        Hitbox() : position(0,0), size(0,0), rect{0,0,0,0} {}

        Hitbox(Vector2D& _position, Vector2D& _size)
            : position(_position), size(_size) {
            rect = {static_cast<int>(_position.x), static_cast<int>(_position.y), static_cast<int>(_size.x), static_cast<int>(_size.y)};
        }

        /** GETTERS & SETTERS */
        const int getX() const { return position.x; }
        const int getY() const { return position.y; }

        const int getWidth() const { return size.x; }
        const int getHeight() const { return size.y; }
        SDL_Rect getRect() { return rect; }

        void setPosition(const Vector2D& _position){
            position = _position;
            rect.x = position.x;
            rect.y = position.y;
        }
        void setSize(Vector2D& _size){
            size = _size;
            rect.w = size.x;
            rect.h = size.y;
        }



    
    private:
        Vector2D position;
        Vector2D size;
        SDL_Rect rect;
};

/**
 * @brief Class representing an entity in the game
 * 
 */

class EntityManager;

class Entity{
private:
    int id;
    std::string name;
    Vector2D position;
    Vector2D size;
    std::string textureID;
    Hitbox hitbox;


public:
    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity() : id(0), name("NULL"), position(0,0), size(0,0), textureID("NULL") {
        hitbox = Hitbox();
    }

    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity(int _id, std::string _name, Vector2D _position, Vector2D _size, std::string _textureID)
        : id(_id), name(_name), position(_position), size(_size), textureID(_textureID){
        hitbox = Hitbox(_position, _size);
    }

    /** GETTERS & SETTERS */
    int getId() {return id; }
    const std::string& getName() { return name; }
    const Vector2D& getPosition() const { return position; }
    const Vector2D& getSize() const { return size; }
    const Hitbox& getHitbox() const { return hitbox; }
    std::string getTextureID() const {
        return textureID;
    }

    void setId(int _id) { id = _id; }
    void setPosition(const Vector2D& _position){position = _position;hitbox.setPosition(position);}
    void setTextureID(const std::string& _textureID) { textureID = _textureID; }


    void render(SDL_Renderer* renderer) {
        if(!textureID.empty()){
            TextureManager::getInstance()->drawTexture(getTextureID(), renderer, getPosition(), getSize());
        }
    }

    void move(Vector2D& direction, float speed){
        Vector2D newPosition = getPosition() + direction.normalize() * speed;

        Hitbox newHitbox = getHitbox();
        newHitbox.setPosition(newPosition);

        if(direction.magnitude() > 0.0f && !checkMapEntityCollision(newHitbox, *TileMap::getInstance())){
            setPosition(newPosition);
        }
    }
};

class EntityManager {
    private:
        static EntityManager* instance;
        EntityManager() = default;

        std::map<int, Entity> entityMap;
    
    public:
        ~EntityManager() {
            entityMap.clear();
        }

        static EntityManager* getInstance(){
            if (instance == nullptr) {
                instance = new EntityManager();
            }
            return instance;
        }

        void addEntity(Entity& entity) {
            int id = entity.getId();
            if (entityMap.find(id) == entityMap.end()) {
                entityMap[id] = std::move(entity);
            } else {
                id = entityMap.size() + 1; // Generar un nuevo ID si ya existe
                entityMap[id] = std::move(entity);
            }
        }

        Entity* getEntity(int id) {
            if (entityMap.find(id) != entityMap.end()) {
                return &entityMap[id];
            }
            return nullptr; // Retorna nullptr si no se encuentra la entidad
        }



};

#endif