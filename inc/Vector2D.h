#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D {

public:
    float x,y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& add(const Vector2D& v2);
    Vector2D& subtract(const Vector2D& v2);
    Vector2D& multiply(const Vector2D& v2);
    Vector2D& divide(const Vector2D& v2);

    friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& v2);
    Vector2D& operator-=(const Vector2D& v2);
    Vector2D& operator*=(const Vector2D& v1);
    Vector2D& operator/=(const Vector2D& v1);

    bool operator==(const Vector2D& v2);

    float magnitude();
    Vector2D normalize() const;
    
    Vector2D& multiplyByScalar(const float scalar);
    Vector2D& divideByScalar(const float scalar);

    friend Vector2D operator*(const Vector2D& v1, const float scalar);
    friend Vector2D operator/(const Vector2D& v1, const float scalar);
    Vector2D& operator*=(const float scalar);
    Vector2D& operator/=(const float scalar);



};



#endif

