#include "PreCompile.h"
#include "SmokeBombItem.h"

SmokeBombItem::SmokeBombItem()
{
	ItemName = "SmokeBomb";
	Type = ItemType::Charm;
	MaxHP = 3;
	OnDashInvisible = true;
}

SmokeBombItem::~SmokeBombItem()
{
}
