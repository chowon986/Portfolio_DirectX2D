#pragma once
#include "CharmItemBase.h"

class CursedRelicItem : public CharmItemBase
{
public:
	CursedRelicItem();
	~CursedRelicItem();
	CursedRelicItem(const CursedRelicItem& _Other) = delete;
	CursedRelicItem(CursedRelicItem&& _Other) noexcept = delete;
	CursedRelicItem& operator=(const CursedRelicItem& _Other) = delete;
	CursedRelicItem& operator=(CursedRelicItem&& _Other) noexcept = delete;

};

