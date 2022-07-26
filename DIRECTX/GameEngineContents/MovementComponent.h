#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class WorldMapCharacterState;

class MovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	MovementComponent();
	~MovementComponent();

	// delete Function
	MovementComponent(const MovementComponent& _Other) = delete;
	MovementComponent(MovementComponent&& _Other) noexcept = delete;
	MovementComponent& operator=(const MovementComponent& _Other) = delete;
	MovementComponent& operator=(MovementComponent&& _Other) noexcept = delete;

	float4 GetDirection() const { return Direction; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

	void OnStateChanged(WorldMapCharacterState _State);
	void OnDirectionChanged(std::string _Dir);

private:
	void UpdateDirection();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);
	virtual void End();

private:
	float4 Direction;
	float Speed;
};

