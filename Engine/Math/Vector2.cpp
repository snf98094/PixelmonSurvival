#include "PreCompiledHeader.h"
#include "Vector2.h"
#include <cassert>

Vector2::Vector2(int x, int y)
    : x(x), y(y)
{
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

bool Vector2::operator==(const Vector2& other)
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other)
{
    return x != other.x || y != other.y;
}