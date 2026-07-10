#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <string>
#include <memory>

class Animation {
    private:
        int frameCount;
        int currentFrame;

        int frameWidth;
        int frameHeight;

        int startX;
        int startY;

        float frameDuration;
        float elapsedTime;

        bool loop;

    public:
        Animation(
            int frameCount,
            int frameWidth,
            int frameHeight,
            float frameDuration,
            int startX,
            int startY
        );

        void update(float deltaTime);

        void reset();

        SDL_Rect getSourceRect() const;
};

class Animator {
    private:

        std::map<std::string, std::unique_ptr<Animation>> animations;
        Animation* currentAnimation;
        std::string currentAnimationName;

    public:
        Animator();

        bool hasAnimations() const { return !animations.empty(); }
        void addAnimation(const std::string& name, std::unique_ptr<Animation> animation);
        void playAnimation(const std::string& name);
        void update(float deltaTime);
        SDL_Rect getSourceRect() const;
};

#endif