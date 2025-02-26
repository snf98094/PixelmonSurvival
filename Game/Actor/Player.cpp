#include "Player.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Background.h"

Player::Player(GameLevel* level)
{
	this->level = level;

	// 가운데에서 시작.
	position = Engine::Get().ScreenSize() / 2.0f;

	// 기본 애니메이션 추가.
	AnimationClip* idleClip = new AnimationClip(idle, 0.8f, true);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle01"), 0.0f);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle02"), 0.5f);
	idleClip->SetLoop(true);
	level->AddActor(idleClip);

	// 이동 애니메이션 추가.
	AnimationClip* moveClip = new AnimationClip(move, 0.6f, true);
	moveClip->AddImage(new ImageText("Character/Warrior_Move01"), 0.0f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move02"), 0.2f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move03"), 0.4f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move04"), 0.6f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move05"), 0.8f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	// 애니메이터에 클립 저장.
	animator.AddClip(idleClip);
	animator.AddClip(moveClip);

	// 재생 위치 이동.
	animator.SetPosition(position);

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
		// 현재 상태가 이동이 아니라면 이동 상태로 변경.
		if (animationClip != animator.GetClip(move))
			SetState(PlayerState::Move);

		// 반전 여부 적용.
		if (movePoint.x > 0.0f)
			animator.SetFlip(true);
		else if (movePoint.x < 0.0f)
			animator.SetFlip(false);

		// 방향 벡터로 변환.
		movePoint = movePoint.Normalized();

		// 이동할 위치값.
		Vector2 movePosition = position + movePoint * speed * deltaTime;

		// 이동 가능 여부 체크.
		if (!Background::Get().CheckMovePoint(movePosition))
			return;

		// 위치 이동.
		position = movePosition;

		// 플레이어 재생 위치 이동.
		animator.SetPosition(position);
	}
	else if (animationClip != animator.GetClip(idle))
		// 기본 상태로 변경.
		SetState(PlayerState::Idle);
}

void Player::SetState(PlayerState state)
{
	this->state = state;

	switch (state)
	{
	case Player::PlayerState::Idle:
		animator.Play(idle);
		break;

	case Player::PlayerState::Die:
		break;

	case Player::PlayerState::Move:
		animator.Play(move);
		break;
	}

	// 현재 재생 중인 클립 저장.
	animationClip = animator.GetCurrentClip();
}