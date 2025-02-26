#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

class Background : public Actor
{
	RTTI_DECLARATIONS(Background, Actor)

public:
	Background();
	~Background();

	virtual void BackgroundDraw() override;
	virtual void Update(float delatTime) override;

	// ������ ���� üũ.
	void SetBloack();
	// AStar�� �׸��� ����.
	void SetAStarGrid();

	// �̵� ���� ��ġ üũ
	bool CheckMovePoint(Vector2 position);

	// ��� ��ü Getter.
	static Background& Get();
	// AStar�� �׸���.
	vector<vector<bool>>& GetAStarGrid() { return aStarGrid; }
	// AStar�� ��ǥ ��ȯ.
	Vector2 GetAStarPosition(Vector2 position);
	// AStar�� �� ����.
	int GetGridInterval() { return gridInterval; }

private:
	// �ν��Ͻ� ����.
	static Background* instance;

	// ��� �̹���.
	ImageText* background = nullptr;
	// ������ ���� üũ�� 2���� �迭.
	bool** blocks;
	bool isBlockOpen = false;
	// AStar�� �׸���.
	vector<vector<bool>> aStarGrid;
	// AStar�� �� ����.
	int gridInterval = 10;
};