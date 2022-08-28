#pragma once
#include "WeaponItemBase.h"

class SmokeBombItem : public WeaponItemBase
{
public:
	SmokeBombItem();
	~SmokeBombItem();
	SmokeBombItem(const SmokeBombItem& _Other) = delete;
	SmokeBombItem(SmokeBombItem&& _Other) noexcept = delete;
	SmokeBombItem& operator=(const SmokeBombItem& _Other) = delete;
	SmokeBombItem& operator=(SmokeBombItem&& _Other) noexcept = delete;

};

