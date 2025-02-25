#include "PreCompiledHeader.h"
#include "Vector2.h"
#include <cassert>
#include <cmath>

const Vector2 Zero = Vector2(0.0f);
const Vector2 One = Vector2(1.0f);
const Vector2 Right = Vector2(1.0f, 0.0f);
const Vector2 Left = Vector2(-1.0f, 0.0f);
const Vector2 Up = Vector2(0.0f, 1.0f);
const Vector2 Down = Vector2(0.0f, -1.0f);

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{ }

Vector2::Vector2(float value)
    : x(value), y(value)
{ }

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{ }

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Vector2& Vector2::operator/=(float scale)
{
    assert(scale != 0.0f);

    x /= scale;
    y /= scale;
    return *this;
}

bool Vector2::operator==(const Vector2& other)
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other)
{
    return x != other.x || y != other.y;
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& other)
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const float scale)
{
    return Vector2(x * scale, y * scale);
}

Vector2 Vector2::operator/(const float scale)
{
    assert(scale != 0.0f);
    return Vector2(x / scale, y / scale);
}

float Vector2::Length()
{
    return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normalized()
{
    float length = Length();
    return Vector2(x / length, y / length);
}