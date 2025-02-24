#include "PreCompiledHeader.h"
#include "AnimationClip.h"

AnimationClip::AnimationClip(const char* name, float time)
	: name(name), time(time)
{
}

AnimationClip::~AnimationClip()
{
	if (imageList.size() > 0)
		for (int i = 0; i < imageList.size(); i++)
		{
			delete imageList[i];
			imageList[i] = nullptr;
		}
}

void AnimationClip::Update(float delatTime)
{
	if (isPlaying && imageList.size() > 1)
	{
		if (!isLoop && currentIndex == imageList.size() - 1)
			return;

		// ��� �ð� ����.
		elapsedTime += delatTime;

		// ���� �̹����� �׸� �ð��� �Ǹ� �ε��� ����
		checkTime = (currentIndex + 1) < imageList.size() ? imageList[(currentIndex + 1)]->position * time : time;
		if (elapsedTime > checkTime)
			currentIndex = (currentIndex + 1) % imageList.size();;

		// �÷��� �ð��� ������ �ʱ�ȭ
		if (elapsedTime > time)
			elapsedTime = 0.0f;
	}
}

void AnimationClip::Draw()
{
	if (isPlaying)
		imageList[currentIndex]->image->Print();
}

void AnimationClip::Play()
{
	isPlaying = true;

	// �ִϸ��̼��� ó������ ���۵ǵ��� �ε��� �ʱ�ȭ
	currentIndex = 0;
}

void AnimationClip::Stop()
{
	isPlaying = false;
}

void AnimationClip::AddImage(ImageText* imageText, float clipPosition)
{
	imageList.push_back(new Image(imageText, clipPosition));
	SetPlayPosition(playPosition);
}

void AnimationClip::SetPlayPosition(Vector2 playPosition)
{
	this->playPosition = playPosition;
	for (auto* image : imageList)
		image->image->SetDrawingPosition(playPosition);
}