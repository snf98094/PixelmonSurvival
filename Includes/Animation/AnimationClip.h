#pragma once
#include "Core.h"
#include "Actor/Actor.h"
#include "Image/ImageText.h"
#include <vector>

class ENGINE_API AnimationClip : public Actor
{
	// RTTI ����.
	RTTI_DECLARATIONS(AnimationClip, Actor)

	class Image
	{
	public:
		Image(ImageText* image, float position)
			: image(image), position(position) { }
		~Image()
		{
			if (image)
			{
				delete image;
				image = nullptr;
			}
		}

		float position;
		ImageText* image = nullptr;
	};

public:
	AnimationClip(const char* name, float time, bool isPlayer = false);
	~AnimationClip();

	virtual void Update(float delatTime) override;
	virtual void Draw() override;
	virtual void MonsterDraw() override;
	virtual void PlayerDraw() override;

	// ���/���� �Լ�
	void Play();
	void Stop();

	// �÷����� �̹��� �߰�.
	// float position = 0.0~1.0 ����� ��ġ ����.
	void AddImage(ImageText* imageText, float clipPosition);
	// �̹��� ��� ��ġ.
	void SetPosition(Vector2 playPosition);
	// �̹��� ���� ����.
	void SetFlip(bool value);

	// Ŭ�� �̸� Getter.
	const char* GetName() { return name; }
	// ���� Setter.
	void SetLoop(bool isLoop) { this->isLoop = isLoop; }
	
	// ���� Image�� ImageText ����.
	ImageText* GetImage() { return imageList[currentIndex]->image; }
	vector<Image*> GetImages() { return imageList; }
	
private:
	// Ŭ�� �̸�.
	const char* name;
	// �÷��� �ð�.
	float time = 0.0f;
	// �÷��� üũ �ð�.
	float checkTime = 0.0f;
	// ��� �ð�.
	float elapsedTime = 0.0f;
	// ����� �̹��� ����Ʈ.
	vector<Image*> imageList;
	// ��� ����.
	bool isPlaying = false;
	// ���� ����.
	bool isLoop = false;
	// �÷��̾�� Ŭ�� ����.
	bool isPlayer = false;
	// ���� �̹��� �ε���.
	int currentIndex = 0;
	// ����� ��ġ.
	Vector2 playPosition;
};