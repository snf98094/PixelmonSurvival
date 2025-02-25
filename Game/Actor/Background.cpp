#include "Background.h"
#include "Engine/Engine.h"

Background::Background()
{
	background = new ImageText("Map");

	int rows = Engine::Get().ScreenSize().x;
	blocks = new bool* [rows];
	for (int x = 0; x < rows; x++)
		blocks[x] = new bool[Engine::Get().ScreenSize().y]();

	SetBloack();
}

void Background::BackgroundDraw()
{
	background->Print();

	if (!isBlockOpen)
		return;

	int rows = Engine::Get().ScreenSize().x;
	for (int x = 0; x < rows; x++)
	{
		int cols = Engine::Get().ScreenSize().y;
		for (int y = 0; y < cols; y++)
			if (blocks[x][y])
				Engine::Get().Draw(Vector2(x, y), L"бс", Color::Red);
	}
}

void Background::LateUpdate(float delatTime)
{
	if (Engine::Get().GetKeyDown(VK_LBUTTON))
		isBlockOpen = !isBlockOpen;
}

void Background::SetBloack()
{
	for (int x = 152; x <= 161; x++)
		for (int y = 0; y <= 484; y++)
			blocks[x][y] = true;

	for (int x = 152; x <= 205; x++)
		for (int y = 483; y <= 505; y++)
			blocks[x][y] = true;

	for (int x = 195; x <= 205; x++)
		for (int y = 505; y <= 609; y++)
			blocks[x][y] = true;

	for (int x = 399; x <= 408; x++)
		for (int y = 0; y <= 77; y++)
			blocks[x][y] = true;

	for (int x = 228; x <= 399; x++)
		for (int y = 53; y <= 77; y++)
			blocks[x][y] = true;

	for (int x = 228; x <= 237; x++)
		for (int y = 77; y <= 320; y++)
			blocks[x][y] = true;

	for (int x = 237; x <= 323; x++)
		for (int y = 310; y <= 320; y++)
			blocks[x][y] = true;

	for (int x = 313; x <= 323; x++)
		for (int y = 310; y <= 406; y++)
			blocks[x][y] = true;

	for (int x = 323; x <= 795; x++)
		for (int y = 396; y <= 406; y++)
			blocks[x][y] = true;

	for (int x = 786; x <= 795; x++)
		for (int y = 406; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 270; x <= 786; x++)
		for (int y = 482; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 270; x <= 280; x++)
		for (int y = 482; y <= 609; y++)
			blocks[x][y] = true;

	for (int x = 538; x <= 548; x++)
		for (int y = 0; y <= 95; y++)
			blocks[x][y] = true;

	for (int x = 614; x <= 623; x++)
		for (int y = 0; y <= 95; y++)
			blocks[x][y] = true;

	for (int x = 839; x <= 849; x++)
		for (int y = 96; y <= 309; y++)
			blocks[x][y] = true;

	for (int x = 849; x <= 935; x++)
		for (int y = 96; y <= 105; y++)
			blocks[x][y] = true;

	for (int x = 925; x <= 935; x++)
		for (int y = 0; y <= 96; y++)
			blocks[x][y] = true;

	for (int x = 916; x <= 924; x++)
		for (int y = 181; y <= 309; y++)
			blocks[x][y] = true;

	for (int x = 925; x <= 935; x++)
		for (int y = 181; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 935; x <= 999; x++)
		for (int y = 482; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1009; x++)
		for (int y = 0; y <= 20; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1009; x++)
		for (int y = 96; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 1010; x <= 1096; x++)
		for (int y = 9; y <= 20; y++)
			blocks[x][y] = true;

	for (int x = 1010; x <= 1096; x++)
		for (int y = 9; y <= 20; y++)
			blocks[x][y] = true;

	for (int x = 1010; x <= 1019; x++)
		for (int y = 96; y <= 223; y++)
			blocks[x][y] = true;

	for (int x = 1086; x <= 1096; x++)
		for (int y = 20; y <= 223; y++)
			blocks[x][y] = true;

	for (int x = 1010; x <= 1182; x++)
		for (int y = 267; y <= 292; y++)
			blocks[x][y] = true;

	for (int x = 1172; x <= 1182; x++)
		for (int y = 0; y <= 267; y++)
			blocks[x][y] = true;

	for (int x = 66; x <= 152; x++)
		for (int y = 439; y <= 448; y++)
			blocks[x][y] = true;

	for (int x = 66; x <= 76; x++)
		for (int y = 449; y <= 660; y++)
			blocks[x][y] = true;

	for (int x = 76; x <= 1096; x++)
		for (int y = 653; y <= 660; y++)
			blocks[x][y] = true;

	for (int x = 1010; x <= 1096; x++)
		for (int y = 439; y <= 449; y++)
			blocks[x][y] = true;

	for (int x = 1086; x <= 1096; x++)
		for (int y = 450; y <= 653; y++)
			blocks[x][y] = true;

	for (int x = 238; x <= 408; x++)
		for (int y = 78; y <= 137; y++)
			blocks[x][y] = true;

	for (int x = 409; x <= 538; x++)
		for (int y = 0; y <= 51; y++)
			blocks[x][y] = true;

	for (int x = 624; x <= 749; x++)
		for (int y = 0; y <= 51; y++)
			blocks[x][y] = true;

	for (int x = 842; x <= 924; x++)
		for (int y = 0; y <= 51; y++)
			blocks[x][y] = true;

	for (int x = 153; x <= 195; x++)
		for (int y = 506; y <= 566; y++)
			blocks[x][y] = true;

	for (int x = 281; x <= 795; x++)
		for (int y = 506; y <= 566; y++)
			blocks[x][y] = true;

	for (int x = 925; x <= 1010; x++)
		for (int y = 506; y <= 566; y++)
			blocks[x][y] = true;

	for (int x = 77; x <= 118; x++)
		for (int y = 449; y <= 477; y++)
			blocks[x][y] = true;

	for (int x = 121; x <= 152; x++)
		for (int y = 455; y <= 506; y++)
			blocks[x][y] = true;

	for (int x = 84; x <= 112; x++)
		for (int y = 627; y <= 647; y++)
			blocks[x][y] = true;

	for (int x = 164; x <= 191; x++)
		for (int y = 567; y <= 575; y++)
			blocks[x][y] = true;

	for (int x = 168; x <= 186; x++)
		for (int y = 576; y <= 581; y++)
			blocks[x][y] = true;

	for (int x = 300; x <= 326; x++)
		for (int y = 138; y <= 147; y++)
			blocks[x][y] = true;

	for (int x = 304; x <= 320; x++)
		for (int y = 148; y <= 152; y++)
			blocks[x][y] = true;

	for (int x = 286; x <= 319; x++)
		for (int y = 241; y <= 263; y++)
			blocks[x][y] = true;

	for (int x = 370; x <= 403; x++)
		for (int y = 189; y <= 211; y++)
			blocks[x][y] = true;

	for (int x = 371; x <= 403; x++)
		for (int y = 317; y <= 339; y++)
			blocks[x][y] = true;

	for (int x = 501; x <= 535; x++)
		for (int y = 44; y <= 78; y++)
			blocks[x][y] = true;

	for (int x = 691; x <= 724; x++)
		for (int y = 44; y <= 75; y++)
			blocks[x][y] = true;

	for (int x = 851; x <= 893; x++)
		for (int y = 44; y <= 82; y++)
			blocks[x][y] = true;

	for (int x = 616; x <= 657; x++)
		for (int y = 383; y <= 396; y++)
			blocks[x][y] = true;

	for (int x = 603; x <= 645; x++)
		for (int y = 229; y <= 254; y++)
			blocks[x][y] = true;

	for (int x = 809; x <= 839; x++)
		for (int y = 147; y <= 212; y++)
			blocks[x][y] = true;

	for (int x = 558; x <= 598; x++)
		for (int y = 427; y <= 461; y++)
			blocks[x][y] = true;

	for (int x = 720; x <= 761; x++)
		for (int y = 427; y <= 461; y++)
			blocks[x][y] = true;

	for (int x = 947; x <= 988; x++)
		for (int y = 247; y <= 281; y++)
			blocks[x][y] = true;

	for (int x = 947; x <= 988; x++)
		for (int y = 427; y <= 461; y++)
			blocks[x][y] = true;

	for (int x = 1026; x <= 1067; x++)
		for (int y = 473; y <= 533; y++)
			blocks[x][y] = true;

	for (int x = 1050; x <= 1078; x++)
		for (int y = 628; y <= 647; y++)
			blocks[x][y] = true;

	for (int x = 1139; x <= 1166; x++)
		for (int y = 243; y <= 262; y++)
			blocks[x][y] = true;

	for (int x = 1096; x <= 1127; x++)
		for (int y = 95; y <= 160; y++)
			blocks[x][y] = true;

	for (int x = 899; x <= 922; x++)
		for (int y = 520; y <= 543; y++)
			blocks[x][y] = true;

	for (int x = 941; x <= 971; x++)
		for (int y = 567; y <= 588; y++)
			blocks[x][y] = true;
}