#include "Background.h"
#include "Engine/Engine.h"

// 스태틱 변수 초기화.
Background* Background::instance = nullptr;

Background::Background()
{
	instance = this;

	background = new ImageText("Map");

	int rows = Engine::Get().ScreenSize().x;
	blocks = new bool* [rows];
	for (int x = 0; x < rows; x++)
		blocks[x] = new bool[Engine::Get().ScreenSize().y]();

	SetBloack();
	SetAStarGrid();

	Engine::Get().SetClearImage(background);
}

Background::~Background()
{
	delete background;

	int rows = Engine::Get().ScreenSize().x;
	for (int x = 0; x < rows; x++)
		delete[] blocks[x];
	delete[] blocks;
}

void Background::Draw()
{
	//background->Print();

	if (!isBlockOpen)
		return;

	int rows = Engine::Get().ScreenSize().x;
	for (int x = 0; x < rows; x++)
	{
		int cols = Engine::Get().ScreenSize().y;
		for (int y = 0; y < cols; y++)
			if (blocks[x][y])
				Engine::Get().Draw(Vector2(x, y), L"■", Color::Red);
	}
}

//void Background::SetBloack()
//{
//	for (int x = 152; x <= 161; x++)
//		for (int y = 0; y <= 484; y++)
//			blocks[x][y] = true;
//
//	for (int x = 152; x <= 205; x++)
//		for (int y = 483; y <= 505; y++)
//			blocks[x][y] = true;
//
//	for (int x = 195; x <= 205; x++)
//		for (int y = 505; y <= 609; y++)
//			blocks[x][y] = true;
//
//	for (int x = 399; x <= 408; x++)
//		for (int y = 0; y <= 77; y++)
//			blocks[x][y] = true;
//
//	for (int x = 228; x <= 399; x++)
//		for (int y = 53; y <= 77; y++)
//			blocks[x][y] = true;
//
//	for (int x = 228; x <= 237; x++)
//		for (int y = 77; y <= 320; y++)
//			blocks[x][y] = true;
//
//	for (int x = 237; x <= 323; x++)
//		for (int y = 310; y <= 320; y++)
//			blocks[x][y] = true;
//
//	for (int x = 313; x <= 323; x++)
//		for (int y = 310; y <= 406; y++)
//			blocks[x][y] = true;
//
//	for (int x = 323; x <= 795; x++)
//		for (int y = 396; y <= 406; y++)
//			blocks[x][y] = true;
//
//	for (int x = 786; x <= 795; x++)
//		for (int y = 406; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 270; x <= 786; x++)
//		for (int y = 482; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 270; x <= 280; x++)
//		for (int y = 482; y <= 609; y++)
//			blocks[x][y] = true;
//
//	for (int x = 538; x <= 548; x++)
//		for (int y = 0; y <= 95; y++)
//			blocks[x][y] = true;
//
//	for (int x = 614; x <= 623; x++)
//		for (int y = 0; y <= 95; y++)
//			blocks[x][y] = true;
//
//	for (int x = 839; x <= 849; x++)
//		for (int y = 96; y <= 309; y++)
//			blocks[x][y] = true;
//
//	for (int x = 849; x <= 935; x++)
//		for (int y = 96; y <= 105; y++)
//			blocks[x][y] = true;
//
//	for (int x = 925; x <= 935; x++)
//		for (int y = 0; y <= 96; y++)
//			blocks[x][y] = true;
//
//	for (int x = 916; x <= 924; x++)
//		for (int y = 181; y <= 309; y++)
//			blocks[x][y] = true;
//
//	for (int x = 925; x <= 935; x++)
//		for (int y = 181; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 935; x <= 999; x++)
//		for (int y = 482; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1000; x <= 1009; x++)
//		for (int y = 0; y <= 20; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1000; x <= 1009; x++)
//		for (int y = 96; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1010; x <= 1096; x++)
//		for (int y = 9; y <= 20; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1010; x <= 1096; x++)
//		for (int y = 9; y <= 20; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1010; x <= 1019; x++)
//		for (int y = 96; y <= 223; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1086; x <= 1096; x++)
//		for (int y = 20; y <= 223; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1010; x <= 1182; x++)
//		for (int y = 267; y <= 292; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1172; x <= 1182; x++)
//		for (int y = 0; y <= 267; y++)
//			blocks[x][y] = true;
//
//	for (int x = 66; x <= 152; x++)
//		for (int y = 439; y <= 448; y++)
//			blocks[x][y] = true;
//
//	for (int x = 66; x <= 76; x++)
//		for (int y = 449; y <= 660; y++)
//			blocks[x][y] = true;
//
//	for (int x = 76; x <= 1096; x++)
//		for (int y = 653; y <= 660; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1010; x <= 1096; x++)
//		for (int y = 439; y <= 449; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1086; x <= 1096; x++)
//		for (int y = 450; y <= 653; y++)
//			blocks[x][y] = true;
//
//	for (int x = 238; x <= 408; x++)
//		for (int y = 78; y <= 137; y++)
//			blocks[x][y] = true;
//
//	for (int x = 409; x <= 538; x++)
//		for (int y = 0; y <= 51; y++)
//			blocks[x][y] = true;
//
//	for (int x = 624; x <= 749; x++)
//		for (int y = 0; y <= 51; y++)
//			blocks[x][y] = true;
//
//	for (int x = 842; x <= 924; x++)
//		for (int y = 0; y <= 51; y++)
//			blocks[x][y] = true;
//
//	for (int x = 153; x <= 195; x++)
//		for (int y = 506; y <= 566; y++)
//			blocks[x][y] = true;
//
//	for (int x = 281; x <= 795; x++)
//		for (int y = 506; y <= 566; y++)
//			blocks[x][y] = true;
//
//	for (int x = 925; x <= 1010; x++)
//		for (int y = 506; y <= 566; y++)
//			blocks[x][y] = true;
//
//	for (int x = 77; x <= 118; x++)
//		for (int y = 449; y <= 477; y++)
//			blocks[x][y] = true;
//
//	for (int x = 121; x <= 152; x++)
//		for (int y = 455; y <= 506; y++)
//			blocks[x][y] = true;
//
//	for (int x = 84; x <= 112; x++)
//		for (int y = 627; y <= 647; y++)
//			blocks[x][y] = true;
//
//	for (int x = 164; x <= 191; x++)
//		for (int y = 567; y <= 575; y++)
//			blocks[x][y] = true;
//
//	for (int x = 168; x <= 186; x++)
//		for (int y = 576; y <= 581; y++)
//			blocks[x][y] = true;
//
//	for (int x = 300; x <= 326; x++)
//		for (int y = 138; y <= 147; y++)
//			blocks[x][y] = true;
//
//	for (int x = 304; x <= 320; x++)
//		for (int y = 148; y <= 152; y++)
//			blocks[x][y] = true;
//
//	for (int x = 286; x <= 319; x++)
//		for (int y = 241; y <= 263; y++)
//			blocks[x][y] = true;
//
//	for (int x = 370; x <= 403; x++)
//		for (int y = 189; y <= 211; y++)
//			blocks[x][y] = true;
//
//	for (int x = 371; x <= 403; x++)
//		for (int y = 317; y <= 339; y++)
//			blocks[x][y] = true;
//
//	for (int x = 501; x <= 535; x++)
//		for (int y = 44; y <= 78; y++)
//			blocks[x][y] = true;
//
//	for (int x = 691; x <= 724; x++)
//		for (int y = 44; y <= 75; y++)
//			blocks[x][y] = true;
//
//	for (int x = 851; x <= 893; x++)
//		for (int y = 44; y <= 82; y++)
//			blocks[x][y] = true;
//
//	for (int x = 616; x <= 657; x++)
//		for (int y = 383; y <= 396; y++)
//			blocks[x][y] = true;
//
//	for (int x = 603; x <= 645; x++)
//		for (int y = 229; y <= 254; y++)
//			blocks[x][y] = true;
//
//	for (int x = 809; x <= 839; x++)
//		for (int y = 147; y <= 212; y++)
//			blocks[x][y] = true;
//
//	for (int x = 558; x <= 598; x++)
//		for (int y = 427; y <= 461; y++)
//			blocks[x][y] = true;
//
//	for (int x = 720; x <= 761; x++)
//		for (int y = 427; y <= 461; y++)
//			blocks[x][y] = true;
//
//	for (int x = 947; x <= 988; x++)
//		for (int y = 247; y <= 281; y++)
//			blocks[x][y] = true;
//
//	for (int x = 947; x <= 988; x++)
//		for (int y = 427; y <= 461; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1026; x <= 1067; x++)
//		for (int y = 473; y <= 533; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1050; x <= 1078; x++)
//		for (int y = 628; y <= 647; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1139; x <= 1166; x++)
//		for (int y = 243; y <= 262; y++)
//			blocks[x][y] = true;
//
//	for (int x = 1096; x <= 1127; x++)
//		for (int y = 95; y <= 160; y++)
//			blocks[x][y] = true;
//
//	for (int x = 899; x <= 922; x++)
//		for (int y = 520; y <= 543; y++)
//			blocks[x][y] = true;
//
//	for (int x = 941; x <= 971; x++)
//		for (int y = 567; y <= 588; y++)
//			blocks[x][y] = true;
//}

