#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class BulletMovementComponent;
class GameEngineTextureRenderer;
class PepperBullet : public BulletBase
{
public:
	PepperBullet();
	~PepperBullet();
	PepperBullet(const PepperBullet& _Other) = delete;
	PepperBullet(PepperBullet&& _Other) noexcept = delete;
	PepperBullet& operator=(const PepperBullet& _Other) = delete;
	PepperBullet& operator=(PepperBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

	std::string GetStartPosName() { return StartPosName; }
	void SetStartPosName(std::string _Pos) { StartPosName = _Pos; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineCollision* Collision;
	float DirectionElapsedTime;
	std::string StartPosName;
};

