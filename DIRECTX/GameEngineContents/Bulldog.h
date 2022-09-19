#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class BulldogPlane;
class Ph1Dog;
class InGameCharacter;
class DogCopterPhase1;
class GameEngineCollision;
class InGameMovementComponent;
class InGameMonsterAnimationControllerComponent;
class Bulldog : public IInGameMonsterBase
{
public:
	Bulldog();
	~Bulldog();

	Bulldog(const Bulldog& _Other) = delete;
	Bulldog(Bulldog&& _Other) noexcept = delete;
	Bulldog& operator=(const Bulldog& _Other) = delete;
	Bulldog& operator=(Bulldog&& _Other) noexcept = delete;

public:
	float4 GetBeforePosition() { return BeforePosition; }
	void SetBeforePosition(float4 _BeforePosition) { BeforePosition = _BeforePosition; }

	void SetPh1Dog(Ph1Dog* _Dog) { Dog = _Dog; }
	Ph1Dog* GetPh1Dog() { return Dog; }

	void LookLeft();
	void LookRight();
	bool AttackChangeOnOffSwitch();
	bool DirectionChangeOnOffSwitch();

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
	void Unmount();
	void Mount();
	void PrepareAttack1();
	void PrepareAttack2();
	void FinishAttack();
	void BulldogDieCheck(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnBulldogIdleAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnBulldogLookAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnAttackFinishAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnPrepareAttackAnimationFinished(const FrameAnimation_DESC& _Info);

	void OnUnmountAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnPrepareAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnPrepareAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnMountAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void Test(const FrameAnimation_DESC& _Info);
	
	CollisionReturn OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);

	void SetEndPos(float4 _EndPos) { EndPos = _EndPos; }
	float4 GetEndPos() { return EndPos; }

private:
	BulldogPlane* Plane;
	DogCopterPhase1* DogCopter;
	GameEngineCollision* Collision;
	InGameMovementComponent* Movement;
	GameEngineTextureRenderer* Renderer;
	InGameMonsterAnimationControllerComponent* Animation;
	float4 BeforePosition;
	bool Attack1On;
	bool MoveWithPlaneOn;
	bool DirecitonChangeOn;
	int OnceAttack1FrameChanged;
	int OnceAttack2FrameChanged;
	float PlayerPosX;
	float CanTakeDamageTime;
	Ph1Dog* Dog;
	float4 EndPos;
	float MoveSpeed;
	float MoveElapsedTime;
};
