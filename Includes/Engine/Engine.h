#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include <Image/ImageText.h>

// �Է� ó���� ���� ����ü.
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��.
	bool isKeyDown = false;

	// ���� �����ӿ� Ű�� ���Ⱦ����� Ȯ��.
	bool wasKeyDown = false;
};

// Ŀ���� ������ ������ �� ����� ������.
enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor
};

// ���� Ŭ����.
class Level;
class Actor;
class ScreenBuffer;
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�.
	void Run();

	// ���� �߰� �Լ�.
	void LoadLevel(Level* newLevel);

	// ���� �߰�/���� �Լ�.
	void AddActor(Actor* newActor, int depth = 0);
	void DestroyActor(Actor* targetActor);

	void Draw(const Vector2& position, vector<vector<Color>>& image);
	void Draw(const Vector2& position, const wchar_t* image, Color color = Color::White);
	void Draw(const Vector2& position, const wchar_t* image, int rightOffset, Color color = Color::White);

	// ȭ�� ��ǥ ���� �Լ�.
	void SetCursorType(CursorType cursorType);
	void SetCursorPosition(const Vector2& position);
	void SetCursorPosition(int x, int y);

	// ȭ�� ũ�� ��ȯ �Լ�.
	inline Vector2 ScreenSize() const { return screenSize; }

	// Ÿ�� ������ �ӵ� ���� �Լ�.
	void SetTargetFrameRate(float targetFrameRate);

	// �Է� ���� �Լ�.
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	Vector2 MousePosition() const;

	// �ʱ�ȭ �̹��� ����.
	void SetClearImage(ImageText* clearImage) { this->clearImage = clearImage; }

	// ���� ���� �Լ�.
	void QuitGame();

	// �̱��� ��ü ���� �Լ�.
	static Engine& Get();

protected:
	void ProcessInput();				// �Է� ó��.
	void Update(float deltaTime);		// Tick();
	void LateUpdate(float deltaTime);

	void Clear();						// ȭ�� �����.
	void Draw();						// Render();
	void Present();

	// ���� �������� Ű ���¸� �����ϴ� �Լ�.
	void SavePreviouseKeyStates();

	inline ScreenBuffer* GetRenderer() const { return renderTargets[currentRenderTargetIndex]; }
	void ClearImageBuffer();

protected:

	// Ÿ�� ������ ����(�ʴ� ������).
	float targetFrameRate = 60.0f;

	// �� ������ �ð� ��(����: ��).
	float targetOneFrameTime = 0.0f;

	// ������ �� ������ ����.
	bool quit;

	// Ű ���¸� �����ϴ� �迭.
	KeyState keyState[255];

	// �̱��� ������ ���� ���� ���� ����.
	static Engine* instance;

	// ���� ���� ����.
	Level* mainLevel = nullptr;

	// ȭ�� ũ��.
	Vector2 screenSize;

	// ���콺 ��ǥ ��ġ.
	Vector2 mousePosition;

	// ȭ�� ���� �� ����� ����(Buffer/Blob).
	CHAR_INFO* imageBuffer = nullptr;

	// ȭ�� ����.
	ScreenBuffer* renderTargets[2];
	int currentRenderTargetIndex = 0;

	// �ʱ�ȭ�� �̹���.
	ImageText* clearImage = nullptr;
};