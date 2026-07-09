#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputManager.h"


class Player : public Entity {
    private:

        int health;
        float speed;

        /**
         * @brief Construct the Player object (singleton)
         * 
         */
        Player() : Entity(
            0,                          // ID
            std::string("Player"),      // NAME
            Vector2D(0,0),              // POSITION
            Vector2D(40,80),            // SIZE
            std::string("player_down"), // TEXTURE ID
            Vector2D(20, 80),           // HITBOX SIZE
            Vector2D(10, 0)              // HITBOX OFFSET
        ) {
            health = 100;               // HEALTH
            speed = 400;                  // SPEED
        }

        static Player* instance;

        

    public:
        /**
         * @brief Get the Instance object
         * 
         * @return Player* 
         */
        static Player* getInstance() {
            if (instance == nullptr) {
                instance = new Player();
                EntityManager::getInstance()->addEntity(*instance);
            }
            return instance;
        }

        void move(Vector2D& direction, float deltaTime, const TileMap& tileMap);

        void render(SDL_Renderer* renderer) {
            Entity::render(renderer);
        }

        void update(float deltaTime, const TileMap& tileMap) override;

};

#endif