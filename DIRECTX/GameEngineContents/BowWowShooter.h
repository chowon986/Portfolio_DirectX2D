#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class BowWowShooter : public MonsterWeaponBase
{
public:
	BowWowShooter();
	~BowWowShooter();
	BowWowShooter(const BowWowShooter& _Other) = delete;
	BowWowShooter(BowWowShooter&& _Other) noexcept = delete;
	BowWowShooter& operator=(const BowWowShooter& _Other) = delete;
	BowWowShooter& operator=(BowWowShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	void Shoot(InGameMonsterAttackState State);
};

