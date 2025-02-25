#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:
	Vector2();
	Vector2(float value);
	Vector2(float x, float y);
	~Vector2() = default;

	// ������ �����ε�.
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

	// ���� ���ϱ�.
	float Length();
	// ���� ���ϱ�.
	Vector2 Normalized();

public:
	// x��ǥ / y��ǥ.
	float x = 0.0f;
	float y = 0.0f;

	// �⺻ ��.
	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Up;
	static const Vector2 Down;
};