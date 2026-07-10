#include "../inc/Character.h"

Character::Character(){}

Character::Character(int _id, std::string _name, Vector2D _position, Vector2D _size, Sprite _sprite, const Vector2D& _hitboxSize, const Vector2D& _hitboxOffset, State _state, Direction _direction, int _health, float _speed)
    : Entity(_id, _name, _position, _size, _sprite, _hitboxSize, _hitboxOffset) {
    this->state = _state;
    this->direction = _direction;
    this->health = _health;
    this->speed = _speed;

    EntityManager::getInstance()->addEntity(*this);
}

void Character::move(const Vector2D& movement, float deltaTime, const TileMap& tileMap){
    Entity::move(movement, speed, deltaTime, tileMap);

    if(movement.x > 0 && movement.y == 0)
        direction = RIGHT;
    else if(movement.x < 0 && movement.y == 0)
        direction = LEFT;
    else if(movement.y > 0 && movement.x == 0)
        direction = DOWN;
    else if(movement.y < 0 && movement.x == 0)
        direction = UP;
    else if(movement.x > 0 && movement.y > 0)
        direction = DOWN_RIGHT;
    else if(movement.x < 0 && movement.y > 0)
        direction = DOWN_LEFT;
    else if(movement.x > 0 && movement.y < 0)
        direction = UP_RIGHT;
    else if(movement.x < 0 && movement.y < 0)
        direction = UP_LEFT;

    updateTexture();
}

void Character::onUpdate(float deltaTime, const TileMap& tileMap){
    move(movementLogic(), deltaTime, tileMap);
}