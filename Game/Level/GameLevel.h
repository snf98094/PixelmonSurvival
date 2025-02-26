#pragma once
#include "Level/Level.h"
#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "UI/NumberText.h"
#include "Image/ImageText.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void Draw() override;
	virtual void Update(float deltaTime) override;

private:
	Player* player = nullptr;

	// 플레이 중 획특한 코인.
	int coin = 0;
	// 플레이 중 획특한 점수.
	int score = 0;
};