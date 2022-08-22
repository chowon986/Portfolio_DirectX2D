#pragma once
#include <GameEngineCore/GameEngineComponent.h>

class GameEngineTextureRenderer;
class DogBowlBulletMovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	DogBowlBulletMovementComponent();
	~DogBowlBulletMovementComponent();

	// delete Function
	DogBowlBulletMovementComponent(const DogBowlBulletMovementComponent& _Other) = delete;
	DogBowlBulletMovementComponent(DogBowlBulletMovementComponent&& _Other) noexcept = delete;
	DogBowlBulletMovementComponent& operator=(const DogBowlBulletMovementComponent& _Other) = delete;
	DogBowlBulletMovementComponent& operator=(DogBowlBulletMovementComponent&& _Other) noexcept = delete;

	float4 GetDirection() const { return Direction; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float _Speed) { Speed = _Speed; }

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	float4 Direction;
	float Speed;
};

