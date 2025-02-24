#include "Player.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"

Player::Player(GameLevel* level)
{
	this->level = level;

	warrior = new ImageText("Character/Warrior");
	warrior->SetDrawingPosition(Engine::Get().ScreenSize() / 2.0f);
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Player::Draw()
{
	warrior->Print();
}

void Player::LateUpdate(float deltaTime)
{
	
}