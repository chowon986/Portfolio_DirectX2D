#pragma once
#include "WeaponItemBase.h"

class SpreadShooterItem: public WeaponItemBase
{
public:
	SpreadShooterItem();
	~SpreadShooterItem();
	SpreadShooterItem(const SpreadShooterItem& _Other) = delete;
	SpreadShooterItem(SpreadShooterItem&& _Other) noexcept = delete;
	SpreadShooterItem& operator=(const SpreadShooterItem& _Other) = delete;
	SpreadShooterItem& operator=(SpreadShooterItem&& _Other) noexcept = delete;

};

