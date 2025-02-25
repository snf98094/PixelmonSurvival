#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
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
	// 액터 순회 후 삭제 요청된 액터를 처리.
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

	// 추가 요청된 액터 처리.
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
}

void Level::Draw()
{
	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->BackgroundDraw();
	}

	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출.
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기.
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
	for (int i = 0; i < actors.size(); i++)
	{
		if (!actors[i]->isActive || actors[i]->isExpired)
			continue;

		actors[i]->LateUpdate(deltaTime);
	}
}