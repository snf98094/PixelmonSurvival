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

	// �÷��� �� ȹƯ�� ����.
	int coin = 0;
	// �÷��� �� ȹƯ�� ����.
	int score = 0;
};