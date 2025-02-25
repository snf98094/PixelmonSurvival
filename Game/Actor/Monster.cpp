#include "Monster.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

Monster::Monster(GameLevel* level, string name, Vector2 position)
{
	this->level = level;
	this->position = position;

	string path = "Monster/" + name + "_";

	// �̵� �ִϸ��̼� �߰�.
	AnimationClip* moveClip = new AnimationClip(move, 0.6f);
	moveClip->AddImage(new ImageText((path + "Move01").c_str()), 0.0f);
	moveClip->AddImage(new ImageText((path + "Move02").c_str()), 0.2f);
	moveClip->AddImage(new ImageText((path + "Move03").c_str()), 0.4f);
	moveClip->AddImage(new ImageText((path + "Move04").c_str()), 0.6f);
	moveClip->AddImage(new ImageText((path + "Move05").c_str()), 0.8f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	// �ִϸ����Ϳ� Ŭ�� ����.
	animator.AddClip(moveClip);

	// ��� ��ġ �̵�.
	animator.SetPosition(position);

	// �⺻ �ִϸ��̼� ����.
	SetState(MonsterState::Move);
}

void Monster::Update(float deltaTime)
{
	if (!target)
		return;

	// ���� ���� �Ÿ�.
	Vector2 length = target->Position() - position;

	// ���� ���̰� targetInterval ���� �۴ٸ� ����� ���� �̵�.
	if (length.Magnitude() > targetInterval)
	{
		// ���� ���ͷ� ��ȯ.
		Vector2 movePoint = length.Normalized();

		// ��ġ �̵�.
		position += movePoint * speed * deltaTime;

		// �÷��̾� ��� ��ġ �̵�.
		animator.SetPosition(position);

		// ���� ���� ����.
		if (movePoint.x > 0.0f)
			animator.SetFlip(true);
		else if (movePoint.x < 0.0f)
			animator.SetFlip(false);

		// ���� ���°� �̵��� �ƴ϶�� �̵� ���·� ����.
		if (animationClip != animator.GetClip(move))
			SetState(MonsterState::Move);
	}
}

void Monster::SetState(MonsterState state)
{
	this->state = state;

	switch (state)
	{
	case Monster::MonsterState::Die:
		break;

	case Monster::MonsterState::Move:
		animator.Play(move);
		break;
	}

	// ���� ��� ���� Ŭ�� ����.
	animationClip = animator.GetCurrentClip();
}

void Monster::SetTarget(Player& player)
{
	target = &player;
}