#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


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
            std::string("player_down")  // TEXTURE ID
        ) {
            health = 100;               // HEALTH
            speed = 5;                  // SPEED
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
            }
            return instance;
        }

        void move(Vector2D& direction);

        void render(SDL_Renderer* renderer) {
            Entity::render(renderer);
        }


        
};

#endif