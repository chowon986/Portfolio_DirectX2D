#include "PreCompile.h"
#include "TwinHeartItem.h"

TwinHeartItem::TwinHeartItem()
{
	ItemName = "TwinHeart";
	Type = ItemType::Charm;
	MaxHP = 5;
	OnDashInvisible = false;
}

TwinHeartItem::~TwinHeartItem()
{
}
