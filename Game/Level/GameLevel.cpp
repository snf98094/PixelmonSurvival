#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Background.h"

GameLevel::GameLevel()
{
	player = new Player(this);
	actors.push_back(player);

	Monster* goblin = new Monster(this, "Goblin", Vector2(200.0f, 200.0f));
	actors.push_back(goblin);
	goblin->SetTarget(*player);

	Background* background = new Background();
	actors.push_back(background);
}

GameLevel::~GameLevel()
{

}

void GameLevel::Draw()
{
	Super::Draw();
}