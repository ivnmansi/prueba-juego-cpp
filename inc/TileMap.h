#ifndef TILEMAP_H
#define TILEMAP_H

#include "Entity.h"
#include "TextureManager.h"
#include "Player.h"
#include "Config.h"


#define GRID_HEIGHT 20
#define TILE_SIZE ((int)(SCREEN_HEIGHT / GRID_HEIGHT))
#define GRID_WIDTH 20

#define TILE_TYPE_NUM 3

/**
 * CAMBIAR LOGICA PARA QUE TILEMAP SOLO MANEJE POSICIÓN DE COLISIONES Y TRIGGERS
 * QUE LA IMAGEN DEL MAPA SEA UNA IMAGEN DIBUJADA DE FONDO EN VEZ DE TILES
 * 
 */

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
    enum CollisionType collisionType;
    enum TriggerType triggerType;
} Tile;

class TileMap {
  private:
    // map grid dimensions
    Tile grid[GRID_WIDTH][GRID_HEIGHT];

    // map name and tile texture ID
    std::string mapName;
    std::string tileTextureID;
    
    const TileType tileTypes[TILE_TYPE_NUM] = {
        {"void", COLLISION_FALSE},
        {"grass", COLLISION_FALSE},
        {"rock", COLLISION_TRUE},
    };


    static TileMap* instance;
    TileMap() {
        // Initialize with an empty tilemap
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                grid[x][y].id = 0;
            }
        }
        mapName = "default_map";
        tileTextureID = "tile_texture1";
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
        tileTextureID = textureID;
    }
    std::string getTileTextureID() const {
        return tileTextureID;
    }


    void render(SDL_Renderer* renderer) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                Tile* tile = &grid[x][y];
                if(tile->id >= 0 && tile->id < TILE_TYPE_NUM){
                    SDL_Rect sheet = {32 * tile->id, 0, 32, 32};
                    TextureManager::getInstance()->drawTexture(
                        tileTextureID,
                        renderer,
                        Vector2D(x * TILE_SIZE, y * TILE_SIZE),
                        Vector2D(TILE_SIZE, TILE_SIZE),
                        &sheet
                    );
                }
            }
        }
    }

    void loadMapFromFile(std::string filePath, SDL_Renderer* renderer){
        std::ifstream file(filePath);
        if(!file.is_open()){
            SDL_Log("Failed to open map file: %s", filePath.c_str());
            return;
        }

        // leer nombre del mapa
        if(std::getline(file, mapName)){
            SDL_Log("Loading map %s...", mapName.c_str());
        }
        // leer ID de textura del tile (la textura ya deberia estar cargada)
        if(!std::getline(file, tileTextureID)){
            SDL_Log("Failed to read tile texture ID from map file: %s", filePath.c_str());
        }

        // leer grid de tiles
        int i = 0;
        std::string line;
        SDL_Log("Reading tile grid from file...");

        while(std::getline(file, line)){
            std::stringstream lineStream(line);
            int tileID;
            int j = 0;

            while(lineStream >> tileID && j < GRID_WIDTH) {
                if(tileID < 0 || tileID >= TILE_TYPE_NUM){
                    SDL_Log("Invalid tile ID %d at position (%d, %d) in map file: %s", tileID, j, i, filePath.c_str());
                    tileID = 0;
                }
                setTile(j, i, tileID);
                j++;
            }
            i++;
        }
        SDL_Log("Map %s loaded successfully", mapName.c_str());
        file.close();
    }

};



#endif