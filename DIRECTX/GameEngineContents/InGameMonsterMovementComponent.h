#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameMonsterState;
class IInGameMonsterBase;
class InGameMonsterMovementComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	InGameMonsterMovementComponent();
	~InGameMonsterMovementComponent();

	// delete Function
	InGameMonsterMovementComponent(const InGameMonsterMovementComponent& _Other) = delete;
	InGameMonsterMovementComponent(InGameMonsterMovementComponent&& _Other) noexcept = delete;
	InGameMonsterMovementComponent& operator=(const InGameMonsterMovementComponent& _Other) = delete;
	InGameMonsterMovementComponent& operator=(InGameMonsterMovementComponent&& _Other) noexcept = delete;

	void OnStateChanged(InGameMonsterState _State);
	void OnDirectionChanged(std::string _Dir);

private:
	void UpdateDirection();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	IInGameMonsterBase* InGameMonster;
	float Speed;
	float4 Direction;
};

