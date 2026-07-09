/**
 * @file TileMap.h
 * @brief Layer of tiles that make up the map. Colission, texture and triggers
 * 
 */
#ifndef TILEMAP_H
#define TILEMAP_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vector2D.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Config.h"


#define GRID_HEIGHT 10
#define GRID_WIDTH 20

#define TILE_SIZE 40

#define TILE_TYPE_NUM 3


// Collisions
enum CollisionType {
    COLLISION_TRUE,
    COLLISION_FALSE,
};

// Triggers
enum TriggerType {
    NO_TRIGGER,
    TEST_TRIGGER,
};

typedef struct {
    std::string name;
    enum CollisionType collisionType;
    enum TriggerType triggerType;
} TileType;

typedef struct {
    int id;
    enum TriggerType triggerType;
    enum CollisionType collisionType;
} Tile;

class TileMap {
  private:
    // map grid dimensions
        int gridWidth;
        int gridHeight;
        std::vector<Tile> grid;
    std::string tileTextureID;
    
    // dictionary of tile types
    const TileType tileTypes[TILE_TYPE_NUM] = {
        {"collidable", COLLISION_TRUE, NO_TRIGGER},
        {"walkable", COLLISION_FALSE, NO_TRIGGER},
        {"trigger_test", COLLISION_FALSE, TEST_TRIGGER}
    };

  public:
    TileMap();

        void setDimensions(int width, int height);

        int getWidth() const;

        int getHeight() const;

    void setTile(int x, int y, int id);

    const Tile getTile(int x, int y) const;

    const TileType getTileType(int id) const;

    const Tile* getGrid() const;

    void setTileTextureID(const std::string& textureID);

    std::string getTileTextureID();

    void render(SDL_Renderer* renderer, const Camera& camera);

};

#endif