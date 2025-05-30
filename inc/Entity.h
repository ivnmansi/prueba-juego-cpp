#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <cstring>
#include <string>
#include <map>

#include "TextureManager.h"

/**
 * @brief Class representing a hitbox for collision detection
 * 
 */
class Hitbox{
    public:
        /**
         * @brief Construct a new Hitbox object
         * 
         * @param _x 
         * @param _y 
         * @param _width 
         * @param _height 
         */
        Hitbox() : x(0), y(0), width(0), height(0) {
            rect = {0,0,0,0};
        }

        /**
         * @brief Construct a new Hitbox object
         * 
         * @param _x 
         * @param _y 
         * @param _width 
         * @param _height 
         */
        Hitbox(int _x, int _y, int _width, int _height)
            : x(_x), y(_y), width(_width), height(_height) {
            rect = {x, y, width, height};
        }

        /** GETTERS & SETTERS */
        int getX() { return x; }
        int getY() { return y; }
        int getWidth() { return width; }
        int getHeight() { return height; }
        SDL_Rect getRect() { return rect; }

        void setX(int _x) { x = _x; rect.x = x; }
        void setY(int _y) { y = _y; rect.y = y; }
        void setWidth(int _width) { width = _width; rect.w = width; }
        void setHeight(int _height) { height = _height; rect.h = height; }

    
    private:
        int x, y;
        int width, height;
        SDL_Rect rect;
};

/**
 * @brief Class representing an entity in the game
 * 
 */
class Entity{
private:
    int id;
    std::string name;
    int x, y;
    int width, height;
    int speed;
    Hitbox hitbox;
    SDL_Texture* texture;
    std::string textureID;
    int health;

public:
    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity() : id(0), name(nullptr), x(0), y(0), width(0), height(0), speed(0), textureID(""), health(100) {
        hitbox = Hitbox();
    }

    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity(int _id, std::string _name, int _x, int _y, int _width, int _height, int _speed, int _health, std::string _textureID)
        : id(_id), name(_name), x(_x), y(_y), width(_width), height(_height), speed(_speed), health(_health), textureID(_textureID){
        hitbox = Hitbox(x, y, width, height);
    }

    /**
     * @brief Destroy the Entity object
     * 
     */
    ~Entity() {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }

    /** GETTERS & SETTERS */
    int getId() {return id; }
    const std::string& getName() { return name; }
    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getSpeed() { return speed; }
    int getHealth() { return health; }
    Hitbox& getHitbox() { return hitbox; }

    void setId(int _id) { id = _id; }
    void setX(int _x){x = _x;hitbox.setX(_x);}
    void setY(int _y){y = _y;hitbox.setY(_y);}
    void setTextureID(const std::string& _textureID) { textureID = _textureID; }
    void setHealth(int _health) { health = _health; }

    /** MÉTODOS */
    void move(int dx, int dy){
        x += dx * speed;
        y += dy * speed;
        hitbox.setX(x);
        hitbox.setY(y);
    }

    std::string getTextureID() const {
        return textureID;
    }

    void render(SDL_Renderer* renderer) {
        if(!textureID.empty()){
            TextureManager::getInstance()->drawTexture(getTextureID(), renderer, getX(), getY(), getWidth(), getHeight());
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