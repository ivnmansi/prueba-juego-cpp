#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>

#include "Vector2D.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Animation.h"

class Sprite {
    private:
        std::string textureID;

        SDL_Rect sourceRect;
        SDL_RendererFlip flip;
        double angle;

    public:
        Sprite();
        Sprite(const std::string& textureID);

        void setTexture(const std::string& textureID);
        const std::string& getTexture() const;

        void setSourceRect(const SDL_Rect& rect) { sourceRect = rect; }
        void setFlip(SDL_RendererFlip flip) { this->flip = flip; }
        void setAngle(double angle) { this->angle = angle; }

        SDL_Rect getSourceRect() const { return sourceRect; }
        SDL_RendererFlip getFlip() const { return flip; }
        double getAngle() const { return angle; }

        void render(
            SDL_Renderer* renderer,
            const Vector2D& position,
            const Vector2D& size,
            const Camera& camera
        );
};

#endif