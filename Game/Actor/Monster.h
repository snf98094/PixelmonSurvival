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
	virtual void LateUpdate(float deltaTime) override;
	virtual void Draw() override;

	void SetState(MonsterState state);

	// 목표 지정.
	void SetTarget(Player& player);

private:
	// GameLevel 변수.
	GameLevel* level;

	// 몬스터 상태.
	MonsterState state = MonsterState::Move;

	// 목표 변수.
	Player* target;

	// 몬스터 애니메이터.
	Animator animator;
	// 플레이 중인 애니메이션 클립.
	AnimationClip* animationClip = nullptr;
	// 몬스터 애니메이션 키.
	const char* move = "Move";

	// 몬스터 이동 속도.
	float speed = 40.0f;
	// 목표와 간격 체크.
	float targetInterval = 30.0f;
	vector<Vector2> neviPoint;

	// 이동 길을 보여줄지 체크하는 변수.
	bool isMovePointDrawing = false;

	// 뎁스 변경용 이전 Y축 저장 변수.
	int prevY = 0;
};