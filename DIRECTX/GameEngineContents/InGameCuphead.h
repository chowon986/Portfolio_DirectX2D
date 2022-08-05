#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IInGameCharacterBase.h"

enum class InGameCharacterState;
class GameEngineCollision;
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
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
	void SuperAttack() override;
	void Walk() override;
	void Idle() override;
	void OnPrepareAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnDashAnimationEnded(const FrameAnimation_DESC& _Info);
	void UpdateState();
	void UpdateDirection();

private:
	GameEngineTextureRenderer* Renderer;
	InGameCharacterMovementCompmonent* Movement;
	bool IsInputEnabled;
	bool IsOnGround;
	GameEngineCollision* Collision;
	InGameCharacterAnimationControllerComponent* Animation;
};
