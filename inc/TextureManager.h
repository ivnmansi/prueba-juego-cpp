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
    bool loadTexture(const std::string& id, const std::string& filePath, SDL_Renderer* renderer);

    void drawTexture(const std::string& id, SDL_Renderer* renderer, const Vector2D& position, const Vector2D& size, SDL_Rect* rect = nullptr);

    void clearAllTextures();

    bool loadTexturesFromDirectory(std::string directory, SDL_Renderer* renderer);
};

#endif