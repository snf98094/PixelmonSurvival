#include "PreCompiledHeader.h"
#include "ImageText.h"
#include "Engine/Engine.h"+

ImageText::ImageText(const char* name)
{
	// 파일 패스 지정.
	char path[512] = {};
	strcat_s(path, "../Assets/Image/");
	strcat_s(path, name);
	strcat_s(path, ".txt");

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	// 파일 처리.
	if (!file)
	{
		std::cout << "이미지 파일 열기 실패.\n";
		__debugbreak;
		return;
	}

	colorList = new std::vector<std::vector<Color>>();
	auto& image = *colorList;

	// 한 줄씩 읽기
	char line[512];  // 한 줄을 저장할 버퍼
	while (fgets(line, sizeof(line), file))
	{
		// colorList 줄 추가.
		image.emplace_back();

		// 줄 끝의 개행 문자 제거
		line[strcspn(line, "\n")] = '\0';

		int tempSizeX = 0;

		// ','로 분리
		char* context = nullptr;
		char* token = strtok_s(line, ",", &context);
		while (token)
		{
			// colorList 값 추가.
			if (token[0] == '-')
				image[size.y].emplace_back(Color::None);
			else image[size.y].emplace_back((Color)atoi(token));

			// 다음 ','로 분리
			token = strtok_s(nullptr, ",", &context);

			// 사이즈 체크.
			tempSizeX++;
			if (size.x < tempSizeX)
				size.x = tempSizeX;
		}

		// 인덱스 증가.
		++size.y;
	}

	// 파일 닫기
	fclose(file);
}

ImageText::ImageText(const ImageText* other)
{
	// 컬러값 리스트.
	colorList = other->colorList;
	// 크기 복사.
	size = other->size;
	// 좌표 복사.
	drawingPosition = other->drawingPosition;
	// 이미지 복사 체크.
	isCopy = true;
}

ImageText::~ImageText()
{
	// 복사한 이미지가 아닐 경우 딜리트.
	if (!isCopy)
	{
		delete colorList;
	}
}

void ImageText::Print()
{
	Engine::Get().Draw(drawingPosition, *colorList);
}

void ImageText::SetDrawingPosition(Vector2 drawingPosition)
{
	// 드로잉 좌표가 있을 경우, 이전 좌표로 이전.
	if (this->drawingPosition != Vector2(0, 0))
		prevPosition = this->drawingPosition;
	else prevPosition = drawingPosition;

	// 드로잉 좌표 갱신.
	this->drawingPosition = drawingPosition - size / 2.0f;
}