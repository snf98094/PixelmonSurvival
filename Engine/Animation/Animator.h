#pragma once
#include "Core.h"
#include "AnimationClip.h"
#include <map>

using Map = std::map<const char*, AnimationClip*>::value_type;

class ENGINE_API Animator
{
public:
	// 애니메이션 클립 추가.
	void AddClip(AnimationClip* clip);
	// 애니메이션 재생.
	void Play(const char* name);
	// 애니메이션 클립 가져오기.
	AnimationClip* GetClip(const char* name);
	// 현재 재생 중인 애니메이션 클립 가져오기.
	AnimationClip* GetCurrentClip();

	// 이미지 재생 위치.
	void SetPosition(Vector2 playPosition);
	// 이미지 반전 여부.
	void SetFlip(bool value);

private:
	map<const char*, AnimationClip*> clips;
	AnimationClip* currentClip = nullptr;
};