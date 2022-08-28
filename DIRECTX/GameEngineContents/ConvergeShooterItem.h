#pragma once
#include "WeaponItemBase.h"

class ConvergeShooterItem : public WeaponItemBase
{
public:
	ConvergeShooterItem();
	~ConvergeShooterItem();
	ConvergeShooterItem(const ConvergeShooterItem& _Other) = delete;
	ConvergeShooterItem(ConvergeShooterItem&& _Other) noexcept = delete;
	ConvergeShooterItem& operator=(const ConvergeShooterItem& _Other) = delete;
	ConvergeShooterItem& operator=(ConvergeShooterItem&& _Other) noexcept = delete;

};

