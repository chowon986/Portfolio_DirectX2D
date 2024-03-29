#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
class IInGameCharacterBase;
class PhysicsComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysicsComponent();
	~PhysicsComponent();

	// delete Function
	PhysicsComponent(const PhysicsComponent& _Other) = delete;
	PhysicsComponent(PhysicsComponent&& _Other) noexcept = delete;
	PhysicsComponent& operator=(const PhysicsComponent& _Other) = delete;
	PhysicsComponent& operator=(PhysicsComponent&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

public:
	void FixedUpdate(float _DeltaTime);

	// Y 방향만
	void AddForce(float _Power);

	float GetGravity() { return Gravity; }
	void SetGravity(float _Gravity) { Gravity = _Gravity; }

	float GetMass() { return Mass; }
	void SetMass(float _Mass) { Mass = _Mass; }

	float GetAcceleration() { return Acceleration; }
	void SetAcceleration(float _Acceleration) { Acceleration = _Acceleration; }

	float GetSpeed() { return Speed; }

	void Reset() { Power = 0.0f; Acceleration = 0.0f; Speed = 0.0f; }

	CollisionReturn GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	
	bool OnGround;


private:
	float Power;
	float Gravity; // 중력
	float Mass;	   // 질량
	float Speed;   // 속도
	float Acceleration; // 가속도
	double FixedUpdateInterval;
	double ElapsedTime;
};

