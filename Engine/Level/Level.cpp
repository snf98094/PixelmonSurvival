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
		delete actor;
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.emplace_back(newActor);
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
	int size = actors.size();
	for (int i = 0; i < size; i++)
	{
		if (actors[i]->isExpired)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.erase(actors.begin() + i);
			continue;
		}

		++i;
	}

	// �߰� ��û�� ���� ó��.
	//if (addRequestedActor)
	if (addRequestedActors.size() > 0)
	{
		for (Actor* actor : addRequestedActors)
		{
			actors.push_back(actor);
			//addRequestedActor = nullptr;
		}

		addRequestedActors.clear();
	}
}

void Level::Update(float deltaTime)
{
	int size = actors.size();
	for (int i = 0; i < size; i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->Update(deltaTime);
	}
}

void Level::Draw()
{
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

	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->MonsterDraw();
	}

	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->PlayerDraw();
	}

	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->ObjectDraw();
	}
}

void Level::LateUpdate(float deltaTime)
{
	int size = actors.size();
	for (int i = 0; i < size; i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->LateUpdate(deltaTime);
	}
}