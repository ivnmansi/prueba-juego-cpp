#include "../inc/Vector2D.h"

/**
 * @brief Empty constructor for Vector2D
 * 
 */
Vector2D::Vector2D(){
    x = 0.0f;
    y = 0.0f;
}

/**
 * @brief Construct for Vector2D
 * 
 * @param x 
 * @param y 
 */
Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& v2){
    this->x += v2.x;
    this->y += v2.y;
    return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& v2){
    this->x -= v2.x;
    this->y -= v2.y;
    return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& v2){
    this->x *= v2.x;
    this->y *= v2.y;
    return *this;
}

Vector2D& Vector2D::divide(const Vector2D& v2){
    this->x /= v2.x;
    this->y /= v2.y;
    return *this;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2){
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2){
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D& v1, const Vector2D& v2){
    return Vector2D(v1.x * v2.x, v1.y * v2.y);
}

Vector2D operator/(const Vector2D& v1, const Vector2D& v2){
    return Vector2D(v1.x / v2.x, v1.y / v2.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2){
    return this->add(v2);
}
Vector2D& Vector2D::operator-=(const Vector2D& v2){
    return this->subtract(v2);
}
Vector2D& Vector2D::operator*=(const Vector2D& v1){
    return this->multiply(v1);
}
Vector2D& Vector2D::operator/=(const Vector2D& v1){
    return this->divide(v1);
}

bool Vector2D::operator==(const Vector2D& v2){
        return (this->x == v2.x && this->y == v2.y);
}

float Vector2D::magnitude(){
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const{
        Vector2D result = *this;
        float magnitude = result.magnitude();
        if (magnitude == 0) {
            return result;
        }
        result /= magnitude;
        return result;
}

Vector2D& Vector2D::multiplyByScalar(const float scalar){
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D& Vector2D::divideByScalar(const float scalar){
    if(scalar != 0.0f){
        this->x /= scalar;
        this->y /= scalar;
    }
    return *this;
}

Vector2D operator*(const Vector2D& v1, const float scalar){
    return Vector2D(v1.x * scalar, v1.y * scalar);
}
Vector2D operator/(const Vector2D& v1, const float scalar){
    return Vector2D(v1.x / scalar, v1.y / scalar);
}

Vector2D& Vector2D::operator*=(const float scalar){
    return this->multiplyByScalar(scalar);
}
Vector2D& Vector2D::operator/=(const float scalar){
    return this->divideByScalar(scalar);
}

