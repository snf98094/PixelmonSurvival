#pragma once
#include "Animation/Animator.h"
#include "Player.h"

class GameLevel;
class Monster : public Actor
{
	enum class MonsterState
	{
		Move,
		Die
	};

	RTTI_DECLARATIONS(Monster, Actor)
public:
	Monster(GameLevel* level, string name, Vector2 position);

	virtual void Update(float deltaTime) override;

	void SetState(MonsterState state);

	// ��ǥ ����.
	void SetTarget(Player& player);

private:
	// GameLevel ����.
	GameLevel* level;

	// ���� ����.
	MonsterState state = MonsterState::Move;

	// ��ǥ ����.
	Player* target;

	// ���� �ִϸ�����.
	Animator animator;
	// �÷��� ���� �ִϸ��̼� Ŭ��.
	AnimationClip* animationClip = nullptr;
	// ���� �ִϸ��̼� Ű.
	const char* move = "Move";

	// ���� �̵� �ӵ�.
	float speed = 40.0f;
	// ��ǥ�� ���� üũ.
	float targetInterval = 30.0f;
};