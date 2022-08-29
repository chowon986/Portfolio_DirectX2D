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
	if (Items.size() > 0)
	{
		for (std::map<ItemType, ItemBase*>::iterator it = Items.begin(); it != Items.end(); it++)
		{
			delete it->second;
		}
		Items.clear();
	}
}

void CharacterState::Start()
{
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::ShotA, new WeaponItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::ShotB, new WeaponItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::Charm, new CharmItemBase()));
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::Super, new SuperItemBase()));

	if (false == GameEngineInput::GetInst()->IsKey("AddCoin"))
	{
		GameEngineInput::GetInst()->CreateKey("AddCoin", VK_OEM_PLUS);
		GameEngineInput::GetInst()->CreateKey("MinusCoin", VK_OEM_MINUS);
	}
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
