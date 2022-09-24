#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterAttackState;
class GameEngineUpdateObject;
class ConvergeShooter : public WeaponBase
{
public:
	ConvergeShooter();
	~ConvergeShooter();
	ConvergeShooter(const ConvergeShooter& _Other) = delete;
	ConvergeShooter(ConvergeShooter&& _Other) noexcept = delete;
	ConvergeShooter& operator=(const ConvergeShooter& _Other) = delete;
	ConvergeShooter& operator=(ConvergeShooter&& _Other) noexcept = delete;

private:
	void Shoot() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

