#include "GameLevel.h"
#include "Engine/Engine.h"

GameLevel::GameLevel()
{
	player = new Player(this);
	actors.push_back(player);

	Monster* goblin = new Monster(this, "Goblin", Vector2(200.0f, 200.0f));
	actors.push_back(goblin);
	goblin->SetTarget(*player);
}

GameLevel::~GameLevel()
{

}

void GameLevel::Draw()
{
	Super::Draw();
}