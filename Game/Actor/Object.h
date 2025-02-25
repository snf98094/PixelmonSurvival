#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

class Object : public Actor
{
	RTTI_DECLARATIONS(Object, Actor)

public:
	Object();

	virtual void BackgroundDraw() override;

private:
	ImageText* object = nullptr;
};