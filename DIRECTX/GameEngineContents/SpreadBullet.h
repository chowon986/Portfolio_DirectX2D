#pragma once
#include "BulletBase.h"

class SpreadShooter;
class GameEngineTextureRenderer;
class SpreadBullet : public BulletBase
{
public:
	SpreadBullet();
	~SpreadBullet();
	SpreadBullet(const SpreadBullet& _Other) = delete;
	SpreadBullet(SpreadBullet&& _Other) noexcept = delete;
	SpreadBullet& operator=(const SpreadBullet& _Other) = delete;
	SpreadBullet& operator=(SpreadBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	SpreadShooter* Weapon;
};

