#include "PreCompile.h"
#include "SuperInvincibleItem.h"

SuperInvincibleItem::SuperInvincibleItem()
{
	WeaponItemBase();
	ItemName = "SuperInvincible";
	Type = ItemType::Super;
}

SuperInvincibleItem::~SuperInvincibleItem()
{
}
