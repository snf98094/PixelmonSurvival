#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "Render/ScreenBuffer.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

// ����ƽ ���� �ʱ�ȭ.
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	// ���� �õ� ����.
	srand((unsigned int)time(nullptr));

	// �̱��� ��ü ����.
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ� ����.
	SetTargetFrameRate(60.0f);

	// ȭ�� ���� �� ����� ���� �ʱ�ȭ.
	// 1. ���� ũ�� �Ҵ�.
	int widthSize = 210;
	int heightSize = 110;
	int interval = 640;
	int ratio = GetSystemMetrics(SM_CXSCREEN) / interval;

	screenSize.x = widthSize * ratio;
	screenSize.y = heightSize * ratio;
	imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// ���� �ʱ�ȭ.
	ClearImageBuffer();

	// �� ���� ���� ���� (���۸� ������ ����ϱ� ����-���� ���۸�).
	COORD size = { (short)screenSize.x, (short)screenSize.y };
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), size);
	renderTargets[1] = new ScreenBuffer(size);

	// ���� ����.
	Present();
}

Engine::~Engine()
{
	// ���� ���� �޸� ����.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	// Ŭ���� ���� ����.
	delete[] imageBuffer;

	// ȭ�� ���� ����.
	delete renderTargets[0];
	delete renderTargets[1];
}

void Engine::Run()
{
	// CPU �ð� ���.
	// �ý��� �ð� -> ���ػ� ī����. (10000000).
	// ���κ��忡 �ð谡 ����.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// ���� �ð� �� ���� �ð��� ���� ����.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// Game-Loop.
	while (true)
	{
		// ���� ����.
		if (quit)
		{
			break;
		}

		// ���� ������ �ð� ����.
		//time = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// ������ �ð� ���.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// �� ������ �ð� ���.
		//float targetOneFrameTime = 1.0f / targetFrameRate;

		// ������ Ȯ��.
		if (deltaTime >= targetOneFrameTime)
		{
			// �Է� ó�� (���� Ű�� ���� ���� Ȯ��).
			ProcessInput();

			// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��.
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
				LateUpdate(deltaTime);
			}

			// Ű ���� ����.
			SavePreviouseKeyStates();

			// ���� ������ �ð� ����.
			previousTime = currentTime;

			// ���� ���� (���� ��û�� ���͵� ����).
			if (mainLevel)
			{
				//mainLevel->DestroyActor();
				mainLevel->ProcessAddedAndDestroyedActor();
			}

			// ������ Ȱ��ȭ.
			shouldUpdate = true;
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü.
	if (mainLevel)
		delete mainLevel;

	// ���� ���� ����.
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// ���� ó��.
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�.
	shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// ���� ó��.
	if (mainLevel == nullptr)
	{
		return;
	}

	// ������ ���� �߰�.
	shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::Draw(const Vector2& position, std::vector<std::vector<Color>>& image)
{
	int sizeY = image.size();
	for (int y = 0; y < sizeY; y++)
	{
		int sizeX = image[y].size() - 1;
		for (int x = 0; x < sizeX; x++)
		{
			if (image[y][x] == Color::None)
				continue;

			int index = (position.y + y) * screenSize.x + position.x + x;
			imageBuffer[index].Char.UnicodeChar = L'��';
			imageBuffer[index].Attributes = (unsigned long)image[y][x];
		}
	}
}

void Engine::Draw(const Vector2& position, const wchar_t* image, Color color)
{
	int size = wcslen(image);
	for (int ix = 0; ix < size; ++ix)
	{
		int index = (position.y * (screenSize.x)) + position.x + ix;
		imageBuffer[index].Char.UnicodeChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::Draw(const Vector2& position, const wchar_t* image, int rightOffset, Color color)
{
	int size = wcslen(image) - rightOffset;
	for (int ix = 0; ix < size; ++ix)
	{
		int index = (position.y * (screenSize.x)) + position.x + ix;
		imageBuffer[index].Char.UnicodeChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. Ŀ�� �Ӽ� ����ü ����.
	CONSOLE_CURSOR_INFO info = { };

	// Ÿ�� ���� ����ü �� ����.
	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;

	}

	// 2. ����.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	// ���� �÷��� ����.
	quit = true;
}

Engine& Engine::Get()
{
	// �̱��� ��ü ��ȯ.
	return *instance;
}

void Engine::ProcessInput()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// ���� ������Ʈ.
	if (mainLevel != nullptr)
		mainLevel->Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
		Engine::Get().QuitGame();
}

void Engine::LateUpdate(float deltaTime)
{
	if (mainLevel != nullptr)
		mainLevel->LateUpdate(deltaTime);
}

void Engine::Clear()
{
	ClearImageBuffer();
	GetRenderer()->Clear();
}

void Engine::Draw()
{
	// ȭ�� �����.
	Clear();

	// ���� �׸���.
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}

	// ����ۿ� ������ ����.
	GetRenderer()->Draw(imageBuffer);

	// ����Ʈ<->�� ���� ��ȯ.
	Present();
}

void Engine::Present()
{
	// Swap Buffer.
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

void Engine::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}

void Engine::ClearImageBuffer()
{
	// ���� �����.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// ���� �����.
		for (int x = 0; x < screenSize.x; ++x)
		{
			auto& buffer = imageBuffer[(y * (screenSize.x)) + x];
			buffer.Char.UnicodeChar = L'��';
			buffer.Attributes = (int)Color::White;
		}

		// �� �� ���� ���� ���� �߰�.
		auto& buffer = imageBuffer[(y * (screenSize.x)) + screenSize.x];
		buffer.Char.UnicodeChar = L'\n';
		buffer.Attributes = (int)Color::White;
	}

	// �������� �� ���� �߰�.
	auto& buffer = imageBuffer[(screenSize.x) * screenSize.y];
	buffer.Char.UnicodeChar = L'\0';
	buffer.Attributes = (int)Color::White;
}
