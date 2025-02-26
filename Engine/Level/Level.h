#pragma once
#include "Core.h"
#include "RTTI.h"
#include <vector>
#include <map>

// 전방 선언(Forward Declaration).
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI 정의.
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// 액터 추가 함수.
	void AddActor(Actor* newActor, int depth = 0);

	// 삭제 요청이 된 액터를 정리하는 함수.
	void ProcessAddedAndDestroyedActor();

	// 그리는 순서 변경.
	void ChangeDepth(Actor* actor, int prevDepth, int newDepth);

	// 루프 처리 함수.
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LateUpdate(float deltaTime);

protected:
	// 게임 공간에 배치되는 물체(액터) 배열.
	multimap<int, Actor*> actors;

	// 추가 요청된 액터.
	multimap<int, Actor*> addRequestedActors;
};