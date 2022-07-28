#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IInGameCharacterBase.h"

enum class InGameCharacterState;
class InGameCharacterMovementCompmonent;
class InGameCharacterAnimationControllerComponent;
class InGameCuphead : public IInGameCharacterBase
{
public:
	// constrcuter destructer
	InGameCuphead();
	~InGameCuphead();

	// delete Function
	InGameCuphead(const InGameCuphead& _Other) = delete;
	InGameCuphead(InGameCuphead&& _Other) noexcept = delete;
	InGameCuphead& operator=(const InGameCuphead& _Other) = delete;
	InGameCuphead& operator=(InGameCuphead&& _Other) noexcept = delete;

public:


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Aim() override;
	void TakeDamage() override;
	void Dash() override;
	void Die() override;
	void Duck() override;
	void Jump() override;
	void Parry() override;
	void Prepare() override;
	void Run() override;
	void Shoot() override;
	void SpecialAttack() override;
	void SuperIAttack() override;
	void SuperIIAttack() override;
	void SuperIIIAttack() override;
	void Walk() override;
	void Idle() override;

private:
	InGameCharacterMovementCompmonent* Movement;
	InGameCharacterAnimationControllerComponent* Animation;
};
