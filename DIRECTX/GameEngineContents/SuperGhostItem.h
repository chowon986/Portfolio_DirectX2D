#pragma once
#include "ItemBase.h"

class SuperGhostItem : public ItemBase
{
public:
	SuperGhostItem();
	~SuperGhostItem();
	SuperGhostItem(const SuperGhostItem& _Other) = delete;
	SuperGhostItem(SuperGhostItem&& _Other) noexcept = delete;
	SuperGhostItem& operator=(const SuperGhostItem& _Other) = delete;
	SuperGhostItem& operator=(SuperGhostItem&& _Other) noexcept = delete;

};

