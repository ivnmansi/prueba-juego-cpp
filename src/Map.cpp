#include "../inc/Map.h"
#include "../inc/TileMap.h"
#include "../inc/MapParser.h"

#include <string>

Map::Map() {
    mapName = "default";
    mapBackground = "default";
    mapSize = Vector2D(20, 10);
    tileMap = new TileMap[MAX_MAP_LAYERS];
}

Map::~Map() {
    delete[] tileMap;
}

void Map::setMapName(const std::string& name) {
    mapName = name;
}

void Map::setMapBackground(const std::string& background) {
    mapBackground = background;
}

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

void Map::render(SDL_Renderer* renderer) {
    TextureManager::getInstance()->drawTexture(
        mapBackground,
        renderer,
        Vector2D(0, 0),
        Vector2D(TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)
    );

    for (int layer = 0; layer < MAX_MAP_LAYERS; ++layer) {
        tileMap[layer].render(renderer);
    }
}

void Map::loadMapFromFile(const std::string& filePath, SDL_Renderer* renderer) {
    MapParser parser;
    parser.loadMapFromFile(*this, filePath);
}