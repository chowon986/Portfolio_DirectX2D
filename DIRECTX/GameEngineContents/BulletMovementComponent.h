#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class WorldMapCharacterState;
class GameEngineTextureRenderer;
class BulletMovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	BulletMovementComponent();
	~BulletMovementComponent();

	// delete Function
	BulletMovementComponent(const BulletMovementComponent& _Other) = delete;
	BulletMovementComponent(BulletMovementComponent&& _Other) noexcept = delete;
	BulletMovementComponent& operator=(const BulletMovementComponent& _Other) = delete;
	BulletMovementComponent& operator=(BulletMovementComponent&& _Other) noexcept = delete;

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
};

