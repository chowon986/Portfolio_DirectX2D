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
class Pepper : public IInGameMonsterBase
{
public:
	Pepper();
	~Pepper();

	// delete Function
	Pepper(const Pepper& _Other) = delete;
	Pepper(Pepper&& _Other) noexcept = delete;
	Pepper& operator=(const Pepper& _Other) = delete;
	Pepper& operator=(Pepper&& _Other) noexcept = delete;

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
	IInGameCharacterBase* GetPlayer() { return Player; }
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameMonsterBase* GetMonster() { return Monster; }
	void SetMonster(IInGameMonsterBase* _Monster) { Monster = _Monster; }

private:
	GameEngineTextureRenderer* Renderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	IInGameCharacterBase* Player;
	IInGameMonsterBase* Monster;
	float4 AttackDirection;
};