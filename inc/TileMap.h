#ifndef TILEMAP_H
#define TILEMAP_H

#include "Entity.h"
#include "TextureManager.h"
#include "Player.h"
#include "Object.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 32


typedef struct {
    int id;
    
} Tile;

class TileMap {
  private:
    Tile grid[GRID_WIDTH][GRID_HEIGHT];

    static TileMap* instance;
    TileMap() {
        // Initialize with an empty tilemap
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                grid[x][y].id = 0;
            }
        }
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

    void render(SDL_Renderer* renderer) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                Tile* tile = &grid[x][y];
                if (tile->id != 0) {
                    SDL_Rect rect = {x * 32, y * 32, 32, 32};
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }

    
  
};



#endif