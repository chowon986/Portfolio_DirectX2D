#pragma once
#include "Delegates.h"
#include "ItemBase.h"

class WeaponBase;
class CharmItemBase : public ItemBase
{
public:
	CharmItemBase();
	~CharmItemBase();
	CharmItemBase(const CharmItemBase& _Other) = delete;
	CharmItemBase(CharmItemBase&& _Other) noexcept = delete;
	CharmItemBase& operator=(const CharmItemBase& _Other) = delete;
	CharmItemBase& operator=(CharmItemBase&& _Other) noexcept = delete;

public:
	CharacterType PlayerCharacterType;
	int MaxHP;
	std::vector<WeaponBase*> Weapons;
};

