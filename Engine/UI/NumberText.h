#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"
#include <vector>

enum class TextSizeType
{
	Normal,
	Large
};

enum class TextSortType
{
	Left,
	Middle,
	Right
};

class ENGINE_API NumberText : public Actor
{
	RTTI_DECLARATIONS(NumberText, Actor)

public:
	NumberText(TextSizeType sizeType = TextSizeType::Normal);
	~NumberText();

	virtual void Draw() override;

	void SetSortType(TextSortType sortType);
	void SetNumber(int number);
	void SetPosition(Vector2 position);

private:
	// ���� 0~9 �̹��� ����.
	ImageText* numbers[10];
	// �ڸ����� ���� �̹��� ����.
	std::vector<std::vector<ImageText>> numberList;
	// ǥ���� ���� �ؽ�Ʈ.
	char* number = nullptr;
	// ���� ����.
	size_t length = 0;
	// �̹����� ǥ���� ���� ��ġ.
	Vector2 position = Vector2();
	// �޸� �̹��� ����.
	ImageText* comma = nullptr;
	// �޸� ����Ʈ.
	std::vector<ImageText> commaList;
	// ��� ũ��.
	TextSizeType sizeType = TextSizeType::Normal;
	// ��� ����.
	TextSortType sortType = TextSortType::Left;
	// �ؽ�Ʈ ����.
	int textInterval = 16;
	// �޸� ����.
	int commaInterval = 0;
	// �޸��� ���� ���� ������.
	int commaOffset = 0;
};