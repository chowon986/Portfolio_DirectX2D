#pragma once
#include "BulletBase.h"

class SuperSpreadShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class SuperSpreadBullet : public BulletBase
{
public:
	SuperSpreadBullet();
	~SuperSpreadBullet();
	SuperSpreadBullet(const SuperSpreadBullet& _Other) = delete;
	SuperSpreadBullet(SuperSpreadBullet&& _Other) noexcept = delete;
	SuperSpreadBullet& operator=(const SuperSpreadBullet& _Other) = delete;
	SuperSpreadBullet& operator=(SuperSpreadBullet&& _Other) noexcept = delete;

protected:
	void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

	//void OnSuperSpreadshotDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	//void Test(const FrameAnimation_DESC& _Info);

private:
	void SuperSpreadshotLoop(const FrameAnimation_DESC& _DESC);
};

