#include "../inc/Player.h"


Player* Player::instance = nullptr;


void Player::updateTexture(){
    if(state == IDLE){
        if(direction == DOWN)
            getSprite().setTexture("player_down_idle");
        else if(direction == UP)
            getSprite().setTexture("player_up_idle");
        else if(direction == LEFT)
            getSprite().setTexture("player_left_idle");
        else if(direction == RIGHT)
            getSprite().setTexture("player_right_idle");
        else if(direction == DOWN_RIGHT)
            getSprite().setTexture("player_down_right_idle");
        else if(direction == DOWN_LEFT)
            getSprite().setTexture("player_down_left_idle");
        else if(direction == UP_RIGHT)
            getSprite().setTexture("player_up_right_idle");
        else if(direction == UP_LEFT)
            getSprite().setTexture("player_up_left_idle");
    }
    if(state == WALKING){
        if(direction == DOWN)
            getSprite().setTexture("player_down_walking");
        else if(direction == UP)
            getSprite().setTexture("player_up_walking");
        else if(direction == LEFT)
            getSprite().setTexture("player_left_walking");
        else if(direction == RIGHT)
            getSprite().setTexture("player_right_walking");
        else if(direction == DOWN_RIGHT)
            getSprite().setTexture("player_down_right_walking");
        else if(direction == DOWN_LEFT)
            getSprite().setTexture("player_down_left_walking");
        else if(direction == UP_RIGHT)
            getSprite().setTexture("player_up_right_walking");
        else if(direction == UP_LEFT)
            getSprite().setTexture("player_up_left_walking");
    }
}


Vector2D Player::movementLogic(){
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
        state = IDLE;
    }
    else {
        state = WALKING;
    }

    return movement;
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