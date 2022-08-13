#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class TennisballShooter : public MonsterWeaponBase
{
public:
	TennisballShooter();
	~TennisballShooter();
	TennisballShooter(const TennisballShooter& _Other) = delete;
	TennisballShooter(TennisballShooter&& _Other) noexcept = delete;
	TennisballShooter& operator=(const TennisballShooter& _Other) = delete;
	TennisballShooter& operator=(TennisballShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	InGameMonsterAttackState MonsterAttackState;
};

