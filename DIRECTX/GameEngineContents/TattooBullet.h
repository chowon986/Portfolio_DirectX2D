#pragma once
#include "BulletBase.h"

class BulldogShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class TattooBullet : public BulletBase
{
public:
	TattooBullet();
	~TattooBullet();
	TattooBullet(const TattooBullet& _Other) = delete;
	TattooBullet(TattooBullet&& _Other) noexcept = delete;
	TattooBullet& operator=(const TattooBullet& _Other) = delete;
	TattooBullet& operator=(TattooBullet&& _Other) noexcept = delete;

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

