#pragma once
#include "MonsterWeaponBase.h"
#include "Delegates.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineUpdateObject;
class BulldogShooter : public MonsterWeaponBase
{
public:
	BulldogShooter();
	~BulldogShooter();
	BulldogShooter(const BulldogShooter& _Other) = delete;
	BulldogShooter(BulldogShooter&& _Other) noexcept = delete;
	BulldogShooter& operator=(const BulldogShooter& _Other) = delete;
	BulldogShooter& operator=(BulldogShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

