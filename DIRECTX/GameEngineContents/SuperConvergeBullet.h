#pragma once
#include "BulletBase.h"

class SuperConvergeShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class SuperConvergeBullet : public BulletBase
{
public:
	SuperConvergeBullet();
	~SuperConvergeBullet();
	SuperConvergeBullet(const SuperConvergeBullet& _Other) = delete;
	SuperConvergeBullet(SuperConvergeBullet&& _Other) noexcept = delete;
	SuperConvergeBullet& operator=(const SuperConvergeBullet& _Other) = delete;
	SuperConvergeBullet& operator=(SuperConvergeBullet&& _Other) noexcept = delete;

protected:
	void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

	//void OnSuperConvergeshotDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	//void Test(const FrameAnimation_DESC& _Info);

private:
	void SuperConvergeshotLoop(const FrameAnimation_DESC& _DESC);
};

