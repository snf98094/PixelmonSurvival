#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

int main()
{
	//system("color 42");

	CheckMemoryLeak();
	//_CrtSetBreakAlloc(53476);
	Engine engine;
    engine.SetTargetFrameRate(60);
    engine.SetCursorType(CursorType::NoCursor);
	engine.LoadLevel(new GameLevel());
	engine.Run();
}