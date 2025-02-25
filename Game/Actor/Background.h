#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

class Background : public Actor
{
	RTTI_DECLARATIONS(Background, Actor)

public:
	Background();

	virtual void BackgroundDraw() override;

private:
	ImageText* background = nullptr;
};