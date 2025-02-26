#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Background.h"
#include "Actor/Object.h"
#include <iostream>

GameLevel::GameLevel()
{
	player = new Player(this);
	AddActor(player);

	Monster* goblin = new Monster(this, "Goblin", Vector2(200.0f, 200.0f));
	AddActor(goblin);
	goblin->SetTarget(*player);

	Background* background = new Background();
	AddActor(background);

	Object* wood = new Object("Wood", Vector2(519.0f, 396.0f));
	AddActor(wood);

	Object* stone01 = new Object("Stone01", Vector2(303.0f, 229.0f));
	actors.push_back(stone01);

	Object* stone02 = new Object("Stone02", Vector2(387.0f, 176.0f));
	actors.push_back(stone02);
}

GameLevel::~GameLevel()
{

}

void GameLevel::Draw()
{
	Super::Draw();
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	char fpsMessage[50] = {};
	sprintf_s(fpsMessage, 50, "fps: %f\n", 1.0f / deltaTime);
	OutputDebugStringA(fpsMessage);
}