#include "PreCompile.h"
#include "TwinHeartItem.h"

TwinHeartItem::TwinHeartItem()
{
	ItemName = "TwinHeart";
	Type = ItemType::Charm;
	MaxHP = 4;
	OnDashInvisible = false;
}

TwinHeartItem::~TwinHeartItem()
{
}
