#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"
#include <vector>

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class DogBowlShooter : public MonsterWeaponBase
{
public:
	DogBowlShooter();
	~DogBowlShooter();
	DogBowlShooter(const DogBowlShooter& _Other) = delete;
	DogBowlShooter(DogBowlShooter&& _Other) noexcept = delete;
	DogBowlShooter& operator=(const DogBowlShooter& _Other) = delete;
	DogBowlShooter& operator=(DogBowlShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	InGameMonsterAttackState MonsterAttackState;
};

