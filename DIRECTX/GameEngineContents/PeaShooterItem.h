#pragma once
#include "WeaponItemBase.h"

class PeaShooterItem : public WeaponItemBase
{
public:
	PeaShooterItem();
	~PeaShooterItem();
	PeaShooterItem(const PeaShooterItem& _Other) = delete;
	PeaShooterItem(PeaShooterItem&& _Other) noexcept = delete;
	PeaShooterItem& operator=(const PeaShooterItem& _Other) = delete;
	PeaShooterItem& operator=(PeaShooterItem&& _Other) noexcept = delete;

};

