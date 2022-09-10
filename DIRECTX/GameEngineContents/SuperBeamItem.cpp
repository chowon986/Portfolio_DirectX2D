#include "PreCompile.h"
#include "SuperBeamItem.h"

SuperBeamItem::SuperBeamItem()
{
	WeaponItemBase();
	ItemName = "SuperBeam";
	Type = ItemType::Super;
}

SuperBeamItem::~SuperBeamItem()
{
}
