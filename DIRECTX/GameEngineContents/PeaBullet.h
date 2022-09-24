#pragma once
#include "BulletBase.h"

class PeaShooter;
class GameEngineCollision;
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

protected:
	void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

	void OnPeashotDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void Test(const FrameAnimation_DESC& _Info);

private:
	void PeashotLoop(const FrameAnimation_DESC& _DESC);
};

