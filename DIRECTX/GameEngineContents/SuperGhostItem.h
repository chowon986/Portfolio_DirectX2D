#pragma once
#include "WeaponItemBase.h"

class SuperGhostItem : public WeaponItemBase
{
public:
	SuperGhostItem();
	~SuperGhostItem();
	SuperGhostItem(const SuperGhostItem& _Other) = delete;
	SuperGhostItem(SuperGhostItem&& _Other) noexcept = delete;
	SuperGhostItem& operator=(const SuperGhostItem& _Other) = delete;
	SuperGhostItem& operator=(SuperGhostItem&& _Other) noexcept = delete;

};

