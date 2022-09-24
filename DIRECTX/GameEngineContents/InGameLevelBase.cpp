#include "PreCompile.h"
#include "InGameLevelBase.h"
#include <GameEngineContents/CharacterState.h>
#include <GameEngineContents/WeaponItemBase.h>
#include <GameEngineContents/WeaponBase.h>

InGameLevelBase::InGameLevelBase()
	: CurrentPhase(Phase::Phase1)
{
}

InGameLevelBase::~InGameLevelBase()
{
}

Phase InGameLevelBase::GetPhase()
{
	return CurrentPhase;
}

void InGameLevelBase::SetPhase(Phase _Phase)
{
	if (GetPhase() != _Phase)
	{
		CurrentPhase = _Phase;
		PhaseChangedDelegate.Invoke(CurrentPhase);
	}
}

void InGameLevelBase::Start()
{
}

void InGameLevelBase::Update(float _DeltaTime)
{
	
}

void InGameLevelBase::End()
{
}

void InGameLevelBase::LevelEndEvent()
{
	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* State = dynamic_cast<CharacterState*>(Actor))
		{
			for (std::shared_ptr<ItemBase> Item : State->Items[ItemType::Shoot])
			{
				if (WeaponItemBase* WeaponItem = dynamic_cast<WeaponItemBase*>(Item.get()))
				{
					if (nullptr != WeaponItem->Weapon)
					{
						WeaponItem->Weapon->SetParent(nullptr);
					}
				}
			}
		}
	}
}
