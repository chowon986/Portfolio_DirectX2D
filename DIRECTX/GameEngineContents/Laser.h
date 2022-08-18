#pragma once
#include "BulletBase.h"

class BulldogShooter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class Laser : public BulletBase
{
public:
	Laser();
	~Laser();
	Laser(const Laser& _Other) = delete;
	Laser(Laser&& _Other) noexcept = delete;
	Laser& operator=(const Laser& _Other) = delete;
	Laser& operator=(Laser&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

	void OnLaserWarningAAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserWarningBAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserWarningCAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserBeamAnimationFinished(const FrameAnimation_DESC& _Info);

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	BulldogShooter* Weapon;
	GameEngineCollision* Collision;
};

