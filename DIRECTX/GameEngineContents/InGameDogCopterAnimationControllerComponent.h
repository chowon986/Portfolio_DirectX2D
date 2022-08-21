#pragma once
#include "InGameMonsterAnimationControllerComponent.h"

enum class InGameDogCopterState;
enum class InGameMonsterAttackState;
class InGameDogCopterAnimationControllerComponent : public InGameMonsterAnimationControllerComponent
{
public:
	// constrcuter destructer
	InGameDogCopterAnimationControllerComponent();
	~InGameDogCopterAnimationControllerComponent();

	// delete Function
	InGameDogCopterAnimationControllerComponent(const InGameDogCopterAnimationControllerComponent& _Other) = delete;
	InGameDogCopterAnimationControllerComponent(InGameDogCopterAnimationControllerComponent&& _Other) noexcept = delete;
	InGameDogCopterAnimationControllerComponent& operator=(const InGameDogCopterAnimationControllerComponent& _Other) = delete;
	InGameDogCopterAnimationControllerComponent& operator=(InGameDogCopterAnimationControllerComponent&& _Other) noexcept = delete;

	virtual void OnStateChanged(InGameDogCopterState _State);
	virtual void OnAttackStateChanged(InGameMonsterAttackState _AttackState);

	virtual void SetMonsterName(std::string _MonsterName);
	virtual std::string GetMonsterName() { return Name; }

private:
	void UpdateAnimation() override;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string Name;
};

