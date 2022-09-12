#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class BulletMovementComponent;
class GameEngineTextureRenderer;
class LimeBullet : public BulletBase
{
public:
	LimeBullet();
	~LimeBullet();
	LimeBullet(const LimeBullet& _Other) = delete;
	LimeBullet(LimeBullet&& _Other) noexcept = delete;
	LimeBullet& operator=(const LimeBullet& _Other) = delete;
	LimeBullet& operator=(LimeBullet&& _Other) noexcept = delete;

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

