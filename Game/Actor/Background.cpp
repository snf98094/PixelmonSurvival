#include "Background.h"

Background::Background()
{
	background = new ImageText("Map");
}

void Background::BackgroundDraw()
{
	background->Print();
}