#pragma once
#include "BulletBase.h"

class SuperPeaShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class SuperPeaBullet : public BulletBase
{
public:
	SuperPeaBullet();
	~SuperPeaBullet();
	SuperPeaBullet(const SuperPeaBullet& _Other) = delete;
	SuperPeaBullet(SuperPeaBullet&& _Other) noexcept = delete;
	SuperPeaBullet& operator=(const SuperPeaBullet& _Other) = delete;
	SuperPeaBullet& operator=(SuperPeaBullet&& _Other) noexcept = delete;

protected:
	void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

	//void OnSuperPeashotDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	//void Test(const FrameAnimation_DESC& _Info);

private:
	void SuperPeashotLoop(const FrameAnimation_DESC& _DESC);
};

