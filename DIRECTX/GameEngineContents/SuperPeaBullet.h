#pragma once
#include "BulletBase.h"

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
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) override;
	void OnPeashotExIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPeashotExDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
};

