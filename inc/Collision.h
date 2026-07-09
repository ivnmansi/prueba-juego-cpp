#ifndef COLLISION_H
#define COLLISION_H

#include "Entity.h"
#include "TileMap.h"

class Hitbox;
class Entity;
class TileMap;

bool checkMapEntityCollision(const Hitbox& entityHitbox, const TileMap& tileMap);

#endif