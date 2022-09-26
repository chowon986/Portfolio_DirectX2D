#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class GameEngineTextureRenderer;
class SugarBullet : public BulletBase
{
public:
	SugarBullet();
	~SugarBullet();
	SugarBullet(const SugarBullet& _Other) = delete;
	SugarBullet(SugarBullet&& _Other) noexcept = delete;
	SugarBullet& operator=(const SugarBullet& _Other) = delete;
	SugarBullet& operator=(SugarBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;
	CollisionReturn OnParryCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	float DirectionElapsedTime;
};

