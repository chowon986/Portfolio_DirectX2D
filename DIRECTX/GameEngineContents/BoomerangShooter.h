#pragma once
#include "WeaponBase.h"
#include "Delegates.h"

enum class InGameCharacterState;
enum class InGameCharacterAttackState;
class GameEngineUpdateObject;
class BoomerangShooter : public WeaponBase
{
public:
	BoomerangShooter();
	~BoomerangShooter();
	BoomerangShooter(const BoomerangShooter& _Other) = delete;
	BoomerangShooter(BoomerangShooter&& _Other) noexcept = delete;
	BoomerangShooter& operator=(const BoomerangShooter& _Other) = delete;
	BoomerangShooter& operator=(BoomerangShooter&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

