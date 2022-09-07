#include "PreCompile.h"
#include "PeaShooterItem.h"

PeaShooterItem::PeaShooterItem()
	: WeaponItemBase()
{
	ItemName = "PeaShooter";
	Type = ItemType::Shoot;
}

PeaShooterItem::~PeaShooterItem()
{
}
