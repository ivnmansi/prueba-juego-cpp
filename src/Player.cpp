#include "../inc/Player.h"

Player* Player::instance = nullptr;

void Player::move(int dx, int dy){
    if(!(Player::getX() + dx * Player::getSpeed() < 0 || 
       Player::getX() + dx * Player::getSpeed() + Player::getWidth() > 1280 ||
       Player::getY() + dy * Player::getSpeed() < 0 || 
       Player::getY() + dy * Player::getSpeed() + Player::getHeight() > 720)){
        Entity::move(dx, dy);
    }

    if(dx > 0 && dy == 0){
        setTextureID("player_right");
    }
    else if(dx < 0 && dy == 0){
        setTextureID("player_left");
    }
    else if(dy > 0 && dx == 0){
        setTextureID("player_down");
    }
    else if(dy < 0 && dx == 0){
        setTextureID("player_up");
            }
    else if(dx > 0 && dy > 0){
        setTextureID("player_down_right");
    }
    else if(dx < 0 && dy > 0){
        setTextureID("player_down_left");
    }
    else if(dx > 0 && dy < 0){
        setTextureID("player_up_right");
    }
    else if(dx < 0 && dy < 0){
        setTextureID("player_up_left");
    }
}