#include "PreCompile.h"
#include "SpreadShooterItem.h"

SpreadShooterItem::SpreadShooterItem()
	: WeaponItemBase()
{
	ItemName = "SpreadShooter";
	Type = ItemType::Shoot;
}

SpreadShooterItem::~SpreadShooterItem()
{
}
