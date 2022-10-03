#pragma once
#include "InGameMonsterAnimationControllerComponent.h"

enum class InGamePh2DogState;
enum class InGameMonsterAttackState;
class InGamePh2DogAnimationControllerComponent : public InGameMonsterAnimationControllerComponent
{
public:
	// constrcuter destructer
	InGamePh2DogAnimationControllerComponent();
	~InGamePh2DogAnimationControllerComponent();

	// delete Function
	InGamePh2DogAnimationControllerComponent(const InGamePh2DogAnimationControllerComponent& _Other) = delete;
	InGamePh2DogAnimationControllerComponent(InGamePh2DogAnimationControllerComponent&& _Other) noexcept = delete;
	InGamePh2DogAnimationControllerComponent& operator=(const InGamePh2DogAnimationControllerComponent& _Other) = delete;
	InGamePh2DogAnimationControllerComponent& operator=(InGamePh2DogAnimationControllerComponent&& _Other) noexcept = delete;
	
	virtual void OnPh2DogStateChanged(InGamePh2DogState _State);
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
	float Angle;
	bool IsCurAnimationAttack;
};

