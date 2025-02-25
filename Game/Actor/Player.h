#pragma once
#include "Animation/Animator.h"

class GameLevel;
class Player : public Actor
{
	enum class PlayerState
	{
		Idle,
		Move,
		Die
	};

	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(GameLevel* level);

	virtual void Update(float deltaTime) override;

	void SetState(PlayerState state);

private:
	// GameLevel ����.
	GameLevel* level;

	// �÷��̾� ����.
	PlayerState state = PlayerState::Idle;

	// �÷��̾� �ִϸ�����.
	Animator animator;
	// �÷��� ���� �ִϸ��̼� Ŭ��.
	AnimationClip* animationClip = nullptr;
	// �÷��̾� �ִϸ��̼� Ű.
	const char* idle = "Idle";
	const char* move = "Move";

	// �÷��̾� �̵� �ӵ�.
	float speed = 60.0f;
};