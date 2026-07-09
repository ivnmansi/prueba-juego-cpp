#include "../inc/Map.h"
#include "../inc/TileMap.h"
#include "../inc/MapParser.h"

#include <string>

/**
 * @brief Construct a new Map:: Map object
 * 
 */
Map::Map() {
    mapName = "default";
    mapBackground = "default";
    mapSize = Vector2D(20, 10);
    tileMap = new TileMap[MAX_MAP_LAYERS];
    for (int layer = 0; layer < MAX_MAP_LAYERS; ++layer) {
        tileMap[layer].setDimensions((int)mapSize.x, (int)mapSize.y);
    }
}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map() {
    delete[] tileMap;
}

/**
 * @brief Sets the name of the map
 * 
 * @param name Name of the map
 */
void Map::setMapName(const std::string& name) {
    mapName = name;
}

/**
 * @brief Sets the background texture of the map
 * 
 * @param background Name of the background texture
 */
void Map::setMapBackground(const std::string& background) {
    mapBackground = background;
}

/**
 * @brief Sets the size of the map
 * 
 * @param size Size of the map
 */
void Map::setMapSize(const Vector2D& size) {
    mapSize = size;
}


std::string Map::getMapBackground() {
    return mapBackground;
}

Vector2D Map::getMapSize() {
    return mapSize;
}

std::string Map::getMapName() {
    return mapName;
}

TileMap& Map::getTileMap(int layer) {
    return tileMap[layer];
}

const TileMap& Map::getTileMap(int layer) const {
    return tileMap[layer];
}

void Map::renderBackground(SDL_Renderer* renderer){
    TextureManager::getInstance()->drawTexture(
        mapBackground,
        renderer,
        Vector2D(0, 0),
        Vector2D(TILE_SIZE * mapSize.x, TILE_SIZE * mapSize.y)
    );
}

void Map::renderLayersBelowPlayer(SDL_Renderer* renderer, bool debugMode){
    for (int layer = 0; layer < 3; ++layer) {
        if(layer == 0 && !debugMode){
            continue;
        }
        tileMap[layer].render(renderer);
    }
}

void Map::renderLayersAbovePlayer(SDL_Renderer* renderer){
    for (int layer = 3; layer < MAX_MAP_LAYERS; ++layer) {
        tileMap[layer].render(renderer);
    }
}


void Map::loadMapFromFile(const std::string& filePath, SDL_Renderer* renderer) {
    MapParser parser;
    parser.loadMapFromFile(*this, filePath);
}