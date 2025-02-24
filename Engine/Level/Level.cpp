#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	actors.push_back(newActor);
	//addRequestedActor = newActor;
}

void Level::RemoveActor(Actor* newActor)
{
	for (auto it = actors.begin(); it != actors.end(); )
	{
		if (*it == newActor)
			it = actors.erase(it);
		else ++it;
	}
}

void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}

		++ix;
	}

	// �߰� ��û�� ���� ó��.
	if (addRequestedActor)
	{
		actors.push_back(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->Update(deltaTime);
	}

	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��.
	//for (Actor* actor : actors)
	//{
	//	// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
	//	if (!actor->isActive || actor->isExpired)
	//	{
	//		continue;
	//	}

	//	actor->Update(deltaTime);
	//}
}

void Level::Draw()
{
	//ClearConsole();

	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->BackgroundDraw();
	}

	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Draw();
	}
}

void Level::LateUpdate(float deltaTime)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->LateUpdate(deltaTime);
	}
}

void Level::ClearConsole()
{
	// �ܼ� ȭ�� ũ�� ���� ��������
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwSize, dwWritten;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwSize = csbi.dwSize.X * csbi.dwSize.Y;
	
	// �ܼ� ȭ���� �������� ä���
	FillConsoleOutputCharacter(hConsole, ' ', dwSize, { 0, 0 }, &dwWritten);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwSize, { 0, 0 }, &dwWritten);

	// Ŀ���� ȭ�� �� ���� �̵�
	SetConsoleCursorPosition(hConsole, { 0, 0 });

	std::cout << dwSize;
}