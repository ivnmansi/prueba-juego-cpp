#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputManager.h"

/**
 * TODO: LAS ANIMACIONES POR MOVIMIENTO HAY QUE DEJARLAS MAS GENERICAS
 * PARA QUE FUNCIONE NO SOLO CON EL PLAYER
 * QUIZA HACER CLASS CHARACTER O ALGO ASI
 */

typedef enum {
    PLAYER_IDLE,
    PLAYER_WALKING,
    PLAYER_RUNNING
} State;

typedef enum {
    PLAYER_UP,
    PLAYER_UP_RIGHT,
    PLAYER_UP_LEFT,
    PLAYER_RIGHT,
    PLAYER_LEFT,
    PLAYER_DOWN,
    PLAYER_DOWN_RIGHT,
    PLAYER_DOWN_LEFT
} Direction;

class Player : public Entity {
    private:

        State state;
        Direction direction;

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
            Sprite("player_down"),      // SPRITE
            Vector2D(20, 80),           // HITBOX SIZE
            Vector2D(10, 0)             // HITBOX OFFSET
        ) {
            state = PLAYER_IDLE;         // STATE
            direction = PLAYER_DOWN;     // DIRECTION
            health = 100;                // HEALTH
            speed = 400;                 // SPEED

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
        
        void updateTexture();

        void move(Vector2D& direction, float deltaTime, const TileMap& tileMap);

        void render(SDL_Renderer* renderer, const Camera& camera) {
            Entity::render(renderer, camera);
        }

        void onUpdate(float deltaTime, const TileMap& tileMap) override;

};

#endif