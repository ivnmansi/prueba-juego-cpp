#ifndef COLLISION_H
#define COLLISION_H

class Hitbox;
class Entity;
class TileMap;

bool checkMapEntityCollision(const Hitbox& entityHitbox, const TileMap& tileMap);

#endif