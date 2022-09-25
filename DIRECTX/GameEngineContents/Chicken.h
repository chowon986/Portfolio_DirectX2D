#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMovementComponent;
class ChickenPhysicsComponent;
class SaltBakerLevel;
class InGameMonsterAnimationControllerComponent;
class Chicken : public IInGameMonsterBase
{
public:
	Chicken();
	~Chicken();

	// delete Function
	Chicken(const Chicken& _Other) = delete;
	Chicken(Chicken&& _Other) noexcept = delete;
	Chicken& operator=(const Chicken& _Other) = delete;
	Chicken& operator=(Chicken&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

public:
	void SetChickenPhysicsComponent(ChickenPhysicsComponent* _Physics);
	ChickenPhysicsComponent* GetChickenPhysicsComponent() { return Physics; }

private:
	void PrepareAttack1();

	void OnChickenIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnChickenPrepareAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnChickenAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnChickenAttackFinish1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnChickenIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	

private:
	SaltBakerLevel* Level;
	GameEngineCollision* Collision;
	ChickenPhysicsComponent* Physics;
	GameEngineTextureRenderer* Renderer;
	
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	
	bool CanAttack;
	float LerpTime;
	float PlayerPosX;
	float AttackIntervalTime;
};