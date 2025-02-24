#pragma once
#include "Core.h"
#include "AnimationClip.h"
#include <map>

using Map = std::map<const char*, AnimationClip*>::value_type;

class ENGINE_API Animator
{
public:
	// �ִϸ��̼� Ŭ�� �߰�.
	void AddClip(AnimationClip* clip);
	// �ִϸ��̼� ���.
	void Play(const char* name);
	// �ִϸ��̼� Ŭ�� ��������.
	AnimationClip* GetClip(const char* name);
	// ���� ��� ���� �ִϸ��̼� Ŭ�� ��������.
	AnimationClip* GetCurrentClip();

	// �̹��� ��� ��ġ.
	void SetPosition(Vector2 playPosition);
	// �̹��� ���� ����.
	void SetFlip(bool value);

private:
	map<const char*, AnimationClip*> clips;
	AnimationClip* currentClip = nullptr;
};