#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

class Object : public Entity {
public:

    Object() : Entity(0, "NULL_OBJECT", 0, 0, 0, 0, 0, 0, "") {}

    Object(int _id, const char* _name, int _x, int _y, int _width, int _height, std::string _textureID)
        : Entity(_id, _name, _x, _y, _width, _height, 0, 0, _textureID) {
        }

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = getHitbox().getRect();
        SDL_RenderFillRect(renderer, &rect);
    }

};

class CollitionObject : public Object {
public:
    CollitionObject() : Object(0, "NULL_COLLITION_OBJECT", 0, 0, 0, 0, "") {}

    CollitionObject(int _id, const char* _name, int _x, int _y, int _width, int _height, std::string _textureID)
        : Object(_id, _name, _x, _y, _width, _height, _textureID) {}

    

};

#endif