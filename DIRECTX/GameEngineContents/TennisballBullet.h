#pragma once
#include "BulletBase.h"

class BulldogShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class TennisballBullet : public BulletBase
{
public:
	TennisballBullet();
	~TennisballBullet();
	TennisballBullet(const TennisballBullet& _Other) = delete;
	TennisballBullet(TennisballBullet&& _Other) noexcept = delete;
	TennisballBullet& operator=(const TennisballBullet& _Other) = delete;
	TennisballBullet& operator=(TennisballBullet&& _Other) noexcept = delete;

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

