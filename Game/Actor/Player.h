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
	virtual void LateUpdate(float deltaTime) override;
	virtual void Draw() override;

	void SetState(PlayerState state);

private:
	// GameLevel 변수.
	GameLevel* level;

	// 플레이어 상태.
	PlayerState state = PlayerState::Idle;

	// 플레이어 애니메이터.
	Animator animator;
	// 플레이 중인 애니메이션 클립.
	AnimationClip* animationClip = nullptr;
	// 플레이어 애니메이션 키.
	const char* idle = "Idle";
	const char* move = "Move";

	// 플레이어 이동 속도.
	float speed = 90.0f;

	// 뎁스 변경용 이전 Y축 저장 변수.
	int prevY = 0;
};