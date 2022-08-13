#pragma once
#include "BulletBase.h"

class BulldogShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class BowWowBullet : public BulletBase
{
public:
	BowWowBullet();
	~BowWowBullet();
	BowWowBullet(const BowWowBullet& _Other) = delete;
	BowWowBullet(BowWowBullet&& _Other) noexcept = delete;
	BowWowBullet& operator=(const BowWowBullet& _Other) = delete;
	BowWowBullet& operator=(BowWowBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	BulldogShooter* Weapon;
	GameEngineCollision* Collision;
};

