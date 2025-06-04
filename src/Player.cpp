#include "../inc/Player.h"

Player* Player::instance = nullptr;

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void Player::move(Vector2D& direction){
    
    Entity::move(direction, speed);
    
    if(direction.x > 0 && direction.y == 0){
        setTextureID("player_right");
    }
    else if(direction.x < 0 && direction.y == 0){
        setTextureID("player_left");
    }
    else if(direction.y > 0 && direction.x == 0){
        setTextureID("player_down");
    }
    else if(direction.y < 0 && direction.x == 0){
        setTextureID("player_up");
            }
    else if(direction.x > 0 && direction.y > 0){
        setTextureID("player_down_right");
    }
    else if(direction.x < 0 && direction.y > 0){
        setTextureID("player_down_left");
    }
    else if(direction.x > 0 && direction.y < 0){
        setTextureID("player_up_right");
    }
    else if(direction.x < 0 && direction.y < 0){
        setTextureID("player_up_left");
    }
}