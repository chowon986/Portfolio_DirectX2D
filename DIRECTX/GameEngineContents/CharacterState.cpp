#include "PreCompile.h"
#include "CharacterState.h"
#include "WeaponItemBase.h"
#include "CharmItemBase.h"
#include "SuperItemBase.h"

CharacterState::CharacterState()
{
}

CharacterState::~CharacterState()
{
}

void CharacterState::Start()
{
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::ShotA, new WeaponItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::ShotB, new WeaponItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::Charm, new CharmItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::Super, new SuperItemBase()));
}

void CharacterState::OnLevelChanged()
{
	{	
		ItemBase* item = Items[ItemType::Charm];
		if (CharmItemBase* ItemBase = dynamic_cast<CharmItemBase*>(item))
		{
			MaxHP = ItemBase->MaxHP;
		}
	}

	{
		ItemBase* item = Items[ItemType::Super];
		if (SuperItemBase* ItemBase = dynamic_cast<SuperItemBase*>(item))
		{

		}
	}

	{
		ItemBase* item = Items[ItemType::ShotA];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item))
		{

		}
	}

	{
		ItemBase* item = Items[ItemType::ShotB];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item))
		{

		}
	}
}

void CharacterState::Update(float _DeltaTime)
{
}

void CharacterState::End()
{
}
