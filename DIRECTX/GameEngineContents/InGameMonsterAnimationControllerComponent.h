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


	void OnStateChanged(InGameMonsterState _State);
	void OnAttackStateChanged(InGameMonsterAttackState _AttackState);

	void SetMonsterName(std::string _MonsterName);
	std::string GetMonsterName() { return Name; }

private:
	void UpdateAnimation();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string Name;
};

