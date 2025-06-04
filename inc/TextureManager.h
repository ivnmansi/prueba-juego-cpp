#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <filesystem>
#include <fstream>

#include "Vector2D.h"


class TextureManager {
private:
    // Singleton instance
    static TextureManager* instance;
    TextureManager() = default;

    std::map<std::string, SDL_Texture*> textureMap; // mapa de texturas por ID

public:
    static TextureManager* getInstance() {
        if (instance == nullptr) {
            instance = new TextureManager();
        }
        return instance;
    }

    /**
     * @brief Load a texture from a file
     * 
     * @param renderer The SDL_Renderer to use for loading the texture
     * @param filePath The path to the texture file
     * @param name The name to associate with the loaded texture
     * @return true if the texture was loaded successfully, false otherwise
     */
    bool loadTexture(const std::string& id, const std::string& filePath, SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (!surface) {
            SDL_Log("Failed to load image %s: %s", filePath.c_str(), SDL_GetError());
            return false;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture) {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
            return false;
        }

        textureMap[id] = texture;
        return true;
    }

    void drawTexture(const std::string& id, SDL_Renderer* renderer, const Vector2D& position, const Vector2D& size, SDL_Rect* rect = nullptr) {
        if (textureMap.find(id) != textureMap.end()){
            SDL_Texture* texture = textureMap[id];
            SDL_Rect destRect = {position.x, position.y, size.x, size.y};
            SDL_RenderCopy(renderer, texture, rect, &destRect);
        } else {
            SDL_Log("Texture with ID '%s' not found", id.c_str());
        }
    }


    void clearAllTextures() {
        for (auto& pair : textureMap) {
            SDL_DestroyTexture(pair.second);
        }
        textureMap.clear();
    }

    bool loadTexturesFromDirectory(std::string directory, SDL_Renderer* renderer){
        SDL_Log("Loading textures...");
        
        bool foundAnyTextures = false;
        
        for(auto& entry : std::filesystem::directory_iterator(directory)){
            std::string extension = entry.path().extension().string();
            if(!entry.is_regular_file() || (extension != ".png" && extension != ".jpg" && extension != ".jpeg" && extension != ".bmp")){
                continue;
            }
            std::string filePath = entry.path().string();
            std::string textureID = entry.path().stem().string();
            if(!loadTexture(textureID, filePath, renderer)){
                SDL_Log("Failed to load texture: %s", filePath.c_str());
                return false;
            }
            SDL_Log("Loaded texture: %s", filePath.c_str());
            foundAnyTextures = true;
        }
        if (!foundAnyTextures) {
            SDL_Log("No textures found in directory: %s", directory.c_str());
        }
        
        SDL_Log("Textures loaded successfully");
        return true;
    }


        





};

#endif