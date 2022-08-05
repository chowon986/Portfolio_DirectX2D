#pragma once
#include "BulletBase.h"

class ChargerShooter;
class GameEngineTextureRenderer;
class ChargerBullet : public BulletBase
{
public:
	ChargerBullet();
	~ChargerBullet();
	ChargerBullet(const ChargerBullet& _Other) = delete;
	ChargerBullet(ChargerBullet&& _Other) noexcept = delete;
	ChargerBullet& operator=(const ChargerBullet& _Other) = delete;
	ChargerBullet& operator=(ChargerBullet&& _Other) noexcept = delete;

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	ChargerShooter* Weapon;
	void ChargershotLoop(const FrameAnimation_DESC& _DESC);
};

