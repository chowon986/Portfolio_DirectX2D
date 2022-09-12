#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
class IInGameCharacterBase;
class ChickenPhysicsComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	ChickenPhysicsComponent();
	~ChickenPhysicsComponent();

	// delete Function
	ChickenPhysicsComponent(const ChickenPhysicsComponent& _Other) = delete;
	ChickenPhysicsComponent(ChickenPhysicsComponent&& _Other) noexcept = delete;
	ChickenPhysicsComponent& operator=(const ChickenPhysicsComponent& _Other) = delete;
	ChickenPhysicsComponent& operator=(ChickenPhysicsComponent&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

public:
	// Y ���⸸
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

	bool IsOnGround;
private:
	float Power;
	float Gravity; // �߷�
	float Mass;	   // ����
	float Speed;   // �ӵ�
	float Acceleration; // ���ӵ�
	double FixedUpdateInterval;
	double ElapsedTime;
};

