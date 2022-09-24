#pragma once
#include "BulletBase.h"

class SuperBoomerangShooter;
class GameEngineTextureRenderer;
class SuperBoomerangBulletMovementComponent;
class SuperBoomerangBullet : public BulletBase
{
public:
	SuperBoomerangBullet();
	~SuperBoomerangBullet();
	SuperBoomerangBullet(const SuperBoomerangBullet& _Other) = delete;
	SuperBoomerangBullet(SuperBoomerangBullet&& _Other) noexcept = delete;
	SuperBoomerangBullet& operator=(const SuperBoomerangBullet& _Other) = delete;
	SuperBoomerangBullet& operator=(SuperBoomerangBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	SuperBoomerangShooter* Weapon;
	float ElapsedTime;
	void SuperBoomerangshotLoop(const FrameAnimation_DESC& _DESC);
	SuperBoomerangBulletMovementComponent* SuperMovementComponent;
};

