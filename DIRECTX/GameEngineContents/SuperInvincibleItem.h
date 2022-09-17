#pragma once
#include "ItemBase.h"

class SuperInvincibleItem : public ItemBase
{
public:
	SuperInvincibleItem();
	~SuperInvincibleItem();
	SuperInvincibleItem(const SuperInvincibleItem& _Other) = delete;
	SuperInvincibleItem(SuperInvincibleItem&& _Other) noexcept = delete;
	SuperInvincibleItem& operator=(const SuperInvincibleItem& _Other) = delete;
	SuperInvincibleItem& operator=(SuperInvincibleItem&& _Other) noexcept = delete;

};

