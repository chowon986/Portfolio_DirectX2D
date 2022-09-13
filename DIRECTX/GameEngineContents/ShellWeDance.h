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
class ShellWeDancePhysicsComponent;
class ShellWeDance : public IInGameMonsterBase
{
public:
	ShellWeDance();
	~ShellWeDance();

	// delete Function
	ShellWeDance(const ShellWeDance& _Other) = delete;
	ShellWeDance(ShellWeDance&& _Other) noexcept = delete;
	ShellWeDance& operator=(const ShellWeDance& _Other) = delete;
	ShellWeDance& operator=(ShellWeDance&& _Other) noexcept = delete;

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

public:
	void SetPhysicsComponent(ShellWeDancePhysicsComponent* _Physics) { Physics = _Physics;}
	ShellWeDancePhysicsComponent* GetPhysicsComponent() { return Physics; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	float4 MoveDirection;
	ShellWeDancePhysicsComponent* Physics;
};