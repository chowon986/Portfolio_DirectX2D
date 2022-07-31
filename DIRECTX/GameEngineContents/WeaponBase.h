#pragma once
#include "GameEngineCore/GameEngineActor.h"

enum class InGameCharacterAttackState;
enum class InGameCharacterState;
class IInGameCharacterBase;
class WeaponBase : public GameEngineActor
{
public:
	WeaponBase();
	~WeaponBase();
	WeaponBase(const WeaponBase& _Other) = delete;
	WeaponBase(WeaponBase&& _Other) noexcept = delete;
	WeaponBase& operator=(const WeaponBase& _Other) = delete;
	WeaponBase& operator=(WeaponBase&& _Other) noexcept = delete;

	std::string GetVerticalDirection() { return VerticalDirection; }
	std::string GetHorizontalDirection() { return HorizontalDirection; }

protected:
	virtual void UpdateDirection();
	void Update(float _DeltaTime) override;

protected:
	float IntervalTime;
	float ElapsedTime;
	std::string VerticalDirection;
	std::string HorizontalDirection;
	IInGameCharacterBase* Character;
	InGameCharacterState State;
	std::string CharacterHorizontalDirection;
	std::string CharacterVerticalDirection;
	InGameCharacterAttackState AttackState;
};

