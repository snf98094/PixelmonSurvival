#pragma once
#include "Core.h"
#include "Math/Vector2.h"

struct Position
{
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{
	}

	int x, y;
};

class AStarNode
{
public:
	AStarNode(int x, int y, AStarNode* parent = nullptr)
		: position(x, y), parent(parent)
	{ }
	~AStarNode() = default;

	// ����� ��ġ.
	Position position;
	// ���� ��忡�� �̵� �������� ���.
	float gCost = 0.0f;
	// �̵� ��忡�� ��ǥ �������� ���(�޸���ƽ, ����)
	float hCost = 0.0f;
	// �� ����� ��ģ ���.
	float fCost = 0.0f;
	// ��ũ �ʵ�(�θ� ���).
	AStarNode* parent = nullptr;
};

class AStar
{
	// �̵� ���� ����ü.
	struct Direction
	{
		// ����
		int x = 0;
		int y = 0;

		// ���
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();
	vector<AStarNode*> FindPath(AStarNode* startNode, AStarNode* goalNode, const vector<vector<bool>>& grid);

private:
	// Ž���� �Ϸ��� �Ŀ� ���� ��θ� ��ȯ�ϴ� �Լ�.
	// ��ǥ���κ��� �θ� ��带 �������� ����.
	vector<AStarNode*> ConstructPath(AStarNode* goalNode);

	// hCost ��� �Լ�.
	float CalculateHeuristic(AStarNode* currentNode, AStarNode* goalNode);

	// Ž���Ϸ��� ��ġ�� ���� �ȿ� �ִ��� Ȯ���ϴ� �Լ�.
	bool IsInRange(int x, int y, const vector<vector<bool>>& grid);

	// �̹� �湮�� ��ġ���� Ȯ���ϴ� �Լ�.
	bool HasVisited(int x, int y, float gCost);

	// Ž���Ϸ��� ��ġ�� ��ǥ ��ġ���� Ȯ���ϴ� �Լ�.
	bool IsDestination(const AStarNode* node);

private:
	// ���� ����Ʈ.
	vector<AStarNode*> openList;
	// ���� ����Ʈ.
	vector<AStarNode*> closedList;
	// ���� ���.
	AStarNode* startNode = nullptr;
	// ��ǥ ���.
	AStarNode* goalNode = nullptr;
	// �����¿� �� �밢�� �̵� ���� �� ��� ���.
	vector<Direction> directions;
};