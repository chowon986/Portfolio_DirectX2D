#include "PreCompile.h"
#include "ItemInventory.h"
#include "CharacterState.h"
#include "ItemBase.h"

ItemInventory::ItemInventory()
	:OnceCheck(true)
	, Phase(InventoryPhase::Front)
	, CurPos(0)
	, BeforePhase(InventoryPhase::None)
	, ShotASlot(nullptr)
{
}

ItemInventory::~ItemInventory()
{
}

void ItemInventory::Start()
{
	SelectorPosFront.push_back(float4{ -200.0f,-165.0f });
	SelectorPosFront.push_back(float4{ -100.0f,-165.0f });
	SelectorPosFront.push_back(float4{ -2.0f,-165.0f });
	SelectorPosFront.push_back(float4{ 98.0f,-165.0f });
	SelectorPosFront.push_back(float4{ 198.0f,-165.0f });
	SelectorPosA.push_back(float4{ -200.0f,-100.0f });

	InventoryFront = CreateComponent<GameEngineTextureRenderer>();
	InventoryFront->SetTexture("ch_equip_front.png");
	InventoryFront->ScaleToTexture();
	InventoryFront->GetTransform().SetLocalPosition({ 0.0f, -0.0f,(int)ZOrder::UI });
	InventoryFront->ChangeCamera(CAMERAORDER::UICAMERA2);



	Selector = CreateComponent<GameEngineTextureRenderer>();
	Selector->CreateFrameAnimationFolder("Selector", FrameAnimation_DESC("Selector", 0.05f, true));
	Selector->ChangeFrameAnimation("Selector");
	Selector->SetScaleModeImage();
	Selector->GetTransform().SetLocalPosition(SelectorPosFront[0]);
	Selector->ChangeCamera(CAMERAORDER::UICAMERA2);

	SetPhase(InventoryPhase::Front);
}

