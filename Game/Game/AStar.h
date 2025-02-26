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

	// 노드의 위치.
	Position position;
	// 현재 노드에서 이동 노드까지의 비용.
	float gCost = 0.0f;
	// 이동 노드에서 목표 노드까지의 비용(휴리스틱, 추정)
	float hCost = 0.0f;
	// 두 비용을 합친 비용.
	float fCost = 0.0f;
	// 링크 필드(부모 노드).
	AStarNode* parent = nullptr;
};

class AStar
{
	// 이동 방향 구조체.
	struct Direction
	{
		// 방향
		int x = 0;
		int y = 0;

		// 비용
		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();
	vector<AStarNode*> FindPath(AStarNode* startNode, AStarNode* goalNode, const vector<vector<bool>>& grid);

private:
	// 탐색을 완료한 후에 최적 경로를 반환하는 함수.
	// 목표노드로부터 부모 노드를 역추적해 구함.
	vector<AStarNode*> ConstructPath(AStarNode* goalNode);

	// hCost 계산 함수.
	float CalculateHeuristic(AStarNode* currentNode, AStarNode* goalNode);

	// 탐색하려는 위치가 범위 안에 있는지 확인하는 함수.
	bool IsInRange(int x, int y, const vector<vector<bool>>& grid);

	// 이미 방문한 위치인지 확인하는 함수.
	bool HasVisited(int x, int y, float gCost);

	// 탐색하려는 위치가 목표 위치인지 확인하는 함수.
	bool IsDestination(const AStarNode* node);

private:
	// 열린 리스트.
	vector<AStarNode*> openList;
	// 닫힌 리스트.
	vector<AStarNode*> closedList;
	// 시작 노드.
	AStarNode* startNode = nullptr;
	// 목표 노드.
	AStarNode* goalNode = nullptr;
	// 상하좌우 및 대각선 이동 방향 및 비용 계산.
	vector<Direction> directions;
};