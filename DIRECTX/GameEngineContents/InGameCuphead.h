#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "IInGameCharacterBase.h"

enum class InGameCharacterState;
class WeaponBase;
class CharacterScore;
class CharacterState;
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
	void SpecialAttack();
	void SuperAttack() override;
	void Walk() override;
	void Idle() override;
	void OnStateChanged() override;
	void OnIsOnGroundChanged() override;

	void OnPrepareAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnDashAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnDashAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnTakeDamageAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnExShootAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnExShootAnimationChanged(const FrameAnimation_DESC& _Info);
	void OnGhostAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnShootAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnShootAnimationFrameStarted(const FrameAnimation_DESC& _Info);
	void OnJumpAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void UpdateState();
	void UpdateDirection();
	void CheckCollision();
	void OnCollisionDebug();

	void OpenScoreBoard();
	
	bool GetIsOpenScoreBoard();
	CollisionReturn OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn OnParry(GameEngineCollision* _This, GameEngineCollision* _Other);

	void OnParryAnimationFrameEnd(const FrameAnimation_DESC& _Info);
	void OnParryAnimationFrameStarted(const FrameAnimation_DESC& _Info);

	void SetCharacterState(CharacterState* _State) { State = _State; }
	CharacterState* GetCharacterState() { return State; }

public:
	void SetOnDashInvisible(bool _IsInvisible) { IsInvisible = _IsInvisible; }

private:
	GameEngineTextureRenderer* Renderer;
	bool IsInputEnabled;
	bool IsOpenScoreBoard;
	GameEngineCollision* Collision;
	InGameCharacterMovementCompmonent* Movement;
	InGameCharacterAnimationControllerComponent* Animation;
	bool AlphaOn;
	float CanTakeDamageIntervalTime;
	float CanTakeDamageElapsedTime;
	bool ToggleWeapon;
	bool IsInvisible;
	CharacterState* State;
	CharacterScore* Score;
	WeaponBase* EquippedWeapon;
	float InvisibleElapsedTime;
	bool CountInvisibleTime;
	bool IsTakeDamageInProgess;
};
