#include "../inc/InputManager.h"

static InputManager* instance = nullptr;

InputManager* InputManager::getInstance() {
    if (instance == nullptr) {
        instance = new InputManager();
    }
    return instance;
}

void InputManager::update()
{
    SDL_PumpEvents();

    int numKeys;
    const Uint8* keyboard = SDL_GetKeyboardState(&numKeys);

    if (currentState.empty())
    {
        currentState.resize(numKeys);
        previousState.resize(numKeys);
    }

    previousState = currentState;

    std::copy(keyboard, keyboard + numKeys, currentState.begin());
}

bool InputManager::isKeyHeld(SDL_Scancode key){
    return currentState[key];
}

bool InputManager::isKeyPressed(SDL_Scancode key){
    return currentState[key] && !previousState[key];
}

bool InputManager::isKeyReleased(SDL_Scancode key){
    return !currentState[key] && previousState[key];
}
