#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2();
	Vector2(float value);
	Vector2(float x, float y);
	~Vector2() = default;

	// 연산자 오버로딩.
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scale);
	Vector2& operator/=(float scale);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	Vector2 operator-() const;

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const float scale);
	Vector2 operator/(const float scale);

	// 길이 구하기.
	float Length();
	// 방향 구하기.
	Vector2 Normalized();

public:
	// x좌표 / y좌표.
	float x = 0.0f;
	float y = 0.0f;

	// 기본 값.
	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Up;
	static const Vector2 Down;
};