#pragma once
#include "BoomerangBulletBase.h"

class BoomerangShooter;
class GameEngineTextureRenderer;
class BoomerangBullet : public BoomerangBulletBase
{
public:
	BoomerangBullet();
	~BoomerangBullet();
	BoomerangBullet(const BoomerangBullet& _Other) = delete;
	BoomerangBullet(BoomerangBullet&& _Other) noexcept = delete;
	BoomerangBullet& operator=(const BoomerangBullet& _Other) = delete;
	BoomerangBullet& operator=(BoomerangBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	BoomerangShooter* Weapon;
	void BoomerangshotLoop(const FrameAnimation_DESC& _DESC);
};

