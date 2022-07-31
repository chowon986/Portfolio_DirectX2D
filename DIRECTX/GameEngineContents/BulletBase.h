#pragma once
#include "GameEngineCore/GameEngineActor.h"

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

protected:
	std::string GetVerticalDirection() { return VerticalDirection; }
	std::string GetHorizontalDirection() { return HorizontalDirection; }

protected:
	std::string VerticalDirection;
	std::string HorizontalDirection;

	GameEngineTextureRenderer* Renderer;
	BulletMovementComponent* MovementComponent;
};
