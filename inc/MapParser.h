#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include "Map.h"
#include "TileMap.h"
#include "Entity.h"

class Map;
struct SDL_Renderer;

class MapParser {
private:
    std::string trim(const std::string& str);
    std::string removeComments(const std::string& line);
    bool isSection(const std::string& line, std::string& sectionName);
    bool parseKeyValue(const std::string& line, std::string& key, std::string& value);
    int extractLayerNumber(const std::string& sectionName);

public:
    MapParser();
    ~MapParser();
    
    void loadMapFromFile(Map& map, const std::string& filePath);
};
#endif