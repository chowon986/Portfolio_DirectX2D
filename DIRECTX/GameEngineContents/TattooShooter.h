#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class TattooShooter : public MonsterWeaponBase
{
public:
	TattooShooter();
	~TattooShooter();
	TattooShooter(const TattooShooter& _Other) = delete;
	TattooShooter(TattooShooter&& _Other) noexcept = delete;
	TattooShooter& operator=(const TattooShooter& _Other) = delete;
	TattooShooter& operator=(TattooShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	InGameMonsterAttackState MonsterAttackState;

};

