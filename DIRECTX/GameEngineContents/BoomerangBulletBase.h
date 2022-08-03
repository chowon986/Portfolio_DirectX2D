#pragma once
#include "GameEngineCore/GameEngineActor.h"

class GameEngineTextureRenderer;
class BoomerangBulletMovementComponent;
class BoomerangBulletBase : public GameEngineActor
{
public:
	BoomerangBulletBase();
	~BoomerangBulletBase();
	BoomerangBulletBase(const BoomerangBulletBase& _Other) = delete;
	BoomerangBulletBase(BoomerangBulletBase&& _Other) noexcept = delete;
	BoomerangBulletBase& operator=(const BoomerangBulletBase& _Other) = delete;
	BoomerangBulletBase& operator=(BoomerangBulletBase&& _Other) noexcept = delete;

public:
	float4 GetDirection() { return Direction; }
	void SetDirection(float4 _Direction);

private:
	float4 Direction;

protected:
	GameEngineTextureRenderer* Renderer;
	BoomerangBulletMovementComponent* MovementComponent;
};