void Background::SetBloack()
{
	for (int x = 142; x <= 171; x++)
		for (int y = 0; y <= 494; y++)
			blocks[x][y] = true;

	for (int x = 142; x <= 215; x++)
		for (int y = 473; y <= 515; y++)
			blocks[x][y] = true;

	for (int x = 185; x <= 215; x++)
		for (int y = 495; y <= 619; y++)
			blocks[x][y] = true;

	for (int x = 389; x <= 418; x++)
		for (int y = 0; y <= 87; y++)
			blocks[x][y] = true;

	for (int x = 218; x <= 409; x++)
		for (int y = 43; y <= 87; y++)
			blocks[x][y] = true;

	for (int x = 218; x <= 247; x++)
		for (int y = 67; y <= 330; y++)
			blocks[x][y] = true;

	for (int x = 227; x <= 333; x++)
		for (int y = 300; y <= 330; y++)
			blocks[x][y] = true;

	for (int x = 323; x <= 333; x++)
		for (int y = 320; y <= 416; y++)
			blocks[x][y] = true;

	for (int x = 313; x <= 805; x++)
		for (int y = 386; y <= 416; y++)
			blocks[x][y] = true;

	for (int x = 776; x <= 805; x++)
		for (int y = 396; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 260; x <= 796; x++)
		for (int y = 472; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 260; x <= 290; x++)
		for (int y = 472; y <= 619; y++)
			blocks[x][y] = true;

	for (int x = 528; x <= 558; x++)
		for (int y = 0; y <= 105; y++)
			blocks[x][y] = true;

	for (int x = 604; x <= 633; x++)
		for (int y = 0; y <= 105; y++)
			blocks[x][y] = true;

	for (int x = 829; x <= 859; x++)
		for (int y = 86; y <= 319; y++)
			blocks[x][y] = true;

	for (int x = 839; x <= 945; x++)
		for (int y = 86; y <= 115; y++)
			blocks[x][y] = true;

	for (int x = 915; x <= 945; x++)
		for (int y = 0; y <= 106; y++)
			blocks[x][y] = true;

	for (int x = 906; x <= 934; x++)
		for (int y = 171; y <= 319; y++)
			blocks[x][y] = true;

	for (int x = 915; x <= 945; x++)
		for (int y = 171; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 925; x <= 1009; x++)
		for (int y = 472; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 990; x <= 1019; x++)
		for (int y = 0; y <= 30; y++)
			blocks[x][y] = true;

	for (int x = 990; x <= 1019; x++)
		for (int y = 86; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1106; x++)
		for (int y = 0; y <= 30; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1029; x++)
		for (int y = 86; y <= 233; y++)
			blocks[x][y] = true;

	for (int x = 1076; x <= 1106; x++)
		for (int y = 10; y <= 233; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1192; x++)
		for (int y = 257; y <= 302; y++)
			blocks[x][y] = true;

	for (int x = 1162; x <= 1192; x++)
		for (int y = 0; y <= 277; y++)
			blocks[x][y] = true;

	for (int x = 56; x <= 162; x++)
		for (int y = 429; y <= 458; y++)
			blocks[x][y] = true;

	for (int x = 56; x <= 86; x++)
		for (int y = 439; y <= 667; y++)
			blocks[x][y] = true;

	for (int x = 66; x <= 1106; x++)
		for (int y = 643; y <= 667; y++)
			blocks[x][y] = true;

	for (int x = 1000; x <= 1106; x++)
		for (int y = 429; y <= 459; y++)
			blocks[x][y] = true;

	for (int x = 1076; x <= 1106; x++)
		for (int y = 440; y <= 663; y++)
			blocks[x][y] = true;

	for (int x = 228; x <= 418; x++)
		for (int y = 68; y <= 147; y++)
			blocks[x][y] = true;

	for (int x = 399; x <= 548; x++)
		for (int y = 0; y <= 61; y++)
			blocks[x][y] = true;

	for (int x = 614; x <= 759; x++)
		for (int y = 0; y <= 61; y++)
			blocks[x][y] = true;

	for (int x = 832; x <= 934; x++)
		for (int y = 0; y <= 61; y++)
			blocks[x][y] = true;

	for (int x = 143; x <= 205; x++)
		for (int y = 496; y <= 576; y++)
			blocks[x][y] = true;

	for (int x = 271; x <= 805; x++)
		for (int y = 496; y <= 576; y++)
			blocks[x][y] = true;

	for (int x = 915; x <= 1020; x++)
		for (int y = 496; y <= 576; y++)
			blocks[x][y] = true;

	for (int x = 67; x <= 128; x++)
		for (int y = 439; y <= 487; y++)
			blocks[x][y] = true;

	for (int x = 111; x <= 162; x++)
		for (int y = 445; y <= 516; y++)
			blocks[x][y] = true;

	for (int x = 74; x <= 122; x++)
		for (int y = 617; y <= 657; y++)
			blocks[x][y] = true;

	for (int x = 154; x <= 201; x++)
		for (int y = 557; y <= 585; y++)
			blocks[x][y] = true;

	for (int x = 158; x <= 196; x++)
		for (int y = 566; y <= 591; y++)
			blocks[x][y] = true;

	for (int x = 290; x <= 336; x++)
		for (int y = 128; y <= 157; y++)
			blocks[x][y] = true;

	for (int x = 294; x <= 330; x++)
		for (int y = 138; y <= 162; y++)
			blocks[x][y] = true;

	for (int x = 276; x <= 329; x++)
		for (int y = 231; y <= 273; y++)
			blocks[x][y] = true;

	for (int x = 360; x <= 413; x++)
		for (int y = 179; y <= 221; y++)
			blocks[x][y] = true;

	for (int x = 361; x <= 413; x++)
		for (int y = 307; y <= 349; y++)
			blocks[x][y] = true;

	for (int x = 491; x <= 545; x++)
		for (int y = 34; y <= 88; y++)
			blocks[x][y] = true;

	for (int x = 681; x <= 734; x++)
		for (int y = 34; y <= 85; y++)
			blocks[x][y] = true;

	for (int x = 841; x <= 903; x++)
		for (int y = 34; y <= 92; y++)
			blocks[x][y] = true;

	for (int x = 606; x <= 667; x++)
		for (int y = 373; y <= 406; y++)
			blocks[x][y] = true;

	for (int x = 593; x <= 655; x++)
		for (int y = 219; y <= 264; y++)
			blocks[x][y] = true;

	for (int x = 799; x <= 849; x++)
		for (int y = 137; y <= 222; y++)
			blocks[x][y] = true;

	for (int x = 548; x <= 608; x++)
		for (int y = 417; y <= 471; y++)
			blocks[x][y] = true;

	for (int x = 710; x <= 771; x++)
		for (int y = 417; y <= 471; y++)
			blocks[x][y] = true;

	for (int x = 937; x <= 998; x++)
		for (int y = 237; y <= 291; y++)
			blocks[x][y] = true;

	for (int x = 937; x <= 998; x++)
		for (int y = 417; y <= 471; y++)
			blocks[x][y] = true;

	for (int x = 1016; x <= 1077; x++)
		for (int y = 463; y <= 543; y++)
			blocks[x][y] = true;

	for (int x = 1040; x <= 1088; x++)
		for (int y = 618; y <= 657; y++)
			blocks[x][y] = true;

	for (int x = 1129; x <= 1176; x++)
		for (int y = 233; y <= 272; y++)
			blocks[x][y] = true;

	for (int x = 1086; x <= 1137; x++)
		for (int y = 85; y <= 170; y++)
			blocks[x][y] = true;

	for (int x = 889; x <= 932; x++)
		for (int y = 510; y <= 553; y++)
			blocks[x][y] = true;

	for (int x = 931; x <= 981; x++)
		for (int y = 557; y <= 598; y++)
			blocks[x][y] = true;
}

void Background::SetAStarGrid()
{
	int index = 0;
	int cols = Engine::Get().ScreenSize().y;
	for (int y = 0; y < cols; y += gridInterval)
	{
		aStarGrid.emplace_back(vector<bool>());
		int rows = Engine::Get().ScreenSize().x;
		for (int x = 0; x < rows; x += gridInterval)
			aStarGrid[index].emplace_back(blocks[x][y]);
		index++;
	}
}

bool Background::CheckMovePoint(Vector2 position)
{
	return !blocks[(int)position.x][(int)position.y];
}

Background& Background::Get()
{
	return *instance;
}

Vector2 Background::GetAStarPosition(Vector2 position)
{
	return Vector2(position.x == 0.0f ? 0.0f : position.x / gridInterval,
		position.y == 0.0f ? 0.0f : position.y / gridInterval);
}
