#pragma once
#include "Delegates.h"
#include "GameEngineCore/GameEngineActor.h"

class GameEngineTextureRenderer;
class BulletMovementComponent;
class GameEngineTexture;
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
	virtual float4 GetDirection() { return Direction; }
	virtual void SetDirection(float4 _Direction);

	BulletMovementComponent* GetMovementComponent() { return MovementComponent; }

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage)
	{
		ColMapImage = _ColMapImage;
	}

	GameEngineTextureRenderer* GetColMapImage()
	{
		return ColMapImage;
	}

	void SetCollision(GameEngineCollision* _Collision)
	{
		Collision = _Collision;
	}

	GameEngineCollision* GetCollision()
	{
		return Collision;
	}

	void SetIsOnGround(bool _IsOnGround);
	MulticastDelegate<bool>& GetIsOnGroundChangedDelegate() { return IsOnGroundChangedDelegate; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	CollisionReturn AttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual void OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other) {}

protected:
	float4 Direction;
	GameEngineTextureRenderer* Renderer;
	BulletMovementComponent* MovementComponent;
	GameEngineTextureRenderer* ColMapImage;
	GameEngineCollision* Collision;
	MulticastDelegate<bool> IsOnGroundChangedDelegate;
	bool IsOnGround;
	GameEngineTexture* ColMapTexture;
	float GaugeElapsedTime;
};
