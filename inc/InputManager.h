#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include <vector>

class InputManager {
    public:
        static InputManager* getInstance();

        void update();
        bool isKeyPressed(SDL_Scancode key);
        bool isKeyReleased(SDL_Scancode key);
        bool isKeyHeld(SDL_Scancode key);
    
    private:
        InputManager() = default;

        std::vector<Uint8> currentState;
        std::vector<Uint8> previousState;
};

#endif