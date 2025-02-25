#include "Player.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"

Player::Player(GameLevel* level)
{
	this->level = level;

	// ������� ����.
	position = Engine::Get().ScreenSize() / 2.0f;

	// �⺻ �ִϸ��̼� �߰�.
	AnimationClip* idleClip = new AnimationClip(idle, 0.8f);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle01"), 0.0f);
	idleClip->AddImage(new ImageText("Character/Warrior_Idle02"), 0.5f);
	idleClip->SetLoop(true);
	level->AddActor(idleClip);

	// �̵� �ִϸ��̼� �߰�.
	AnimationClip* moveClip = new AnimationClip(move, 0.6f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move01"), 0.0f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move02"), 0.2f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move03"), 0.4f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move04"), 0.6f);
	moveClip->AddImage(new ImageText("Character/Warrior_Move05"), 0.8f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	// �ִϸ����Ϳ� Ŭ�� ����.
	playerAnimator.AddClip(idleClip);
	playerAnimator.AddClip(moveClip);

	// ��� ��ġ �̵�.
	playerAnimator.SetPosition(position);

	// �⺻ �ִϸ��̼� ����.
	SetState(PlayerState::Idle);
}

void Player::Update(float deltaTime)
{
	// �̵��� ��.
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
		// ���� ���ͷ� ��ȯ.
		movePoint = movePoint.Normalized();

		// ��ġ �̵�.
		position = position + movePoint * speed * deltaTime;

		// �÷��̾� ��� ��ġ �̵�.
		playerAnimator.SetPosition(position);

		// ���� ���� ����.
		if (movePoint.x > 0.0f)
			playerAnimator.SetFlip(true);
		else if (movePoint.x < 0.0f)
			playerAnimator.SetFlip(false);

		// ���� ���°� �̵��� �ƴ϶�� �̵� ���·� ����.
		if (animationClip != playerAnimator.GetClip(move))
			SetState(PlayerState::Move);
	}
	else if (animationClip != playerAnimator.GetClip(idle))
		// �⺻ ���·� ����.
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

	// ���� ��� ���� Ŭ�� ����.
	animationClip = playerAnimator.GetCurrentClip();
}