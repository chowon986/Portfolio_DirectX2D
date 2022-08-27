#include "PreCompile.h"
#include "CharacterState.h"
#include "WeaponItemBase.h"
#include "CharmItemBase.h"

CharacterState::CharacterState()
{
}

CharacterState::~CharacterState()
{
}

void CharacterState::Start()
{
	Items.insert(std::make_pair<ItemType, ItemBase*>(ItemType::ShotA, new WeaponItemBase()));

}

void CharacterState::OnLevelChanged()
{
	ItemBase* item = Items[ItemType::Charm];
	if (CharmItemBase* ItemBase = dynamic_cast<CharmItemBase*>(item))
	{
		MaxHP = ItemBase->MaxHP;

	}
}

void CharacterState::Update(float _DeltaTime)
{
}

void CharacterState::End()
{
}
