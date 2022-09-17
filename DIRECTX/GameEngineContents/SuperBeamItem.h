#pragma once
#include "ItemBase.h"

class SuperBeamItem : public ItemBase
{
public:
	SuperBeamItem();
	~SuperBeamItem();
	SuperBeamItem(const SuperBeamItem& _Other) = delete;
	SuperBeamItem(SuperBeamItem&& _Other) noexcept = delete;
	SuperBeamItem& operator=(const SuperBeamItem& _Other) = delete;
	SuperBeamItem& operator=(SuperBeamItem&& _Other) noexcept = delete;

};

