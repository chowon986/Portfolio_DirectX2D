#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterAttackState;
class GameEngineUpdateObject;
class SpreadShooter : public WeaponBase
{
public:
	SpreadShooter();
	~SpreadShooter();
	SpreadShooter(const SpreadShooter& _Other) = delete;
	SpreadShooter(SpreadShooter&& _Other) noexcept = delete;
	SpreadShooter& operator=(const SpreadShooter& _Other) = delete;
	SpreadShooter& operator=(SpreadShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

