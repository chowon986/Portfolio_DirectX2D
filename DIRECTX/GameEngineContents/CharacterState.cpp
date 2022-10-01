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

	Items.clear();
	EquippedItems.clear();
}

void CharacterState::Start()
{
	EquippedItems.insert(std::make_pair<InventoryType, std::shared_ptr<ItemBase>>(InventoryType::ShotA, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, std::shared_ptr<ItemBase>>(InventoryType::ShotB, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, std::shared_ptr<ItemBase>>(InventoryType::Super, nullptr));
	EquippedItems.insert(std::make_pair<InventoryType, std::shared_ptr<ItemBase>>(InventoryType::Charm, nullptr));

	Items.insert(std::make_pair<ItemType, std::vector<std::shared_ptr<ItemBase>>>(ItemType::Shoot, std::vector<std::shared_ptr<ItemBase>>()));
	Items.insert(std::make_pair<ItemType, std::vector<std::shared_ptr<ItemBase>>>(ItemType::Super, std::vector<std::shared_ptr<ItemBase>>()));
	Items.insert(std::make_pair<ItemType, std::vector<std::shared_ptr<ItemBase>>>(ItemType::Charm, std::vector<std::shared_ptr<ItemBase>>()));
}

void CharacterState::OnLevelChanged()
{
	{	
		std::shared_ptr<ItemBase> item = EquippedItems[InventoryType::Charm];
		if (CharmItemBase* ItemBase = dynamic_cast<CharmItemBase*>(item.get()))
		{
			MaxHP = ItemBase->MaxHP;
			Type = ItemBase->PlayerCharacterType;
		}
	}

	{
		std::shared_ptr<ItemBase> item = EquippedItems[InventoryType::Super];
		if (SuperItemBase* ItemBase = dynamic_cast<SuperItemBase*>(item.get()))
		{

		}
	}

	{
		std::shared_ptr<ItemBase> item = EquippedItems[InventoryType::ShotA];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item.get()))
		{

		}
	}

	{
		std::shared_ptr<ItemBase> item = EquippedItems[InventoryType::ShotB];
		if (WeaponItemBase* ItemBase = dynamic_cast<WeaponItemBase*>(item.get()))
		{
		}
	}
}

void CharacterState::SetEquippedItem(InventoryType _Item, std::shared_ptr<ItemBase> _ItemBase)
{
	EquippedItems[_Item] = _ItemBase;
	switch (_Item) {
	case InventoryType::Charm:
		if (CharmItemBase* Item = dynamic_cast<CharmItemBase*>(_ItemBase.get()))
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
