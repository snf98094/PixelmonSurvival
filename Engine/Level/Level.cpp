#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
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
	// 액터 삭제 요청 처리
	for (auto it = actors.begin(); it != actors.end();)
	{
		if (it->second->isExpired) // 삭제 대상이면
		{
			delete it->second; // 메모리 해제
			it = actors.erase(it); // multimap에서 제거 (반환값이 다음 원소를 가리킴)
		}
		else ++it;
	}

	// 추가 요청된 액터 처리
	if (!addRequestedActors.empty())
	{
		for (auto& pair : addRequestedActors)
			actors.insert(pair); // Z 인덱스를 유지하며 추가

		addRequestedActors.clear(); // 추가 요청 목록 비우기
	}
}

void Level::ChangeDepth(Actor* actor, int prevDepth, int newDepth)
{
	// oldZ에서 해당 객체를 찾기
	auto range = actors.equal_range(prevDepth);
	for (auto it = range.first; it != range.second; ++it)
		if (it->second == actor) 
		{
			// 기존 객체 삭제
			actors.erase(it);
			break;
		}
	
	// 새로운 Depth로 다시 추가
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