void ItemInventory::Update(float _DeltaTime)
{
	if (GetPhase() == InventoryPhase::Front)
	{
		if (BeforePhase != GetPhase())
		{
			BeforePhase = Phase;
			if (FrontARenderer != nullptr)
			{
				FrontARenderer->On();
				FrontBRenderer->On();
				FrontCRenderer->On();
				FrontDRenderer->On();
				InventoryFront->SetTexture("ch_equip_front.png");
			}
			CurPos = 0;
			Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
		}

		InventoryFront->On();
		std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
			{
				ItemBase* EquippedItemShotA = _State->EquippedItems[InventoryType::ShotA];
				ItemBase* EquippedItemShotB = _State->EquippedItems[InventoryType::ShotB];
				ItemBase* EquippedItemSuper = _State->EquippedItems[InventoryType::Super];
				ItemBase* EquippedItemCharm = _State->EquippedItems[InventoryType::Charm];

				if (nullptr != EquippedItemShotA)
				{
					if (EquippedShotAName != EquippedItemShotA->ItemName + "Equip")
					{
						EquippedShotAName = EquippedItemShotA->ItemName + "Equip";
						FrontARenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontARenderer->CreateFrameAnimationFolder(EquippedShotAName, FrameAnimation_DESC(EquippedShotAName, 0.05f, true));
						FrontARenderer->ChangeFrameAnimation(EquippedShotAName);
						FrontARenderer->SetScaleModeImage();
						FrontARenderer->GetTransform().SetLocalPosition({ -198.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontARenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}
				else
				{
					if (EquippedShotAName != "UnKnwon")
					{
						EquippedShotAName = "UnKnwon";
						FrontARenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontARenderer->CreateFrameAnimationFolder(EquippedShotAName, FrameAnimation_DESC(EquippedShotAName, 0.05f, true));
						FrontARenderer->ChangeFrameAnimation(EquippedShotAName);
						FrontARenderer->SetScaleModeImage();
						FrontARenderer->GetTransform().SetLocalPosition({ -198.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontARenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}

				if (nullptr != EquippedItemShotB)
				{
					if (EquippedShotBName != EquippedItemShotB->ItemName + "Equip")
					{
						EquippedShotBName = EquippedItemShotB->ItemName + "Equip";
						FrontBRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontBRenderer->CreateFrameAnimationFolder(EquippedShotBName, FrameAnimation_DESC(EquippedShotBName, 0.05f, true));
						FrontBRenderer->ChangeFrameAnimation(EquippedShotBName);
						FrontBRenderer->SetScaleModeImage();
						FrontBRenderer->GetTransform().SetLocalPosition({ -98.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontBRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}
				else
				{
					if (EquippedShotBName != "UnKnwon")
					{
						EquippedShotBName = "UnKnwon";
						FrontBRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontBRenderer->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
						FrontBRenderer->ChangeFrameAnimation("UnKnown");
						FrontBRenderer->SetScaleModeImage();
						FrontBRenderer->GetTransform().SetLocalPosition({ -98.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontBRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}

				if (nullptr != EquippedItemSuper)
				{
					if (EquippedSuperName != EquippedItemSuper->ItemName + "Equip")
					{
						EquippedSuperName = EquippedItemSuper->ItemName + "Equip";
						FrontCRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontCRenderer->CreateFrameAnimationFolder(EquippedSuperName, FrameAnimation_DESC(EquippedSuperName, 0.05f, true));
						FrontCRenderer->ChangeFrameAnimation(EquippedSuperName);
						FrontCRenderer->SetScaleModeImage();
						FrontCRenderer->GetTransform().SetLocalPosition({ 0.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontCRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}
				else
				{
					if (EquippedSuperName != "UnKnwon")
					{
						EquippedSuperName = "UnKnwon";
						FrontCRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontCRenderer->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
						FrontCRenderer->ChangeFrameAnimation("UnKnown");
						FrontCRenderer->SetScaleModeImage();
						FrontCRenderer->GetTransform().SetLocalPosition({ 0.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontCRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}

				if (nullptr != EquippedItemCharm)
				{
					if (EquippedCharmName != EquippedItemCharm->ItemName + "Equip")
					{
						FrontDRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontDRenderer->CreateFrameAnimationFolder(EquippedCharmName, FrameAnimation_DESC(EquippedCharmName, 0.05f, true));
						FrontDRenderer->ChangeFrameAnimation(EquippedCharmName);
						FrontDRenderer->SetScaleModeImage();
						FrontDRenderer->GetTransform().SetLocalPosition({ 100.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontDRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}
				else
				{
					if (EquippedCharmName != "UnKnwon")
					{
						EquippedCharmName = "UnKnwon";
						FrontDRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontDRenderer->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.1f, false));
						FrontDRenderer->ChangeFrameAnimation("UnKnown");
						FrontDRenderer->SetScaleModeImage();
						FrontDRenderer->GetTransform().SetLocalPosition({ 100.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontDRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
					}
				}
			}
		}

		if (GameEngineInput::GetInst()->IsDown("MoveRight"))
		{
			if (CurPos < 4)
			{
				CurPos += 1;
				Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
			}
			else
			{
				CurPos = 3;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("MoveLeft"))
		{
			if (CurPos > 0)
			{
				CurPos -= 1;
				Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
			}
			else
			{
				CurPos = 0;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (Selector->GetTransform().GetLocalPosition().x == SelectorPosFront[0].x)
			{
				SetPhase(InventoryPhase::ShotASlot);
			}
			else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosFront[1].x)
			{
				SetPhase(InventoryPhase::ShotBSlot);
			}
			else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosFront[2].x)
			{
				SetPhase(InventoryPhase::SuperSlot);
			}
			else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosFront[3].x)
			{
				SetPhase(InventoryPhase::CharmSlot);
			}
			else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosFront[4].x)
			{
				SetPhase(InventoryPhase::ListSlot);
			}
			else
			{
				return;
			}
		}
	}
	if (GetPhase() == InventoryPhase::ShotASlot)
	{
		if (BeforePhase != GetPhase())
		{
			BeforePhase = Phase;
			FrontARenderer->Off();
			FrontBRenderer->Off();
			FrontCRenderer->Off();
			FrontDRenderer->Off();
			CurPos = 0;
			Selector->GetTransform().SetLocalPosition(SelectorPosA[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			if (ShotASlot == nullptr)
			{
				ShotASlot = CreateComponent<GameEngineTextureRenderer>();
				ShotASlot->SetTexture("generic_equip_back_9_icons.png");
				ShotASlot->ScaleToTexture();
				ShotASlot->GetTransform().SetLocalPosition({ 0.0f, -0.0f,(int)ZOrder::UI });
				ShotASlot->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
			else
			{
				ShotASlot->On();
			}
		}

		if (GameEngineInput::GetInst()->IsDown("ESC"))
		{
			ShotASlot->Off();
			SetPhase(InventoryPhase::Front);
		}

	}

	if (GetLevel()->GetNameCopy() != "WORLDMAP")
	{
		Off();
	}
	else
	{
		On();
	}

	//std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
	//for (GameEngineActor* Actor : Actors)
	//{
	//	if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
	//	{
	//		for (ItemBase* Item : _State->Items[ItemType::Charm])
	//		{
	//			GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
	//			ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
	//			ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
	//			ItemIconRenderer->SetScaleModeImage();
	//			ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
	//			ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	//		}

	//		for (ItemBase* Item : _State->Items[ItemType::Shoot])
	//		{
	//			GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
	//			ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
	//			ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
	//			ItemIconRenderer->SetScaleModeImage();
	//			ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
	//			ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	//		}

	//		for (ItemBase* Item : _State->Items[ItemType::Super])
	//		{
	//			GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
	//			ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
	//			ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
	//			ItemIconRenderer->SetScaleModeImage();
	//			ItemIconRenderer->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::UI - 5 });
	//			ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	//		}
	//	}

	//}
}

void ItemInventory::End()
{
}