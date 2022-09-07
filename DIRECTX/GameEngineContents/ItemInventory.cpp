#include "PreCompile.h"
#include "ItemInventory.h"
#include "CharacterState.h"
#include "ItemBase.h"

ItemInventory::ItemInventory()
	:OnceCheck(true)
{
}

ItemInventory::~ItemInventory()
{
}

void ItemInventory::Start()
{
	GameEngineTextureRenderer* InventoryScreen = CreateComponent<GameEngineTextureRenderer>();
	InventoryScreen->SetTexture("slot_selection_bg.png");
	InventoryScreen->ScaleToTexture();
	InventoryScreen->ChangeCamera(CAMERAORDER::UICAMERA);

	std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			for (ItemBase* Item : _State->Items[ItemType::Charm])
			{
				GameEngineTextureRenderer* Test = CreateComponent<GameEngineTextureRenderer>();
				Test->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
				Test->ChangeFrameAnimation(Item->ItemName + "Equip");
				Test->SetScaleModeImage();
				Test->GetTransform().SetWorldPosition({ Test->GetTransform().GetWorldPosition().x, Test->GetTransform().GetWorldPosition().y, (int)ZOrder::UI});
				Test->ChangeCamera(CAMERAORDER::UICAMERA);
			}

			for (ItemBase* Item : _State->Items[ItemType::Shoot])
			{

			}

			for (ItemBase* Item : _State->Items[ItemType::Super])
			{

			}
		}

	}
}

void ItemInventory::Update(float _DeltaTime)
{
}

void ItemInventory::End()
{
}