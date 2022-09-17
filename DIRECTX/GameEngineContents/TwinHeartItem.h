#pragma once
#include "CharmItemBase.h"

class TwinHeartItem : public CharmItemBase
{
public:
	TwinHeartItem();
	~TwinHeartItem();
	TwinHeartItem(const TwinHeartItem& _Other) = delete;
	TwinHeartItem(TwinHeartItem&& _Other) noexcept = delete;
	TwinHeartItem& operator=(const TwinHeartItem& _Other) = delete;
	TwinHeartItem& operator=(TwinHeartItem&& _Other) noexcept = delete;

};

