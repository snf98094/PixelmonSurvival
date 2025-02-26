#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "Render/ScreenBuffer.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

// 콘솔 창 메시지 콜백.
BOOL WINAPI MessageProcessor(DWORD message)
{
	switch (message)
	{
	case CTRL_CLOSE_EVENT:
		Engine::Get().QuitGame();
		return true;
	default:
		return false;
	}
}

// 스태틱 변수 초기화.
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	// 랜덤 시드 설정.
	srand((unsigned int)time(nullptr));

	// 싱글톤 객체 설정.
	instance = this;

	// 기본 타겟 프레임 속도 설정.
	SetTargetFrameRate(60.0f);

	// 화면 지울 때 사용할 버퍼 초기화.
	// 1. 버퍼 크기 할당.
	int widthSize = 315;
	int heightSize = 167;
	int interval = 640;
	int ratio = GetSystemMetrics(SM_CXSCREEN) / interval;

	screenSize.x = widthSize * ratio;
	screenSize.y = heightSize * ratio;
	imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// 버퍼 초기화.
	ClearImageBuffer();

	// 두 개의 버퍼 생성 (버퍼를 번갈아 사용하기 위해-더블 버퍼링).
	COORD size = { (short)screenSize.x, (short)screenSize.y };
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), size);
	renderTargets[1] = new ScreenBuffer(size);

	// 스왑 버퍼.
	Present();

	// 콘솔 창 이벤트 콜백 등록.
	SetConsoleCtrlHandler(MessageProcessor, true);

	// 마우스/윈도우 이벤트 활성화.
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	int flag = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(inputHandle, flag);

	// std::cin/std::cout 연결 끊기.
	ios::sync_with_stdio(false);
}

Engine::~Engine()
{
	// 메인 레벨 메모리 해제.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	// 클리어 버퍼 삭제.
	delete[] imageBuffer;

	// 화면 버퍼 삭제.
	delete renderTargets[0];
	delete renderTargets[1];
}

void Engine::Run()
{
	// CPU 시계 사용.
	// 시스템 시계 -> 고해상도 카운터. (10000000).
	// 메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 시작 시간 및 이전 시간을 위한 변수.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// Game-Loop.
	while (true)
	{
		// 종료 조건.
		if (quit)
		{
			break;
		}

		// 현재 프레임 시간 저장.
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 프레임 시간 계산.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		// 프레임 확인.
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인).
			ProcessInput();

			Update(deltaTime);
			Draw();
			LateUpdate(deltaTime);

			// 키 상태 저장.
			SavePreviouseKeyStates();

			// 이전 프레임 시간 저장.
			previousTime = currentTime;

			// 액터 정리 (삭제 요청된 액터들 정리).
			if (mainLevel)
				mainLevel->ProcessAddedAndDestroyedActor();
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체.
	if (mainLevel)
		delete mainLevel;

	// 메인 레벨 설정.
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// 예외 처리.
	if (mainLevel == nullptr)
	{
		return;
	}

	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// 예외 처리.
	if (mainLevel == nullptr)
	{
		return;
	}

	targetActor->Destroy();
}

void Engine::Draw(const Vector2& position, vector<vector<Color>>& image)
{
	int sizeY = image.size();
	for (int y = 0; y < sizeY; y++)
	{
		int sizeX = image[y].size() - 1;
		for (int x = 0; x < sizeX; x++)
		{
			if (image[y][x] == Color::None)
				continue;

			int index = ((int)position.y + y) * (int)screenSize.x + (int)position.x + x;
			imageBuffer[index].Char.UnicodeChar = L'■';
			imageBuffer[index].Attributes = (unsigned long)image[y][x];
		}
	}
}

void Engine::Draw(const Vector2& position, const wchar_t* image, Color color)
{
	int size = wcslen(image);
	for (int ix = 0; ix < size; ++ix)
	{
		int index = position.y * screenSize.x + position.x + ix;
		imageBuffer[index].Char.UnicodeChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::Draw(const Vector2& position, const wchar_t* image, int rightOffset, Color color)
{
	int size = wcslen(image) - rightOffset;
	for (int ix = 0; ix < size; ++ix)
	{
		int index = position.y * screenSize.x + position.x + ix;
		imageBuffer[index].Char.UnicodeChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
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

	// 2. 설정.
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

Vector2 Engine::MousePosition() const
{
	return mousePosition;
}

void Engine::QuitGame()
{
	// 종료 플래그 설정.
	quit = true;
}

Engine& Engine::Get()
{
	// 싱글톤 객체 반환.
	return *instance;
}

void Engine::ProcessInput()
{
	static HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	int flag = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(inputHandle, flag);

	INPUT_RECORD record;
	DWORD events;
	if (PeekConsoleInput(inputHandle, &record, 1, &events) && events > 0)
	{
		if (ReadConsoleInput(inputHandle, &record, 1, &events))
		{
			switch (record.EventType)
			{
			case KEY_EVENT:
			{
				// 키 눌림 상태 업데이트.
				if (record.Event.KeyEvent.bKeyDown)
					keyState[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = true;
				// 키 눌림 해제 상태 업데이트.
				else keyState[record.Event.KeyEvent.wVirtualKeyCode].isKeyDown = false;
			}
			break;

			case MOUSE_EVENT:
			{
				// 마우스 커서 위치 업데이트.
				mousePosition.x = record.Event.MouseEvent.dwMousePosition.X;
				mousePosition.y = record.Event.MouseEvent.dwMousePosition.Y;

				// 마우스 왼쪽 버튼 클릭 상태 업데이트.
				keyState[VK_LBUTTON].isKeyDown
					= (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;

				// 마우스 오른쪽 버튼 클릭 상태 업데이트.
				keyState[VK_RBUTTON].isKeyDown
					= (record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0;
			}
			break;
			}
		}
	}
}

void Engine::Update(float deltaTime)
{
	// 레벨 업데이트.
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
	// 화면 지우기.
	Clear();

	// 레벨 그리기.
	if (mainLevel != nullptr)
		mainLevel->Draw();

	// 백버퍼에 데이터 쓰기.
	GetRenderer()->Draw(imageBuffer);

	// 프론트<->백 버퍼 교환.
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
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
}

void Engine::ClearImageBuffer()
{
	// 버퍼 덮어쓰기.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// 버퍼 덮어쓰기.
		for (int x = 0; x < screenSize.x; ++x)
		{
			auto& buffer = imageBuffer[y * (int)screenSize.x + x];
			buffer.Char.UnicodeChar = L'■';
			buffer.Attributes = (int)Color::White;
		}

		// 각 줄 끝에 개행 문자 추가.
		auto& buffer = imageBuffer[y * (int)screenSize.x + (int)screenSize.x];
		buffer.Char.UnicodeChar = L'\n';
		buffer.Attributes = (int)Color::White;
	}

	// 마지막에 널 문자 추가.
	auto& buffer = imageBuffer[(int)screenSize.x * (int)screenSize.y];
	buffer.Char.UnicodeChar = L'\0';
	buffer.Attributes = (int)Color::White;
}