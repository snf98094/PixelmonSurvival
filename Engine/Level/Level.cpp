#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (auto& actor : actors)
		delete actor.second;
	actors.clear();
}

void Level::AddActor(Actor* newActor, int depth)
{
	addRequestedActors.insert({ depth, newActor });
}

void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ���� ��û ó��
	for (auto it = actors.begin(); it != actors.end();)
	{
		if (it->second->isExpired) // ���� ����̸�
		{
			delete it->second; // �޸� ����
			it = actors.erase(it); // multimap���� ���� (��ȯ���� ���� ���Ҹ� ����Ŵ)
		}
		else ++it;
	}

	// �߰� ��û�� ���� ó��
	if (!addRequestedActors.empty())
	{
		for (auto& pair : addRequestedActors)
			actors.insert(pair); // Z �ε����� �����ϸ� �߰�

		addRequestedActors.clear(); // �߰� ��û ��� ����
	}
}

void Level::ChangeDepth(Actor* actor, int prevDepth, int newDepth)
{
	// oldZ���� �ش� ��ü�� ã��
	auto range = actors.equal_range(prevDepth);
	for (auto it = range.first; it != range.second; ++it)
		if (it->second == actor) 
		{
			// ���� ��ü ����
			actors.erase(it);
			break;
		}
	
	// ���ο� Depth�� �ٽ� �߰�
	actors.insert({ newDepth, actor });
}

void Level::Update(float deltaTime)
{
	for (auto& pair : actors)
	{
		Actor* actor = pair.second;
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	for (auto& pair : actors)
	{
		Actor* actor = pair.second;
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->Draw();
	}
}

void Level::LateUpdate(float deltaTime)
{
	for (auto& pair : actors)
	{
		Actor* actor = pair.second;
		if (!actor->isActive || actor->isExpired)
			continue;

		actor->LateUpdate(deltaTime);
	}
}