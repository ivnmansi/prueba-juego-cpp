#include "../inc/Collision.h"
#include "../inc/Entity.h"
#include "../inc/TileMap.h"

bool checkMapEntityCollision(const Hitbox& entityHitbox, const TileMap& tileMap){
    // colisions with the map are based on where the entity steps rather than the entire hitbox
    int left = entityHitbox.getX() / TILE_SIZE;
    int right = (entityHitbox.getX() + entityHitbox.getWidth()) / TILE_SIZE;
    int bottom = (entityHitbox.getY() + entityHitbox.getHeight()) / TILE_SIZE;

    for(int x = left; x <= right; x++){
        Tile tile = tileMap.getTile(x, bottom);
        // check if those tiles are collisions
        if(tileMap.getTileType(tile.id).collisionType == COLLISION_TRUE){
            return true;
        }
        // check if those tiles are triggers
        if(tileMap.getTileType(tile.id).triggerType != NO_TRIGGER){
            // TODO: CALL THE TRIGGER MANAGER OR SOMETHING LIKE THAT
            SDL_Log("Trigger event detected at tile (%d, %d) with trigger type %d", x, bottom, tileMap.getTileType(tile.id).triggerType);
        }
    }

    
    return false;
}