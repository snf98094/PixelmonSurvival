#pragma once
#include "Actor/Actor.h"
#include "Image/ImageText.h"

class Object : public Actor
{
	RTTI_DECLARATIONS(Object, Actor)

public:
	Object(string name, Vector2 position);
	~Object();

	virtual void ObjectDraw() override;

private:
	ImageText* object = nullptr;
};