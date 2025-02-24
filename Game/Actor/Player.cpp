#include "Player.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"

Player::Player(GameLevel* level)
{
	this->level = level;

	// 가운데에서 시작.
	position = Engine::Get().ScreenSize() / 2.0f;
	warrior = new ImageText("Character/Warrior");
	warrior->SetDrawingPosition(position);
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	if (Engine::Get().GetKey(VK_LEFT))
		position.x = (float)position.x - (float)speed * deltaTime;
	if (Engine::Get().GetKey(VK_RIGHT))
		position.x = (float)position.x + (float)speed * deltaTime;
	if (Engine::Get().GetKey(VK_UP))
		position.y = (float)position.y - (float)speed * deltaTime;
	if (Engine::Get().GetKey(VK_DOWN))
		position.y = (float)position.y + (float)speed * deltaTime;

	warrior->SetDrawingPosition(position);
}

void Player::Draw()
{
	warrior->Print();
}

void Player::LateUpdate(float deltaTime)
{
	
}