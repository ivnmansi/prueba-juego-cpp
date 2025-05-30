#ifndef TILEMAP_H
#define TILEMAP_H

#include "Entity.h"
#include "TextureManager.h"
#include "Player.h"
#include "Object.h"
#include "Config.h"


#define GRID_HEIGHT 20
#define TILE_SIZE ((int)(SCREEN_HEIGHT / GRID_HEIGHT))
#define GRID_WIDTH ((int)(SCREEN_WIDTH / TILE_SIZE))

#define TILE_TYPE_NUM 3

enum CollisionType {
    COLLISION_TRUE,
    COLLISION_FALSE,
};
typedef struct {
    std::string name;
    enum CollisionType collisionType;
} TileType;
typedef struct {
    int id;
} Tile;

class TileMap {
  private:
    Tile grid[GRID_WIDTH][GRID_HEIGHT];
    std::string mapName;
    const TileType tileTypes[TILE_TYPE_NUM] = {
        {"void", COLLISION_FALSE},
        {"grass", COLLISION_FALSE},
        {"rock", COLLISION_TRUE},
    };
    std::string tileTexureID;

    static TileMap* instance;
    TileMap() {
        // Initialize with an empty tilemap
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                grid[x][y].id = 0;
            }
        }
        mapName = "default_map";
        tileTexureID = "tile_texture1";
    }

  public:
    static TileMap* getInstance() {
      if(instance == nullptr){
        instance = new TileMap();
      }
      return instance;
    }

    void setTile(int x, int y, int id) {
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            grid[x][y].id = id;
        }
    }
    Tile getTile(int x, int y) {
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            return grid[x][y];
        }
        return {0};
    }

    TileType getTileType(int id) {
        if (id >= 0 && id < TILE_TYPE_NUM) {
            return tileTypes[id];
        }
        return {"unknown", COLLISION_FALSE};
    }

    void setMapName(const std::string& name) {
        mapName = name;
    }
    std::string getMapName() const {
        return mapName;
    }

    void setTileTextureID(const std::string& textureID) {
        tileTexureID = textureID;
    }
    std::string getTileTextureID() const {
        return tileTexureID;
    }


    void render(SDL_Renderer* renderer) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                Tile* tile = &grid[x][y];
                if(tile->id >= 0 && tile->id < TILE_TYPE_NUM){
                    SDL_Rect sheet = {32 * tile->id, 0, 32, 32};
                    TextureManager::getInstance()->drawTexture(
                        tileTexureID,
                        renderer,
                        x * TILE_SIZE,
                        y * TILE_SIZE,
                        TILE_SIZE,
                        TILE_SIZE,
                        &sheet
                    );
                }
            }
        }
    }
};



#endif