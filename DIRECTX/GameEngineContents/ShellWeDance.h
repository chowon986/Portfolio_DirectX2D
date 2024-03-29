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
class CogWheel;
class ShellWeDanceDust;
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

public:
	void SetWheel(CogWheel* _Wheel) { Wheel = _Wheel; }

public:
	float4 MoveDirection;

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
	void SetPhysicsComponent(ShellWeDancePhysicsComponent* _Physics) { Physics = _Physics; }
	ShellWeDancePhysicsComponent* GetPhysicsComponent() { return Physics; }
	void OnShellWeDanceDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnShellWeDanceIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);	
	void OnShellWeDanceAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void SetCurAnimationName(std::string _AnimationName) { CurAnimationName = _AnimationName; }
	std::string GetCurAnimationName() { return CurAnimationName; }
	CollisionReturn OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* SnowRenderer;
	GameEngineTextureRenderer* SnowTopperRenderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	ShellWeDancePhysicsComponent* Physics;
	CogWheel* Wheel;
	std::string CurAnimationName;
	float4 BeforeMoveDirection;
	ShellWeDanceDust* Dust;
};