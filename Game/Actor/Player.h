#pragma once
#include "Animation/Animator.h"

class GameLevel;
class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player(GameLevel* level);
	~Player();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void LateUpdate(float deltaTime) override;

private:
	// GameLevel 변수.
	GameLevel* level;

	// 워리어 캐릭터 이미지.
	ImageText* warrior;

	// 플레이어 위치.
	Vector2 position = Vector2(0.0f);
	// 플레이어 이동 속도.
	float speed = 30.0f;
};