#include "Monster.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

Monster::Monster(GameLevel* level, string name, Vector2 position)
{
	this->level = level;
	this->position = position;

	string path = "Monster/" + name + "_";

	// 이동 애니메이션 추가.
	AnimationClip* moveClip = new AnimationClip(move, 0.6f);
	moveClip->AddImage(new ImageText((path + "Move01").c_str()), 0.0f);
	moveClip->AddImage(new ImageText((path + "Move02").c_str()), 0.2f);
	moveClip->AddImage(new ImageText((path + "Move03").c_str()), 0.4f);
	moveClip->AddImage(new ImageText((path + "Move04").c_str()), 0.6f);
	moveClip->AddImage(new ImageText((path + "Move05").c_str()), 0.8f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	// 애니메이터에 클립 저장.
	animator.AddClip(moveClip);

	// 재생 위치 이동.
	animator.SetPosition(position);

	// 기본 애니메이션 실행.
	SetState(MonsterState::Move);
}

void Monster::Update(float deltaTime)
{
	if (!target)
		return;

	// 대상과 벡터 거리.
	Vector2 length = target->Position() - position;

	// 대상과 길이가 targetInterval 보다 작다면 대상을 향해 이동.
	if (length.Magnitude() > targetInterval)
	{
		// 방향 벡터로 변환.
		Vector2 movePoint = length.Normalized();

		// 위치 이동.
		position += movePoint * speed * deltaTime;

		// 플레이어 재생 위치 이동.
		animator.SetPosition(position);

		// 반전 여부 적용.
		if (movePoint.x > 0.0f)
			animator.SetFlip(true);
		else if (movePoint.x < 0.0f)
			animator.SetFlip(false);

		// 현재 상태가 이동이 아니라면 이동 상태로 변경.
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

	// 현재 재생 중인 클립 저장.
	animationClip = animator.GetCurrentClip();
}

void Monster::SetTarget(Player& player)
{
	target = &player;
}