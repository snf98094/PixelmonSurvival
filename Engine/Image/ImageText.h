#pragma once
#include "Core.h"
#include <Math/Vector2.h>

class ENGINE_API ImageText
{
public:
	ImageText(const char* name);
	// 복사 생성자
	ImageText(const ImageText* other);
	~ImageText();

	void Print();
	void SetDrawingPosition(Vector2 drawingPosition);

	// 좌우 반전 값 생성.
	void CreateFlipImage();

	// 이미지 크기 Getter.
	const Vector2& GetSize() { return size; }
	// 이미지를 그릴 좌표 Getter.
	const Vector2& GetDrawingPosition() { return drawingPosition; }
	// 이미지 반전 여부 Setter.
	void SetFlip(bool value) { isFlip = value; }
	// 이미지 컬러값 Getter.
	vector<vector<Color>>& GetColorList() { return *colorList; }

private:
	// 이미지로 사용할 컬러값 리스트.
	vector<vector<Color>>* colorList;
	// 좌우 반전 이미지로 사용할 컬러값 리스트.
	vector<vector<Color>>* flipList;
	// 이미지 크기.
	Vector2 size = Vector2(0, 0);
	// 이미지를 그릴 좌표.
	Vector2 drawingPosition = Vector2(0, 0);
	// 이전 이미지 좌표.
	Vector2 prevPosition = Vector2(0, 0);
	// 복사로 생성한 이미지 여부.
	bool isCopy = false;
	// 이미지 반전 여부.
	bool isFlip = false;
};