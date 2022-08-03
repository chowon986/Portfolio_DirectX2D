#pragma once
#include "BulletBase.h"

class ConvergeShooter;
class GameEngineTextureRenderer;
class ConvergeBullet : public BulletBase
{
public:
	ConvergeBullet();
	~ConvergeBullet();
	ConvergeBullet(const ConvergeBullet& _Other) = delete;
	ConvergeBullet(ConvergeBullet&& _Other) noexcept = delete;
	ConvergeBullet& operator=(const ConvergeBullet& _Other) = delete;
	ConvergeBullet& operator=(ConvergeBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	ConvergeShooter* Weapon;
};

