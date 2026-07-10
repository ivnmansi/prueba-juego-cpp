#include "../inc/Sprite.h"

Sprite::Sprite(){
    this->sourceRect = {0, 0, 0, 0};
    this->flip = SDL_FLIP_NONE;
    this->angle = 0.0;
    this->textureID = "";
}

Sprite::Sprite(const std::string& textureID){
    this->textureID = textureID;

    this->sourceRect = {0,0,0,0};

    this->flip = SDL_FLIP_NONE;
    this->angle = 0;
}

void Sprite::setTexture(const std::string& textureID) {
    if(this->textureID == textureID)
        return;
    this->textureID = textureID;
}

const std::string& Sprite::getTexture() const {
    return textureID;
}


void Sprite::render(SDL_Renderer* renderer, const Vector2D& position, const Vector2D& size,const Camera& camera){
    if(!textureID.empty()){
        TextureManager::getInstance()->drawTexture(getTexture(), renderer, camera.worldToScreen(position), size, &sourceRect);
    }
}