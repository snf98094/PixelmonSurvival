#pragma once
#include "Animation/Animator.h"

class GameLevel;
class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player(GameLevel* level);
	~Player();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void LateUpdate(float deltaTime) override;

private:
	// GameLevel º¯¼ö.
	GameLevel* level;

	ImageText* warrior;
};