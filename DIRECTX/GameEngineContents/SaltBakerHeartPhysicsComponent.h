#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
class IInGameCharacterBase;
class SaltBakerHeartPhysicsComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	SaltBakerHeartPhysicsComponent();
	~SaltBakerHeartPhysicsComponent();

	// delete Function
	SaltBakerHeartPhysicsComponent(const SaltBakerHeartPhysicsComponent& _Other) = delete;
	SaltBakerHeartPhysicsComponent(SaltBakerHeartPhysicsComponent&& _Other) noexcept = delete;
	SaltBakerHeartPhysicsComponent& operator=(const SaltBakerHeartPhysicsComponent& _Other) = delete;
	SaltBakerHeartPhysicsComponent& operator=(SaltBakerHeartPhysicsComponent&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

public:
	// Y 방향만
	void AddForce(float _Power);

	float GetGravity() { return Gravity; }
	void SetGravity(float _Gravity) { Gravity = _Gravity; }

	float GetMass() { return Mass; }
	void SetMass(float _Mass) { Mass = _Mass; }

	float GetAcceleration() { return Acceleration; }
	void SetAcceleration(float _Acceleration) { Acceleration = _Acceleration; }

	float GetSpeed() { return Speed; }

	void Reset() { Power = 0.0f, Acceleration = 0.0f, Speed = 0.0f; }

	bool GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	void FixedUpdate(double _FixedUpdateInterval);

	bool IsOnBottomGround;
	bool IsOnCeilingGround;
private:
	float Power;
	float Gravity; // 중력
	float Mass;	   // 질량
	float Speed;   // 속도
	float Acceleration; // 가속도
	double FixedUpdateInterval;
	double ElapsedTime;
};

