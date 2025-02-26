#pragma once
#include "Core.h"
#include "RTTI.h"
#include <vector>
#include <map>

// ���� ����(Forward Declaration).
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�.
	void AddActor(Actor* newActor, int depth = 0);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�.
	void ProcessAddedAndDestroyedActor();

	// �׸��� ���� ����.
	void ChangeDepth(Actor* actor, int prevDepth, int newDepth);

	// ���� ó�� �Լ�.
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LateUpdate(float deltaTime);

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭.
	multimap<int, Actor*> actors;

	// �߰� ��û�� ����.
	multimap<int, Actor*> addRequestedActors;
};