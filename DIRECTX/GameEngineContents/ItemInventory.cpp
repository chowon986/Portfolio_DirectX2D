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
	InventoryScreen->GetTransform().SetLocalPosition({ 0.0f, -0.0f,(int)ZOrder::UI });
	InventoryScreen->ChangeCamera(CAMERAORDER::UICAMERA2);

}

void ItemInventory::Update(float _DeltaTime)
{

	std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			for (ItemBase* Item : _State->Items[ItemType::Charm])
			{
				GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
				ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
				ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
				ItemIconRenderer->SetScaleModeImage();
				ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
				ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}

			for (ItemBase* Item : _State->Items[ItemType::Shoot])
			{
				GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
				ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
				ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
				ItemIconRenderer->SetScaleModeImage();
				ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
				ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}

			for (ItemBase* Item : _State->Items[ItemType::Super])
			{
				GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
				ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
				ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
				ItemIconRenderer->SetScaleModeImage();
				ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
				ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
		}

	}
}

void ItemInventory::End()
{
}