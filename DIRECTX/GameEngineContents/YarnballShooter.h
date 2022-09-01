#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class YarnballShooter : public MonsterWeaponBase
{
public:
	YarnballShooter();
	~YarnballShooter();
	YarnballShooter(const YarnballShooter& _Other) = delete;
	YarnballShooter(YarnballShooter&& _Other) noexcept = delete;
	YarnballShooter& operator=(const YarnballShooter& _Other) = delete;
	YarnballShooter& operator=(YarnballShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void UpdatePivot() override;

private:
	InGameMonsterAttackState MonsterAttackState;
};

