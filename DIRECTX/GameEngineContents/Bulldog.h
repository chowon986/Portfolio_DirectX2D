#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineCollision;
class InGameMonsterMovementComponent;
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
	void SetStateIdle(const FrameAnimation_DESC& _Info);
	bool OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);
	void BulldogDieCheck(const FrameAnimation_DESC& _Info);

private:
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* Renderer;
	InGameMonsterMovementComponent* Movement;
	InGameMonsterAnimationControllerComponent* Animation;
	float ElapsedTime;
	float AttackIntervalTime;
};
