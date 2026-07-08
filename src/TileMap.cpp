#include "../inc/TileMap.h"

/**
 * @brief Construct a new Tile Map:: Tile Map object
 * Initializes with an empty grid
 */
TileMap::TileMap() {
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            grid[x][y].id = 0;
        }
    }
    tileTextureID = "collition_tiles";
}

/**
 * @brief Sets type of tile at the specified position
 * 
 * @param x 
 * @param y 
 * @param id 
 */
void TileMap::setTile(int x, int y, int id) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[x][y].id = id;
    }
}

/**
 * @brief Gets the type of tile at the specified position
 * 
 * @param x 
 * @param y 
 * @return const Tile 
 */
const Tile TileMap::getTile(int x, int y) const {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return grid[x][y];
    }
    return {0};
}

/**
 * @brief Returns the TileType corresponding to the given ID. If the ID is invalid, returns a default TileType with name "unknown" and COLLISION_FALSE.
 * 
 * @param id 
 * @return const TileType 
 */
const TileType TileMap::getTileType(int id) const {
    if (id >= 0 && id < TILE_TYPE_NUM) {
        return tileTypes[id];
    }
    return {"unknown", COLLISION_FALSE};
}

const Tile* TileMap::getGrid() const {
    return &grid[0][0];
}

void TileMap::setTileTextureID(const std::string& textureID) {
    tileTextureID = textureID;
}

std::string TileMap::getTileTextureID() {
    return tileTextureID;
}

void TileMap::render(SDL_Renderer* renderer) {
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


