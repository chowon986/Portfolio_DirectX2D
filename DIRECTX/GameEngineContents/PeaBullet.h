#pragma once
#include "BulletBase.h"

class PeaShooter;
class GameEngineTextureRenderer;
class PeaBullet : public BulletBase
{
public:
	PeaBullet();
	~PeaBullet();
	PeaBullet(const PeaBullet& _Other) = delete;
	PeaBullet(PeaBullet&& _Other) noexcept = delete;
	PeaBullet& operator=(const PeaBullet& _Other) = delete;
	PeaBullet& operator=(PeaBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	PeaShooter* Weapon;
	void PeashotLoop(const FrameAnimation_DESC& _DESC);
};

