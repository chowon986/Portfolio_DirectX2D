#pragma once
#include <GameEngineCore/GameEngineComponent.h>

class GameEngineTextureRenderer;
class BoomerangBulletMovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	BoomerangBulletMovementComponent();
	~BoomerangBulletMovementComponent();

	// delete Function
	BoomerangBulletMovementComponent(const BoomerangBulletMovementComponent& _Other) = delete;
	BoomerangBulletMovementComponent(BoomerangBulletMovementComponent&& _Other) noexcept = delete;
	BoomerangBulletMovementComponent& operator=(const BoomerangBulletMovementComponent& _Other) = delete;
	BoomerangBulletMovementComponent& operator=(BoomerangBulletMovementComponent&& _Other) noexcept = delete;

	float4 GetDirection() const { return Direction; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float _Speed) { Speed = _Speed; }

private:

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	float4 Direction;
	float Speed;
	float InitialY;
};

