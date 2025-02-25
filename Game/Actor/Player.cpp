#include "Player.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"

Player::Player(GameLevel* level)
{
	this->level = level;

	// 가운데에서 시작.
	position = Engine::Get().ScreenSize() / 2.0f;

	// 기본 애니메이션 추가.
	AnimationClip* idleClip = new AnimationClip(idle, 0.8f);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle01"), 0.0f);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle02"), 0.5f);
	idleClip->SetLoop(true);
	level->AddActor(idleClip);

	// 이동 애니메이션 추가.
	AnimationClip* moveClip = new AnimationClip(move, 0.6f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move01"), 0.0f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move02"), 0.2f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move03"), 0.4f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move04"), 0.6f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move05"), 0.8f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	// 애니메이터에 클립 저장.
	playerAnimator.AddClip(idleClip);
	playerAnimator.AddClip(moveClip);

	// 재생 위치 이동.
	playerAnimator.SetPosition(position);

	// 기본 애니메이션 실행.
	SetState(PlayerState::Idle);
}

void Player::Update(float deltaTime)
{
	// 이동할 값.
	Vector2 movePoint;

	if (Engine::Get().GetKey(VK_LEFT))
		movePoint.x = -1.0f;
	if (Engine::Get().GetKey(VK_RIGHT))
		movePoint.x = 1.0f;
	if (Engine::Get().GetKey(VK_UP))
		movePoint.y = -1.0f;
	if (Engine::Get().GetKey(VK_DOWN))
		movePoint.y = 1.0f;

	if (movePoint != Vector2(0.0f, 0.0f))
	{
		// 방향 벡터로 변환.
		movePoint = movePoint.Normalized();

		// 위치 이동.
		position = position + movePoint * speed * deltaTime;

		// 플레이어 재생 위치 이동.
		playerAnimator.SetPosition(position);

		// 반전 여부 적용.
		if (movePoint.x > 0.0f)
			playerAnimator.SetFlip(true);
		else if (movePoint.x < 0.0f)
			playerAnimator.SetFlip(false);

		// 현재 상태가 이동이 아니라면 이동 상태로 변경.
		if (animationClip != playerAnimator.GetClip(move))
			SetState(PlayerState::Move);
	}
	else if (animationClip != playerAnimator.GetClip(idle))
		// 기본 상태로 변경.
		SetState(PlayerState::Idle);
}

void Player::SetState(PlayerState state)
{
	this->state = state;

	switch (state)
	{
	case Player::PlayerState::Idle:
		playerAnimator.Play(idle);
		break;

	case Player::PlayerState::Die:
		break;

	case Player::PlayerState::Move:
		playerAnimator.Play(move);
		break;
	}

	// 현재 재생 중인 클립 저장.
	animationClip = playerAnimator.GetCurrentClip();
}