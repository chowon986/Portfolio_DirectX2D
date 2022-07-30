#pragma once
#include "GameEngineCore/GameEngineActor.h"

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
	float IntervalTime;
	float ElapsedTime;
	std::string VerticalDirection;
	std::string HorizontalDirection;
};

