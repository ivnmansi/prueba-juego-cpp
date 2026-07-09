#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <sstream>
#include <string>

#include "Vector2D.h"
#include "TextureManager.h"
#include "Config.h"
#include "TileMap.h"
#include "Camera.h"

#define TILE_SIZE 40
#define MAX_MAP_LAYERS 8

class Map {
    private:
        // map characteristics
        std::string mapName;
        std::string mapBackground;
        Vector2D mapSize;

        // array of tile maps for different layers
        TileMap* tileMap;

    public:
        Map();
        ~Map();

        void setMapName(const std::string& name);
        void setMapBackground(const std::string& background);
        void setMapSize(const Vector2D& size);
        std::string getMapBackground();
        Vector2D getMapSize();
        std::string getMapName();

        TileMap& getTileMap(int layer);
        const TileMap& getTileMap(int layer) const;

        void loadMapFromFile(const std::string& filePath, SDL_Renderer* renderer);

        void renderBackground(SDL_Renderer* renderer, const Camera& camera);
        void renderLayersBelowPlayer(SDL_Renderer* renderer, const Camera& camera, bool debugMode);
        void renderLayersAbovePlayer(SDL_Renderer* renderer, const Camera& camera);
};

#endif