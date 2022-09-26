#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class GameEngineTextureRenderer;
class StrawberryBullet : public BulletBase
{
public:
	StrawberryBullet();
	~StrawberryBullet();
	StrawberryBullet(const StrawberryBullet& _Other) = delete;
	StrawberryBullet(StrawberryBullet&& _Other) noexcept = delete;
	StrawberryBullet& operator=(const StrawberryBullet& _Other) = delete;
	StrawberryBullet& operator=(StrawberryBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	void OnBerryDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);

private:
	GameEngineCollision* Collision;
};

