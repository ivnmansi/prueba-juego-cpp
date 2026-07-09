#include "../inc/TileMap.h"

/**
 * @brief Construct a new Tile Map:: Tile Map object
 * Initializes with an empty grid
 */
TileMap::TileMap() {
    gridWidth = GRID_WIDTH;
    gridHeight = GRID_HEIGHT;
    grid.resize(gridWidth * gridHeight, Tile{});
    tileTextureID = "collition_tiles";
}

void TileMap::setDimensions(int width, int height) {
    gridWidth = width > 0 ? width : 1;
    gridHeight = height > 0 ? height : 1;
    grid.assign(gridWidth * gridHeight, Tile{});
}

int TileMap::getWidth() const {
    return gridWidth;
}

int TileMap::getHeight() const {
    return gridHeight;
}

/**
 * @brief Sets type of tile at the specified position
 * 
 * @param x 
 * @param y 
 * @param id 
 */
void TileMap::setTile(int x, int y, int id) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        grid[y * gridWidth + x].id = id;
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
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        return grid[y * gridWidth + x];
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
    return grid.empty() ? nullptr : grid.data();
}

void TileMap::setTileTextureID(const std::string& textureID) {
    tileTextureID = textureID;
}

std::string TileMap::getTileTextureID() {
    return tileTextureID;
}

void TileMap::render(SDL_Renderer* renderer, const Camera& camera) {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            Tile* tile = &grid[y * gridWidth + x];
            if(tile->id >= 0 && tile->id < TILE_TYPE_NUM){
                SDL_Rect sheet = {32 * tile->id, 0, 32, 32};
                TextureManager::getInstance()->drawTexture(
                    tileTextureID,
                    renderer,
                    camera.worldToScreen(Vector2D(x * TILE_SIZE, y * TILE_SIZE)),
                    Vector2D(TILE_SIZE, TILE_SIZE),
                    &sheet
                );
            }
        }
    }
}


