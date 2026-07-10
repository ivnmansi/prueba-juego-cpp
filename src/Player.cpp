#include "../inc/Player.h"


Player* Player::instance = nullptr;

// LO A CONTINUACION ESTA FEISIMO. HAY QUE REFACTORIZARLO EN UN FUTURO Y DEJARLO GENERICO PARA UN CLASS CHARACTER

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void Player::move(Vector2D& movement, float deltaTime, const TileMap& tileMap){
    Entity::move(movement, speed, deltaTime, tileMap);

    if(movement.x > 0 && movement.y == 0)
        direction = PLAYER_RIGHT;
    else if(movement.x < 0 && movement.y == 0)
        direction = PLAYER_LEFT;
    else if(movement.y > 0 && movement.x == 0)
        direction = PLAYER_DOWN;
    else if(movement.y < 0 && movement.x == 0)
        direction = PLAYER_UP;
    else if(movement.x > 0 && movement.y > 0)
        direction = PLAYER_DOWN_RIGHT;
    else if(movement.x < 0 && movement.y > 0)
        direction = PLAYER_DOWN_LEFT;
    else if(movement.x > 0 && movement.y < 0)
        direction = PLAYER_UP_RIGHT;
    else if(movement.x < 0 && movement.y < 0)
        direction = PLAYER_UP_LEFT;

    updateTexture();
}

void Player::updateTexture(){
    if(state == PLAYER_IDLE){
        if(direction == PLAYER_DOWN)
            getSprite().setTexture("player_down_idle");
        else if(direction == PLAYER_UP)
            getSprite().setTexture("player_up_idle");
        else if(direction == PLAYER_LEFT)
            getSprite().setTexture("player_left_idle");
        else if(direction == PLAYER_RIGHT)
            getSprite().setTexture("player_right_idle");
        else if(direction == PLAYER_DOWN_RIGHT)
            getSprite().setTexture("player_down_right_idle");
        else if(direction == PLAYER_DOWN_LEFT)
            getSprite().setTexture("player_down_left_idle");
        else if(direction == PLAYER_UP_RIGHT)
            getSprite().setTexture("player_up_right_idle");
        else if(direction == PLAYER_UP_LEFT)
            getSprite().setTexture("player_up_left_idle");
    }
    if(state == PLAYER_WALKING){
        if(direction == PLAYER_DOWN)
            getSprite().setTexture("player_down_walking");
        else if(direction == PLAYER_UP)
            getSprite().setTexture("player_up_walking");
        else if(direction == PLAYER_LEFT)
            getSprite().setTexture("player_left_walking");
        else if(direction == PLAYER_RIGHT)
            getSprite().setTexture("player_right_walking");
        else if(direction == PLAYER_DOWN_RIGHT)
            getSprite().setTexture("player_down_right_walking");
        else if(direction == PLAYER_DOWN_LEFT)
            getSprite().setTexture("player_down_left_walking");
        else if(direction == PLAYER_UP_RIGHT)
            getSprite().setTexture("player_up_right_walking");
        else if(direction == PLAYER_UP_LEFT)
            getSprite().setTexture("player_up_left_walking");
    }
}

void Player::onUpdate(float deltaTime, const TileMap& tileMap){
    Vector2D movement;

    auto& input = *InputManager::getInstance();

    if (input.isKeyHeld(SDL_SCANCODE_UP))
        movement.y--;

    if (input.isKeyHeld(SDL_SCANCODE_DOWN))
        movement.y++;

    if (input.isKeyHeld(SDL_SCANCODE_LEFT))
        movement.x--;

    if (input.isKeyHeld(SDL_SCANCODE_RIGHT))
        movement.x++;

    if (movement.x == 0 && movement.y == 0){
        state = PLAYER_IDLE;
    }
    else {
        state = PLAYER_WALKING;
    }

    move(movement, deltaTime, tileMap);
}

// EN UN FUTURO QUE SE LEA ESTO QUIZA DE UN JSON
void Player::SetupAnimations() {

    animator.addAnimation("player_animation", std::make_unique<Animation>(
        3,          // frameCount
        40,         // frameWidth
        80,         // frameHeight
        0.5f,       // frameDuration
        0,          // startX
        0           // startY
    ));

}