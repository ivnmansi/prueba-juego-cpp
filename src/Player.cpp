#include "../inc/Player.h"

Player* Player::instance = nullptr;

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void Player::move(Vector2D& direction, float deltaTime, const TileMap& tileMap){
    
    Entity::move(direction, speed, deltaTime, tileMap);
    
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

void Player::update(float deltaTime, const TileMap& tileMap){
    Vector2D direction;

    auto& input = *InputManager::getInstance();

    if (input.isKeyHeld(SDL_SCANCODE_UP))
        direction.y--;

    if (input.isKeyHeld(SDL_SCANCODE_DOWN))
        direction.y++;

    if (input.isKeyHeld(SDL_SCANCODE_LEFT))
        direction.x--;

    if (input.isKeyHeld(SDL_SCANCODE_RIGHT))
        direction.x++;

    move(direction, deltaTime, tileMap);
}