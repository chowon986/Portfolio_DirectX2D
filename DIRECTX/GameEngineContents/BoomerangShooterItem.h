#pragma once
#include "WeaponItemBase.h"

class BoomerangShooterItem : public WeaponItemBase
{
public:
	BoomerangShooterItem();
	~BoomerangShooterItem();
	BoomerangShooterItem(const BoomerangShooterItem& _Other) = delete;
	BoomerangShooterItem(BoomerangShooterItem&& _Other) noexcept = delete;
	BoomerangShooterItem& operator=(const BoomerangShooterItem& _Other) = delete;
	BoomerangShooterItem& operator=(BoomerangShooterItem&& _Other) noexcept = delete;

};

