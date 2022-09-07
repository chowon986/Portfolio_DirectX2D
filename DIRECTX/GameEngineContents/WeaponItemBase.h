#pragma once
#include "Delegates.h"
#include "ItemBase.h"

class WeaponBase;
class WeaponItemBase : public ItemBase
{
public:
	WeaponItemBase();
	~WeaponItemBase();
	WeaponItemBase(const WeaponItemBase& _Other) = delete;
	WeaponItemBase(WeaponItemBase&& _Other) noexcept = delete;
	WeaponItemBase& operator=(const WeaponItemBase& _Other) = delete;
	WeaponItemBase& operator=(WeaponItemBase&& _Other) noexcept = delete;

public:
	WeaponBase* Weapon;	
};

