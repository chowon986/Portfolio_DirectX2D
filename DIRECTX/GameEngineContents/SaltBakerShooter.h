#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class StrawberryBullet;
class SaltBakerShooter : public MonsterWeaponBase
{
public:
	SaltBakerShooter();
	~SaltBakerShooter();
	SaltBakerShooter(const SaltBakerShooter& _Other) = delete;
	SaltBakerShooter(SaltBakerShooter&& _Other) noexcept = delete;
	SaltBakerShooter& operator=(const SaltBakerShooter& _Other) = delete;
	SaltBakerShooter& operator=(SaltBakerShooter&& _Other) noexcept = delete;

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
	std::map<int, float> StrawberryBulletStartPosX;
	bool StartPosSwitch;
	float SugarBulletStartPosX;
	float LimeBulletStartPosX;
	float LimeBulletStartPosY;
	int SugarAttackCount;
	int DoughAttackCount;
	int LimeAttackCount;
	bool CanDoughAttackWithBerry;
	bool Switch;
};

