#include "../inc/Collision.h"
#include "../inc/Entity.h"
#include "../inc/TileMap.h"

bool checkMapEntityCollision(const Hitbox& entityHitbox, const TileMap& tileMap){
    // colisions with the map are based on where the entity steps rather than the entire hitbox
    int left = entityHitbox.getX() / TILE_SIZE;
    int right = (entityHitbox.getX() + entityHitbox.getWidth()) / TILE_SIZE;
    int bottom = (entityHitbox.getY() + entityHitbox.getHeight()) / TILE_SIZE;

    // check if those tiles are collisions
    for(int x = left; x <= right; x++){
        Tile tile = tileMap.getTile(x, bottom);
        if(tileMap.getTileType(tile.id).collisionType == COLLISION_TRUE){
            return true;
        }
    }
    return false;
}