#include "PreCompiledHeader.h"
#include "ImageText.h"
#include "Engine/Engine.h"+

ImageText::ImageText(const char* name)
{
	// ���� �н� ����.
	char path[512] = {};
	strcat_s(path, "../Assets/Image/");
	strcat_s(path, name);
	strcat_s(path, ".txt");

	// ���� ����.
	FILE* file = nullptr;
	fopen_s(&file, path, "rb");

	// ���� ó��.
	if (!file)
	{
		std::cout << "�̹��� ���� ���� ����.\n";
		__debugbreak;
		return;
	}

	colorList = new std::vector<std::vector<Color>>();
	auto& image = *colorList;

	// �� �پ� �б�
	char line[512];  // �� ���� ������ ����
	while (fgets(line, sizeof(line), file))
	{
		// colorList �� �߰�.
		image.emplace_back();

		// �� ���� ���� ���� ����
		line[strcspn(line, "\n")] = '\0';

		int tempSizeX = 0;

		// ','�� �и�
		char* context = nullptr;
		char* token = strtok_s(line, ",", &context);
		while (token)
		{
			// colorList �� �߰�.
			if (token[0] == '-')
				image[size.y].emplace_back(Color::None);
			else image[size.y].emplace_back((Color)atoi(token));

			// ���� ','�� �и�
			token = strtok_s(nullptr, ",", &context);

			// ������ üũ.
			tempSizeX++;
			if (size.x < tempSizeX)
				size.x = tempSizeX;
		}

		// �ε��� ����.
		++size.y;
	}

	// ���� �ݱ�
	fclose(file);
}

ImageText::ImageText(const ImageText* other)
{
	// �÷��� ����Ʈ.
	colorList = other->colorList;
	// ũ�� ����.
	size = other->size;
	// ��ǥ ����.
	drawingPosition = other->drawingPosition;
	// �̹��� ���� üũ.
	isCopy = true;
}

ImageText::~ImageText()
{
	// ������ �̹����� �ƴ� ��� ����Ʈ.
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
	// ����� ��ǥ�� ���� ���, ���� ��ǥ�� ����.
	if (this->drawingPosition != Vector2(0, 0))
		prevPosition = this->drawingPosition;
	else prevPosition = drawingPosition;

	// ����� ��ǥ ����.
	this->drawingPosition = drawingPosition - size / 2.0f;
}