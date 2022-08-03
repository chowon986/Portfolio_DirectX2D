#pragma once
#include "GameEngineCore/GameEngineActor.h"

class GameEngineTextureRenderer;
class BulletMovementComponent;
class BulletBase : public GameEngineActor
{
public:
	BulletBase();
	~BulletBase();
	BulletBase(const BulletBase& _Other) = delete;
	BulletBase(BulletBase&& _Other) noexcept = delete;
	BulletBase& operator=(const BulletBase& _Other) = delete;
	BulletBase& operator=(BulletBase&& _Other) noexcept = delete;

public:
	float4 GetDirection() { return Direction; }
	void SetDirection(float4 _Direction);

private:
	float4 Direction;

protected:
	GameEngineTextureRenderer* Renderer;
	BulletMovementComponent* MovementComponent;
};
