#pragma once
#include "Delegates.h"

class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();
	ItemBase(const ItemBase& _Other) = delete;
	ItemBase(ItemBase&& _Other) noexcept = delete;
	ItemBase& operator=(const ItemBase& _Other) = delete;
	ItemBase& operator=(ItemBase&& _Other) noexcept = delete;

public:
	std::string ItemName;
};

