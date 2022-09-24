#pragma once
#include "BulletMovementComponent.h"

class GameEngineTextureRenderer;

class SuperBoomerangBulletMovementComponent : public BulletMovementComponent
{
public:
	// constrcuter destructer
	SuperBoomerangBulletMovementComponent();
	~SuperBoomerangBulletMovementComponent();

	// delete Function
	SuperBoomerangBulletMovementComponent(const SuperBoomerangBulletMovementComponent& _Other) = delete;
	SuperBoomerangBulletMovementComponent(SuperBoomerangBulletMovementComponent&& _Other) noexcept = delete;
	SuperBoomerangBulletMovementComponent& operator=(const SuperBoomerangBulletMovementComponent& _Other) = delete;
	SuperBoomerangBulletMovementComponent& operator=(SuperBoomerangBulletMovementComponent&& _Other) noexcept = delete;

	float4 GetDirection() const { return Direction; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

	float4 GetSpeed() const { return Speed; }
	void SetSpeed(float4 _Speed) { Speed = _Speed; }

private:

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

public:
	void FixedUpdate(float _DeltaTime);

	// Y 방향만
	void AddForce(float4 _Power);

	float4 GetGravity() { return Gravity; }
	void SetGravity(float4 _Gravity) { Gravity = _Gravity; }

	float GetMass() { return Mass; }
	void SetMass(float _Mass) { Mass = _Mass; }

	float4 GetAcceleration() { return Acceleration; }
	void SetAcceleration(float4 _Acceleration) { Acceleration = _Acceleration; }

	float4 GetSpeed() { return Speed; }

	void Reset() { Power = 0.0f; Acceleration = 0.0f; Speed = 0.0f; }

private:
	float4 Power;
	float4 Gravity; // 중력
	float Mass;	   // 질량
	float4 Speed;
	float4 Acceleration; // 가속도
	double FixedUpdateInterval;
	double ElapsedTime;
	float4 Direction;
};

