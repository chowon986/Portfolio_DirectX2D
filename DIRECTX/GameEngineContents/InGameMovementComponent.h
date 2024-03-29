#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineContents/IInGameMonsterBase.h>

enum class InGameMonsterState;
class InGameMovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	InGameMovementComponent();
	~InGameMovementComponent();

	// delete Function
	InGameMovementComponent(const InGameMovementComponent& _Other) = delete;
	InGameMovementComponent(InGameMovementComponent&& _Other) noexcept = delete;
	InGameMovementComponent& operator=(const InGameMovementComponent& _Other) = delete;
	InGameMovementComponent& operator=(InGameMovementComponent&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	float Speed;
	float4 Direction;
	float4 StartPos;
	float4 EndPos;
	float4 ImageDir;
	InGameMonsterState State;
};

