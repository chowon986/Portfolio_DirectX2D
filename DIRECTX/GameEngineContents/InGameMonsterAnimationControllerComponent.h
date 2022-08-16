#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameMonsterAnimationControllerComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	InGameMonsterAnimationControllerComponent();
	~InGameMonsterAnimationControllerComponent();

	// delete Function
	InGameMonsterAnimationControllerComponent(const InGameMonsterAnimationControllerComponent& _Other) = delete;
	InGameMonsterAnimationControllerComponent(InGameMonsterAnimationControllerComponent&& _Other) noexcept = delete;
	InGameMonsterAnimationControllerComponent& operator=(const InGameMonsterAnimationControllerComponent& _Other) = delete;
	InGameMonsterAnimationControllerComponent& operator=(InGameMonsterAnimationControllerComponent&& _Other) noexcept = delete;


	virtual void OnStateChanged(InGameMonsterState _State);
	virtual void OnAttackStateChanged(InGameMonsterAttackState _AttackState);

	virtual void SetMonsterName(std::string _MonsterName);
	virtual std::string GetMonsterName() { return Name; }

	virtual void UpdateAnimation();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string Name;
};

