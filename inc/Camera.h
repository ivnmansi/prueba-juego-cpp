#ifndef CAMERA_H
#define CAMERA_H

#include "Config.h"
#include "Vector2D.h"

class Camera {
    private:
        Vector2D position;
        Vector2D size;
    public:
        Camera(const Vector2D& position, const Vector2D& size);

        const Vector2D& getPosition() const;
        const Vector2D& getSize() const;

        void setPosition(const Vector2D& position);

        Vector2D worldToScreen(const Vector2D& worldPosition) const;
};

#endif