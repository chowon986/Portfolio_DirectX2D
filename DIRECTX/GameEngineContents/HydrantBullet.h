#pragma once
#include "BulletBase.h"

class DogCopterPhase1;
class GameEngineCollision;
class GameEngineTextureRenderer;
class HydrantBullet : public BulletBase
{
public:
	HydrantBullet();
	~HydrantBullet();
	HydrantBullet(const HydrantBullet& _Other) = delete;
	HydrantBullet(HydrantBullet&& _Other) noexcept = delete;
	HydrantBullet& operator=(const HydrantBullet& _Other) = delete;
	HydrantBullet& operator=(HydrantBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineCollision* Collision;
	DogCopterPhase1* Parent;
	float4 MovePosition;
};

