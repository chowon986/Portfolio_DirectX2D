#pragma once
#include "WeaponItemBase.h"

class SuperInvincibleItem : public WeaponItemBase
{
public:
	SuperInvincibleItem();
	~SuperInvincibleItem();
	SuperInvincibleItem(const SuperInvincibleItem& _Other) = delete;
	SuperInvincibleItem(SuperInvincibleItem&& _Other) noexcept = delete;
	SuperInvincibleItem& operator=(const SuperInvincibleItem& _Other) = delete;
	SuperInvincibleItem& operator=(SuperInvincibleItem&& _Other) noexcept = delete;

};

