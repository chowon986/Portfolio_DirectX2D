#include "PreCompile.h"
#include "CharacterState.h"
#include "WeaponItemBase.h"
#include "CharmItemBase.h"
#include "SuperItemBase.h"
#include "PeaShooterItem.h"

CharacterState::CharacterState()
{
}

CharacterState::~CharacterState()
{
	if (EquippedItems.size() > 0)
	{
		for (std::map<InventoryType, ItemBase*>::iterator it = EquippedItems.begin(); it != EquippedItems.end(); it++)
		{
			if (it->second != nullptr)
			{
				delete it->second;
				it->second = nullptr;
			}
		}
		EquippedItems.clear();
	}

	if (Items.size() > 0)
	{
		for (std::map<ItemType, std::vector<ItemBase*>>::iterator it = Items.begin(); it != Items.end(); it++) 
		{
			for (ItemBase* Item : it->second)
			{
				if (Item != nullptr)
				{
					delete Item;
					Item = nullptr;
				}
			}
		}
		Items.clear();
	}
}

void CharacterState::Start()
{
	EquippedItems.insert(std::make_pair<InventoryType, ItemBase*>(InventoryType::ShotA, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, ItemBase*>(InventoryType::ShotB, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, ItemBase*>(InventoryType::Super, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, ItemBase*>(InventoryType::Charm, nullptr));

	Items.insert(std::make_pair<ItemType, std::vector<ItemBase*>>(ItemType::Shoot, std::vector<ItemBase*>()));
	Items.insert(std::make_pair<ItemType, std::vector<ItemBase*>>(ItemType::Super, std::vector<ItemBase*>()));
	Items.insert(std::make_pair<ItemType, std::vector<ItemBase*>>(ItemType::Charm, std::vector<ItemBase*>()));


	if (false == GameEngineInput::GetInst()->IsKey("AddCoin"))
	{
		GameEngineInput::GetInst()->CreateKey("AddCoin", VK_OEM_PLUS);
		GameEngineInput::GetInst()->CreateKey("MinusCoin", VK_OEM_MINUS);
	}
}

void CharacterState::OnLevelChanged()
{
	{	
		ItemBase* item = EquippedItems[InventoryType::Charm];
		if (CharmItemBase* ItemBase = dynamic_cast<CharmItemBase*>(item))
		{
			MaxHP = ItemBase->MaxHP;
			Type = ItemBase->PlayerCharacterType;
		}
	}

	{
		ItemBase* item = EquippedItems[InventoryType::Super];
		if (SuperItemBase* ItemBase = dynamic_cast<SuperItemBase*>(item))
		{

		}
	}

	{
		ItemBase* item = EquippedItems[InventoryType::ShotA];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item))
		{

		}
	}

	{
		ItemBase* item = EquippedItems[InventoryType::ShotB];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item))
		{
		}
	}
}

void CharacterState::SetEquippedItem(InventoryType _Item, ItemBase* _ItemBase)
{
	EquippedItems[_Item] = _ItemBase;
	switch (_Item) {
	case InventoryType::Charm:
		if (CharmItemBase* Item = dynamic_cast<CharmItemBase*>(_ItemBase))
		{
			MaxHP = Item->MaxHP;
			Type = Item->PlayerCharacterType;
			OnDashInvisible = Item->OnDashInvisible;
		}
		break;
	}
}

void CharacterState::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("AddCoin"))
	{
		++Coin;
	}
	else if(true == GameEngineInput::GetInst()->IsDown("MinusCoin"))
	{
		--Coin;
	}
}

void CharacterState::End()
{
}
