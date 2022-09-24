#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterState;
enum class InGameCharacterAttackState;
class GameEngineUpdateObject;
class ChargerShooter : public WeaponBase
{
public:
	ChargerShooter();
	~ChargerShooter();
	ChargerShooter(const ChargerShooter& _Other) = delete;
	ChargerShooter(ChargerShooter&& _Other) noexcept = delete;
	ChargerShooter& operator=(const ChargerShooter& _Other) = delete;
	ChargerShooter& operator=(ChargerShooter&& _Other) noexcept = delete;

private:
	void Shoot() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float ChargeTime;
};

