#include "PreCompile.h"
#include "CursedRelicItem.h"

CursedRelicItem::CursedRelicItem()
{
	WeaponItemBase();
	ItemName = "CursedRelic";
	Type = ItemType::Charm;
}

CursedRelicItem::~CursedRelicItem()
{
}
