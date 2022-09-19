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

	std::string GetColor() { return Color; }
	void SetColor(std::string _Color) { Color = _Color; }

	GameEngineCollision* GetTrackCollision() { return TrackCollision; }
	void SetTrackCollision(GameEngineCollision* _Collision) { TrackCollision = _Collision; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;
	CollisionReturn CanCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	DogCopterShooter* Weapon;
	GameEngineTextureRenderer* Renderer;
	MonsterPhysicsComponent* Physics;
	DogBowlBulletMovementComponent* DogBowlMovementComponent;
	float RotateAngle;
	bool IsOnGround;
	int Index;
	GameEngineCollision* TrackCollision;
	float4 Direction;
	std::string Color;
};

