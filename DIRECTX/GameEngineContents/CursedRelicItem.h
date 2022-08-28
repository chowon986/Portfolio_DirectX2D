#pragma once
#include "WeaponItemBase.h"

class CursedRelicItem : public WeaponItemBase
{
public:
	CursedRelicItem();
	~CursedRelicItem();
	CursedRelicItem(const CursedRelicItem& _Other) = delete;
	CursedRelicItem(CursedRelicItem&& _Other) noexcept = delete;
	CursedRelicItem& operator=(const CursedRelicItem& _Other) = delete;
	CursedRelicItem& operator=(CursedRelicItem&& _Other) noexcept = delete;

};

