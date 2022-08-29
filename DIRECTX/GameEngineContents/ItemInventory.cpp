#include "PreCompile.h"
#include "ItemInventory.h"

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
}

void ItemInventory::Update(float _DeltaTime)
{
	if (true == IsUpdate())
	{
		//if (OnceCheck == true)
		//{
			for (std::string ItemName : PurchasedItem)
			{
				if (ItemName != "")
				{
					GameEngineTextureRenderer* Test = CreateComponent<GameEngineTextureRenderer>();
					Test->CreateFrameAnimationFolder(PurchasedItem[0]+"Equip", FrameAnimation_DESC(PurchasedItem[0] + "Equip", 0.1f, false));
					Test->ChangeFrameAnimation(PurchasedItem[0] + "Equip");
					Test->SetScaleModeImage();			
					Test->GetTransform().SetWorldPosition({ Test->GetTransform().GetWorldPosition().x, Test->GetTransform().GetWorldPosition().y, -50 });
;					Test->ChangeCamera(CAMERAORDER::UICAMERA);
					OnceCheck = false;
				}
			}
		/*}*/
	}
}

void ItemInventory::End()
{
}