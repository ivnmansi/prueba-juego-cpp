#include "../inc/MapParser.h"
#include <SDL2/SDL.h>
#include <cctype>
#include <algorithm>

MapParser::MapParser() {
}

MapParser::~MapParser() {
}

std::string MapParser::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

std::string MapParser::removeComments(const std::string& line) {
    size_t pos = line.find(';');
    if (pos != std::string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

bool MapParser::isSection(const std::string& line, std::string& sectionName) {
    std::string trimmed = trim(line);
    if (trimmed.length() >= 2 && trimmed[0] == '[' && trimmed[trimmed.length() - 1] == ']') {
        sectionName = trim(trimmed.substr(1, trimmed.length() - 2));
        return true;
    }
    return false;
}

bool MapParser::parseKeyValue(const std::string& line, std::string& key, std::string& value) {
    std::string trimmed = trim(removeComments(line));
    if (trimmed.empty()) return false;
    
    size_t pos = trimmed.find('=');
    if (pos == std::string::npos) return false;
    
    key = trim(trimmed.substr(0, pos));
    value = trim(trimmed.substr(pos + 1));
    return !key.empty() && !value.empty();
}

int MapParser::extractLayerNumber(const std::string& sectionName) {
    if (sectionName.substr(0, 6) == "layer_") {
        try {
            return std::stoi(sectionName.substr(6));
        } catch (...) {
            return -1;
        }
    }
    return -1;
}

void MapParser::loadMapFromFile(Map& map, const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        SDL_Log("Failed to open map file: %s", filePath.c_str());
        return;
    }

    std::string currentSection = "";
    int currentLayer = -1;
    int rowInLayer = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::string sectionName;
        
        // Check if it's a section header
        if (isSection(line, sectionName)) {
            currentSection = sectionName;
            currentLayer = extractLayerNumber(sectionName);
            rowInLayer = 0;
            SDL_Log("Entering section: %s", currentSection.c_str());
            continue;
        }

        // Skip empty lines
        std::string trimmedLine = trim(removeComments(line));
        if (trimmedLine.empty()) continue;

        // Parse [info] section
        if (currentSection == "info") {
            std::string key, value;
            if (parseKeyValue(line, key, value)) {
                if (key == "name") {
                    map.setMapName(value);
                    SDL_Log("Map name: %s", value.c_str());
                } else if (key == "background") {
                    map.setMapBackground(value);
                    SDL_Log("Map background: %s", value.c_str());
                } else if (key == "width") {
                    try {
                        int width = std::stoi(value);
                        map.setMapSize({(float)width, map.getMapSize().y});
                    } catch (...) {}
                } else if (key == "height") {
                    try {
                        int height = std::stoi(value);
                        map.setMapSize({map.getMapSize().x, (float)height});
                    } catch (...) {}
                }
            }
        }
        // Parse [layer_N] sections
        else if (currentLayer >= 0 && currentLayer < MAX_MAP_LAYERS) {
            std::string key, value;
            
            // Check for texture key
            if (parseKeyValue(line, key, value)) {
                if (key == "texture") {
                    map.getTileMap(currentLayer).setTileTextureID(value);
                }
                continue;
            }

            // Parse tile grid
            if (rowInLayer < GRID_HEIGHT) {
                std::stringstream lineStream(trimmedLine);
                int tileID;
                int col = 0;

                while (lineStream >> tileID && col < GRID_WIDTH) {
                    if (tileID < 0 || tileID >= TILE_TYPE_NUM) {
                        SDL_Log("Invalid tile ID %d at position (%d, %d)", tileID, col, rowInLayer);
                        tileID = 0;
                    }
                    map.getTileMap(currentLayer).setTile(col, rowInLayer, tileID);
                    col++;
                }
                rowInLayer++;
            }
        }
    }

    SDL_Log("Map loaded successfully from %s", filePath.c_str());
    file.close();
}