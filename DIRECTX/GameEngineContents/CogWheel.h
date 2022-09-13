#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMovementComponent;
class IInGameCharacterBase;
class InGameMonsterAnimationControllerComponent;
class CogWheel : public IInGameMonsterBase
{
public:
	CogWheel();
	~CogWheel();

	// delete Function
	CogWheel(const CogWheel& _Other) = delete;
	CogWheel(CogWheel&& _Other) noexcept = delete;
	CogWheel& operator=(const CogWheel& _Other) = delete;
	CogWheel& operator=(CogWheel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

	void Test(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	float4 MoveDirection;
};