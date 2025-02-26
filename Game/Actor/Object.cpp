#include "Object.h"

Object::Object(string name, Vector2 position)
{
	object = new ImageText(("Object/" + name).c_str());
	object->SetDrawingPosition(position);
}

Object::~Object()
{
	delete object;
}

void Object::Draw()
{
	object->Print();
}