#include "../inc/Animation.h"

Animation::Animation(int frameCount, int frameWidth, int frameHeight, float frameDuration, int startX, int startY) {
    this->frameCount = frameCount;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->startX = startX;
    this->startY = startY;

    this->frameDuration = frameDuration;

    currentFrame = 0;
    elapsedTime = 0;
}

void Animation::update(float deltaTime){
    elapsedTime += deltaTime;

    if(elapsedTime >= frameDuration){
        elapsedTime = 0;

        currentFrame++;

        if(currentFrame >= frameCount){
            currentFrame = 0;
        }
    }
}

void Animation::reset(){
    currentFrame = 0;
    elapsedTime = 0;
}

SDL_Rect Animation::getSourceRect() const {
    return {
        startX + currentFrame * frameWidth,
        startY,
        frameWidth,
        frameHeight
    };
}

Animator::Animator() : currentAnimation(nullptr) {}

void Animator::addAnimation(const std::string& name, std::unique_ptr<Animation> animation) {
    animations[name] = std::move(animation);
}

void Animator::playAnimation(const std::string& name){

    if(currentAnimationName == name)
        return;

    auto it = animations.find(name);

    if(it != animations.end()){
        currentAnimation = it->second.get();
        currentAnimationName = name;
        currentAnimation->reset();
    }
}

void Animator::update(float deltaTime){
    if(currentAnimation){
        currentAnimation->update(deltaTime);
    }
}

SDL_Rect Animator::getSourceRect() const{
    if(currentAnimation){
        return currentAnimation->getSourceRect();
    }
    return {0, 0, 0, 0};
}