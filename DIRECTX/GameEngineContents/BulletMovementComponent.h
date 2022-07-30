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

	std::string GetHorizontalDirection() const { return HorizontalDirection; }
	void SetHorizontalDirection(std::string _HorizontalDirection) { HorizontalDirection = _HorizontalDirection; }

	std::string GetVerticalDirection() const { return VerticalDirection; }
	void SetVerticalDirection(std::string _VerticalDirection) { VerticalDirection = _VerticalDirection; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float _Speed) { Speed = _Speed; }

private:

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string VerticalDirection;
	std::string HorizontalDirection;
	float Speed;
};

