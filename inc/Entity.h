#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <cstring>
#include <string>
#include <map>
#include <utility>

#include "Vector2D.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Sprite.h"

class TileMap;
class Player;

typedef enum {
    ENTITY_PLAYER,
    ENTITY_TEST
} EntityType;

/**
 * @brief Class representing a hitbox for collision detection
 * 
 */
class Hitbox{
    public:

        Hitbox() : position(0,0), size(0,0), offset(0,0), rect{0,0,0,0} {}

        Hitbox(const Vector2D& _position, const Vector2D& _size, const Vector2D& _offset = Vector2D(0, 0))
            : position(_position), size(_size), offset(_offset) {
            rect = {
                static_cast<int>(_position.x + _offset.x),
                static_cast<int>(_position.y + _offset.y),
                static_cast<int>(_size.x),
                static_cast<int>(_size.y)
            };
        }

        /** GETTERS & SETTERS */
        const int getX() const { return rect.x; }
        const int getY() const { return rect.y; }

        const int getWidth() const { return size.x; }
        const int getHeight() const { return size.y; }
        SDL_Rect getRect() { return rect; }

        void setPosition(const Vector2D& _position){
            position = _position;
            rect.x = position.x + offset.x;
            rect.y = position.y + offset.y;
        }
        void setSize(const Vector2D& _size){
            size = _size;
            rect.w = size.x;
            rect.h = size.y;
        }

        void setOffset(const Vector2D& _offset) {
            offset = _offset;
            rect.x = position.x + offset.x;
            rect.y = position.y + offset.y;
        }

        void setBounds(const Vector2D& _position, const Vector2D& _size, const Vector2D& _offset = Vector2D(0, 0)) {
            position = _position;
            size = _size;
            offset = _offset;
            rect = {
                static_cast<int>(position.x + offset.x),
                static_cast<int>(position.y + offset.y),
                static_cast<int>(size.x),
                static_cast<int>(size.y)
            };
        }

        void update(float deltaTime, const TileMap& tileMap);



    
    private:
        Vector2D position;
        Vector2D size;
        Vector2D offset;
        SDL_Rect rect;
};

/**
 * @brief Class representing an entity in the game
 * 
 */

class EntityManager;

class Entity{
protected:
    Sprite sprite;
    Animator animator;

private:
    int id;
    std::string name;
    EntityType type;
    Vector2D position;
    Vector2D size;
    Hitbox hitbox;
    Vector2D hitboxSize;
    Vector2D hitboxOffset;

public:
    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity() :
        sprite(),
        animator(),
        id(0),
        name("NULL"),
        type(ENTITY_TEST),
        position(0,0),
        size(0,0),
        hitbox(),
        hitboxSize(0,0),
        hitboxOffset(0,0)
    {

        hitboxSize = size;
        hitboxOffset = Vector2D(0, 0);
        hitbox = Hitbox();
    }

    /**
     * @brief Construct a new Entity object
     * 
     */
    Entity(
        int _id,
        std::string _name,
        Vector2D _position,
        Vector2D _size,
        Sprite _sprite,
        const Vector2D& _hitboxSize = Vector2D(0,0),
        const Vector2D& _hitboxOffset = Vector2D(0,0)
    )
    :
        sprite(_sprite),
        animator(),
        id(_id),
        name(_name),
        type(ENTITY_TEST),
        position(_position),
        size(_size),
        hitbox(_position, _hitboxSize, _hitboxOffset),
        hitboxSize(_hitboxSize),
        hitboxOffset(_hitboxOffset)
        {
            if(hitboxSize.x <= 0 || hitboxSize.y <= 0)
            {
                hitboxSize = _size;
            }
        }

    /** GETTERS & SETTERS */
    int getId() {return id; }
    const std::string& getName() { return name; }
    EntityType getType() { return type; }
    const Vector2D& getPosition() const { return position; }
    const Vector2D& getSize() const { return size; }
    const Hitbox& getHitbox() const { return hitbox; }
    Sprite& getSprite() { return sprite; }

    void setId(int _id) { id = _id; }
    void setPosition(const Vector2D& _position){position = _position;hitbox.setBounds(position, hitboxSize, hitboxOffset);}
    void setSprite(const std::string& _textureID) { sprite.setTexture(_textureID); }
    void setHitbox(const Hitbox& _hitbox) { hitbox = _hitbox; }


    void render(SDL_Renderer* renderer, const Camera& camera);

    void move(const Vector2D& direction, float speed, float dt, const TileMap& tileMap);

    void update(float deltaTime, const TileMap& tileMap);

    protected:
        virtual void onUpdate(float deltaTime, const TileMap& tileMap) {}
        virtual void SetupAnimations() {}
};

/**
 * @brief Singleton class to manage all entities in the game
 * 
 */
class EntityManager {
    private:

        static EntityManager* instance;
        EntityManager() = default;

        std::map<int, Entity*> entityMap;
    
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

        void addEntity(Entity& entity);
        Entity* getEntity(int id);
        void removeEntity(int id);

        Entity* createEntity(EntityType type, Vector2D position);

        void updateEntities(float deltaTime, const TileMap& tileMap);
        void renderEntities(SDL_Renderer* renderer, const Camera& camera);

        void clearEntities();

        void printEntities();
};

#endif