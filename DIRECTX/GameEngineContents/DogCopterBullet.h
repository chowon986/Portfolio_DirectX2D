#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class GameEngineTextureRenderer;
class DogCopterBullet : public BulletBase
{
public:
	DogCopterBullet();
	~DogCopterBullet();
	DogCopterBullet(const DogCopterBullet& _Other) = delete;
	DogCopterBullet(DogCopterBullet&& _Other) noexcept = delete;
	DogCopterBullet& operator=(const DogCopterBullet& _Other) = delete;
	DogCopterBullet& operator=(DogCopterBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineCollision* Collision;
};

