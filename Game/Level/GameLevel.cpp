#include "GameLevel.h"
#include "Engine/Engine.h"

GameLevel::GameLevel()
{
	player = new Player(this);
	actors.push_back(player);
}

GameLevel::~GameLevel()
{

}

void GameLevel::Draw()
{
	Super::Draw();
}