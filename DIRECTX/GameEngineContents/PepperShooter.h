#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class PepperState
{
	Prepare,
	Idle,
	Attack1, // 총알
	Attack2, // 보스 공격
	Death, 
};

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class StrawberryBullet;
class IInGameCharacterBase;
class GameEngineTextureRenderer;
enum class CollisionReturn;
class SaltBaker;
class PepperShooter : public MonsterWeaponBase
{
public:
	PepperShooter();
	~PepperShooter();
	PepperShooter(const PepperShooter& _Other) = delete;
	PepperShooter(PepperShooter&& _Other) noexcept = delete;
	PepperShooter& operator=(const PepperShooter& _Other) = delete;
	PepperShooter& operator=(PepperShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void UpdateDirection() override;
	void UpdatePivot() override;
	void OnMonsterStateChanged(InGameMonsterState _State) override;
	void OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState) override;

	void UpdateAnimation();

	void SetHP(int _HP) { HP = _HP; }
	int GetHP() { return HP; }
	
	CollisionReturn OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other);

	void SetPepperState(PepperState _State);
	PepperState GetPepperState() { return State; }

	void OnPepperShooterIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPepperShooterAttackAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPepperShooterDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnPepperShooterReturnAnimationFrameFinished(const FrameAnimation_DESC& _Info);

public:
	void SetDeathNum(int _Num);
	int GetDeathNum() { return DeathNum; }

private:
	InGameMonsterAttackState MonsterAttackState;
	IInGameCharacterBase* Player;
	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;
	int HP;
	float CanTakeDamageInterval;
	int DeathNum;
	SaltBaker* Boss;
	float4 DestPos;
	float4 StartPos;
	PepperState State;
	bool StartBodyAttack;
	float ElapsedTimeMove;
};

