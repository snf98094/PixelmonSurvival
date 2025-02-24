#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

class Background : public Actor
{
	RTTI_DECLARATIONS(Background, Actor)

public:
	Background();

	virtual void BackgroundDraw() override;
	virtual void LateUpdate(float delatTime) override;

	void SetBloack();

private:
	ImageText* background = nullptr;
	bool** blocks;
	bool isBlockOpen = true;
};