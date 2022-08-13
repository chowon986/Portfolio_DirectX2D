#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMovementComponent;
class InGameMonsterAnimationControllerComponent;
class Ph1Dog : public IInGameMonsterBase
{
public:
	Ph1Dog();
	~Ph1Dog();

	// delete Function
	Ph1Dog(const Ph1Dog& _Other) = delete;
	Ph1Dog(Ph1Dog&& _Other) noexcept = delete;
	Ph1Dog& operator=(const Ph1Dog& _Other) = delete;
	Ph1Dog& operator=(Ph1Dog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

private:
	void OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttackAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	bool AnimationDirectionSwtich();

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState; 
	InGameMovementComponent* Movement;
	InGameMonsterAnimationControllerComponent* Animation;
	GameEngineCollision* Collision;
	BulldogPlane* Plane;
	bool MoveWithPlaneOn;
	float ElapsedTime;
	float AttackIntervalTime;
	bool CountTimeOnOff;
	bool IsAnimationDiretionRight;
};