#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Entity.h"
#include "InputManager.h"


class Player : public Character {
    private:

        /**
         * @brief Construct the Player object (singleton)
         * 
         */
        Player() : Character(
            0,                          // ID
            std::string("Player"),      // NAME
            Vector2D(0,0),              // POSITION
            Vector2D(40,80),            // SIZE
            Sprite("player_down"),      // SPRITE
            Vector2D(20, 80),           // HITBOX SIZE
            Vector2D(10, 0),            // HITBOX OFFSET
            State::IDLE,                // STATE
            Direction::DOWN,            // DIRECTION
            100,                        // HEALTH
            200.0f                      // SPEED
        ) {
            SetupAnimations();
            animator.playAnimation("player_animation");
        }

        static Player* instance;
        
        void SetupAnimations() override;

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
        
        void updateTexture() override;
        Vector2D movementLogic() override;

};

#endif