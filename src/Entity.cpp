#include "../inc/Entity.h"
#include "../inc/TileMap.h"

EntityManager* EntityManager::instance = nullptr;

 void Entity::move(Vector2D& direction, float speed, const TileMap& tileMap) {
	Vector2D newPosition = getPosition() + direction.normalize() * speed;

	Hitbox newHitbox = getHitbox();
	newHitbox.setPosition(newPosition);

	if (direction.magnitude() > 0.0f && !checkMapEntityCollision(newHitbox, tileMap)) {
		setPosition(newPosition);
	}
}