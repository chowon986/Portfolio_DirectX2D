#pragma once
#include "BulletBase.h"

class DogCopterShooter;
class GameEngineTextureRenderer;
class MonsterPhysicsComponent;
class DogBowlBulletMovementComponent;
class DogBowlBullet : public BulletBase
{
public:
	DogBowlBullet();
	~DogBowlBullet();
	DogBowlBullet(const DogBowlBullet& _Other) = delete;
	DogBowlBullet(DogBowlBullet&& _Other) noexcept = delete;
	DogBowlBullet& operator=(const DogBowlBullet& _Other) = delete;
	DogBowlBullet& operator=(DogBowlBullet&& _Other) noexcept = delete;

public:
	std::map<int, float4> DirectionMap;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	virtual void SetDirection(float4 _Direction);
	void SetMonsterPhysicsComponent(MonsterPhysicsComponent* _Physics);
	MonsterPhysicsComponent* GetMonsterPhysicsComponent() { return Physics; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;
	bool CanCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
private:
	DogCopterShooter* Weapon;
	GameEngineTextureRenderer* Renderer;
	MonsterPhysicsComponent* Physics;
	DogBowlBulletMovementComponent* DogBowlMovementComponent;
	float RotateAngle;
	bool IsOnGround;
	GameEngineCollision* TrackCollision;
	float4 Direction;
};

