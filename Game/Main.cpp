#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

int main()
{
	//system("color 42");

	CheckMemoryLeak();
	//_CrtSetBreakAlloc(15124);
	Engine engine;
    engine.SetTargetFrameRate(20);
    engine.SetCursorType(CursorType::NoCursor);
	engine.LoadLevel(new GameLevel());
	engine.Run();
}