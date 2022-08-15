#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMonsterAnimationControllerComponent;
class DogCopterArms : public IInGameMonsterBase
{
public:
	DogCopterArms();
	~DogCopterArms();

	// delete Function
	DogCopterArms(const DogCopterArms& _Other) = delete;
	DogCopterArms(DogCopterArms&& _Other) noexcept = delete;
	DogCopterArms& operator=(const DogCopterArms& _Other) = delete;
	DogCopterArms& operator=(DogCopterArms&& _Other) noexcept = delete;

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
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* WristRenderer;
	GameEngineTextureRenderer* LowPadRenderer;
	GameEngineTextureRenderer* MidPadRenderer;
	GameEngineTextureRenderer* TopPadRenderer;
	GameEngineTextureRenderer* PawMergeRenderer;

	InGameMonsterState State;
	InGameMonsterState LeaderState;
	InGameMonsterAttackState AttackState;
	InGameMonsterAttackState LeaderAttackState;
	InGameMonsterAnimationControllerComponent* Animation;
	GameEngineCollision* Collision;

	bool CountTimeOnOff;
	float ElapsedTime;
	float AttackIntervalTime;
};