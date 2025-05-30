#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Animation{
private:
    int currentFrame; // Current frame of the animation
    int frameCount; // Total number of frames in the animation
    int frameDelay; // Delay between frames in milliseconds
    bool loop; // does it loop?

public:

};

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
        SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
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

    void drawTexture(const std::string& id, SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Rect* rect = nullptr) {
        if (textureMap.find(id) != textureMap.end()){
            SDL_Texture* texture = textureMap[id];
            SDL_Rect destRect = {x, y, width, height};
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


        





};


#endif