#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class StrawberryBullet;
class IInGameCharacterBase;
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

private:
	InGameMonsterAttackState MonsterAttackState;
	IInGameCharacterBase* Player;
};

