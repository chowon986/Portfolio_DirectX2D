#pragma once
#include "BulletBase.h"

class BulldogShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class YarnballBullet : public BulletBase
{
public:
	YarnballBullet();
	~YarnballBullet();
	YarnballBullet(const YarnballBullet& _Other) = delete;
	YarnballBullet(YarnballBullet&& _Other) noexcept = delete;
	YarnballBullet& operator=(const YarnballBullet& _Other) = delete;
	YarnballBullet& operator=(YarnballBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	BulldogShooter* Weapon;
	GameEngineCollision* Collision;
};

