#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class LaserShooter : public MonsterWeaponBase
{
public:
	LaserShooter();
	~LaserShooter();
	LaserShooter(const LaserShooter& _Other) = delete;
	LaserShooter(LaserShooter&& _Other) noexcept = delete;
	LaserShooter& operator=(const LaserShooter& _Other) = delete;
	LaserShooter& operator=(LaserShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	InGameMonsterAttackState MonsterAttackState;

};

