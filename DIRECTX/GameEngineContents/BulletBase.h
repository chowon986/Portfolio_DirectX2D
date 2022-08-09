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

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage)
	{
		ColMapImage = _ColMapImage;
	}

	GameEngineTextureRenderer* GetColMapImage()
	{
		return ColMapImage;
	}

	void Death();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float4 Direction;
	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	GameEngineTextureRenderer* Renderer;
	BulletMovementComponent* MovementComponent;
	GameEngineTextureRenderer* ColMapImage;
	GameEngineCollision* Collision;
};
