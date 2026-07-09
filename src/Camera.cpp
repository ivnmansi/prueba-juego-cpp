#include "../inc/Camera.h"

Camera::Camera(const Vector2D& position, const Vector2D& size) : position(position), size(size) {}

const Vector2D& Camera::getPosition() const {
    return position;
}

const Vector2D& Camera::getSize() const {
    return size;
}

void Camera::setPosition(const Vector2D& position) {
    this->position = position;
}

Vector2D Camera::worldToScreen(const Vector2D& worldPosition) const {
    return worldPosition - position;
}