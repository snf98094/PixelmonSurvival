#include "Monster.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Game/AStar.h"
#include "Background.h"

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

	float magnitude = (target->Position() - position).Magnitude();
	if (magnitude < targetInterval)
		return;

	// AStar ��ü.
	AStar aStar;

	// �ʿ��� ���� ��ġ ��ǥ ��ġ �˻�.
	Vector2 startPosition = Background::Get().GetAStarPosition(position);
	Vector2 goalPosition = Background::Get().GetAStarPosition(target->Position());
	AStarNode* startNode = new AStarNode(startPosition.x, startPosition.y);
	AStarNode goalNode(goalPosition.x, goalPosition.y);
	vector<vector<bool>>& grid = Background::Get().GetAStarGrid();

	// ��� Ž��.
	vector<AStarNode*> path = aStar.FindPath(startNode, &goalNode, grid);
	if (path.size() == 0)
		return;

	// ���� ���� �Ÿ�.
	Vector2 targetPosition = Vector2(path[1]->position.x, path[1]->position.y) * Background::Get().GetGridInterval();
	Vector2 length = targetPosition - position;

	// ���� ���̰� targetInterval ���� �۴ٸ� ����� ���� �̵�.
	if (length.Magnitude() > 0)
	{
		// ���� ���ͷ� ��ȯ.
		Vector2 movePoint = length.Normalized();

		// ��ġ �̵�.
		position += movePoint * speed * deltaTime;

		// �÷��̾� ��� ��ġ �̵�.
		animator.SetPosition(position);

		// ���� ���� ����.
		if (movePoint.x > 0.5f)
			animator.SetFlip(true);
		else if (movePoint.x < -0.5f)
			animator.SetFlip(false);

		// ���� ���°� �̵��� �ƴ϶�� �̵� ���·� ����.
		if (animationClip != animator.GetClip(move))
			SetState(MonsterState::Move);
	}

	if (isMovePointDrawing)
	{
		int size = path.size();
		for (int i = 1; i < size; i++)
			Engine::Get().Draw(Vector2(path[i]->position.x, path[i]->position.y), L"��", Color::Blue);
	}
}

void Monster::LateUpdate(float deltaTime)
{
	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		Vector2 mousePoint = Engine::Get().MousePosition();
		Vector2 monsterSize = animationClip->GetImage()->GetSize();
		if (mousePoint.x > position.x - monsterSize.x * 0.5f &&
			mousePoint.x < position.x + monsterSize.x * 0.5f &&
			mousePoint.y > position.y - monsterSize.y &&
			mousePoint.y < position.y)
		{
			isMovePointDrawing = !isMovePointDrawing;
		}
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