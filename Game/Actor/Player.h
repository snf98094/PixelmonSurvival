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
	// GameLevel ����.
	GameLevel* level;

	// ������ ĳ���� �̹���.
	ImageText* warrior;

	// �÷��̾� ��ġ.
	Vector2 position = Vector2(0.0f);
	// �÷��̾� �̵� �ӵ�.
	float speed = 30.0f;
};