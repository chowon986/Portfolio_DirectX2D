#include "PreCompile.h"
#include "BoomerangShooterItem.h"

BoomerangShooterItem::BoomerangShooterItem()
	: WeaponItemBase()
{
	ItemName = "BoomerangShooter";
	Type = ItemType::Shoot;
}

BoomerangShooterItem::~BoomerangShooterItem()
{
}
