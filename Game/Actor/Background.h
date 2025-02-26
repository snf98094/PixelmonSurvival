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

	// 못가는 지형 체크.
	void SetBloack();
	// AStar용 그리드 세팅.
	void SetAStarGrid();

	// 이동 가능 위치 체크
	bool CheckMovePoint(Vector2 position);

	// 배경 객체 Getter.
	static Background& Get();
	// AStar용 그리드.
	vector<vector<bool>>& GetAStarGrid() { return aStarGrid; }
	// AStar용 좌표 변환.
	Vector2 GetAStarPosition(Vector2 position);
	// AStar용 맵 간격.
	int GetGridInterval() { return gridInterval; }

private:
	// 인스턴스 변수.
	static Background* instance;

	// 배경 이미지.
	ImageText* background = nullptr;
	// 못가는 지형 체크용 2차원 배열.
	bool** blocks;
	bool isBlockOpen = false;
	// AStar용 그리드.
	vector<vector<bool>> aStarGrid;
	// AStar용 맵 간격.
	int gridInterval = 10;
};