#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class InGameMovementComponent;
class InGameMonsterAnimationControllerComponent;
class Bulldog : public IInGameMonsterBase
{
public:
	Bulldog();
	~Bulldog();

	// delete Function
	Bulldog(const Bulldog& _Other) = delete;
	Bulldog(Bulldog&& _Other) noexcept = delete;
	Bulldog& operator=(const Bulldog& _Other) = delete;
	Bulldog& operator=(Bulldog&& _Other) noexcept = delete;


public:
	float4 GetBeforePosition() { return BeforePosition; }
	void SetBeforePosition(float4 _BeforePosition) { BeforePosition = _BeforePosition; }
	bool DirectionChangeOnOffSwitch();
	bool AttackChangeOnOffSwitch();
	void LookRight();
	void LookLeft();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;
	void UpdateState();

private:
	void PrepareAttack1();
	void PrepareAttack2();
	void Unmount();
	void Mount();
	void FinishAttack();
	void OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info);
	bool OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);
	void BulldogDieCheck(const FrameAnimation_DESC& _Info);
	void OnUnmountAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnBulldogLookAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnPrepareAttackAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnAttackFinishAnimationFinished(const FrameAnimation_DESC& _Info);

	void OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnMountAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnPrePareAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	
	void OnBulldogIdleAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnBulldogMountAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnAttackFinish2AnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* LegRenderer;
	InGameMovementComponent* Movement;
	InGameMonsterAnimationControllerComponent* Animation;
	float4 BeforePosition;
	bool DirecitonChangeOn;
	bool Attack1On;
	bool MoveWithPlaneOn;
	int OnceAttack1FrameChanged;
	int OnceAttack2FrameChanged;
	BulldogPlane* Plane;
	float PlayerPosX;
};
