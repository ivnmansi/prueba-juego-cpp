#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

/**
 * @brief Represents a character entity in the game (player, NPC, etc.)
 * 
 */
class Character : public Entity {
    public:
        /**
         * Character states
         */
        typedef enum {
            IDLE,
            WALKING,
            RUNNING,
            ATTACKING,
            HURT,
            DEAD
        } State;

        /*
        * Character directions
        */
        typedef enum {
            UP,
            UP_RIGHT,
            UP_LEFT,
            RIGHT,
            LEFT,
            DOWN,
            DOWN_RIGHT,
            DOWN_LEFT
        } Direction;

        /*
        * Atributes
        */
       State state;
       Direction direction;
       int health;
       float speed;

       /*
       * Constructor
       */
      Character();
      Character(
        int _id,                        // ID
        std::string _name,              // NAME
        Vector2D _position,             // POSITION
        Vector2D _size,                 // SIZE
        Sprite _sprite,                 // SPRITE
        const Vector2D& _hitboxSize,    // HITBOX SIZE
        const Vector2D& _hitboxOffset,  // HITBOX OFFSET
        State state,                    // STATE
        Direction direction,            // DIRECTION
        int health,                     // HEALTH
        float speed                     // SPEED
      );

      /*-------------
      *   Methods
      ---------------*/

     /**
      * @brief Moves the character and updates its direction based on the movement vector.
      * @param movement The movement vector.
      * @param deltaTime The time elapsed since the last frame.
      * @param tileMap The tile map for collision detection.
      */
     void move(const Vector2D& movement, float deltaTime, const TileMap& tileMap);

     /**
      * @brief Updates the character's texture based on its current state and direction.
      */
     virtual void updateTexture() = 0;
     virtual Vector2D movementLogic() = 0;
     virtual void SetupAnimations() = 0;

     void onUpdate(float deltaTime, const TileMap& tileMap) override;

    private:
        
};

#endif