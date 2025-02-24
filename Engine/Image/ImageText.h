#pragma once
#include "Core.h"
#include <Math/Vector2.h>

class ENGINE_API ImageText
{
public:
	ImageText(const char* name);
	// ���� ������
	ImageText(const ImageText* other);
	~ImageText();

	void Print();
	void SetDrawingPosition(Vector2 drawingPosition);

	// �̹��� ũ�� Getter.
	const Vector2& GetSize() { return size; }
	// �̹����� �׸� ��ǥ Getter.
	const Vector2& GetDrawingPosition() { return drawingPosition; }

private:
	// �̹����� ����� �÷��� ����Ʈ.
	std::vector<std::vector<Color>>* colorList;
	// �̹��� ũ��.
	Vector2 size = Vector2(0, 0);
	// �̹����� �׸� ��ǥ.
	Vector2 drawingPosition = Vector2(0, 0);
	// ���� �̹��� ��ǥ.
	Vector2 prevPosition = Vector2(0, 0);
	// ����� ������ �̹��� ����.
	bool isCopy = false;
};