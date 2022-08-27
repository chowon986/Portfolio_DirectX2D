#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Delegates.h"
#include "ItemBase.h"

class SuperItemBase : public ItemBase
{
public:
	SuperItemBase();
	~SuperItemBase();
	SuperItemBase(const SuperItemBase& _Other) = delete;
	SuperItemBase(SuperItemBase&& _Other) noexcept = delete;
	SuperItemBase& operator=(const SuperItemBase& _Other) = delete;
	SuperItemBase& operator=(SuperItemBase&& _Other) noexcept = delete;
};

