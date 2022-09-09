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
	, MinPos(0)
{
}

ItemInventory::~ItemInventory()
{
}

void ItemInventory::Start()
{
	SelectorPosFront.push_back(float4{ -200.0f,-165.0f, (int)ZOrder::UI - 5 });
	SelectorPosFront.push_back(float4{ -100.0f,-165.0f, (int)ZOrder::UI - 5 });
	SelectorPosFront.push_back(float4{ -2.0f,-165.0f , (int)ZOrder::UI - 5 });
	SelectorPosFront.push_back(float4{ 98.0f,-165.0f, (int)ZOrder::UI - 5 });
	SelectorPosFront.push_back(float4{ 198.0f,-165.0f, (int)ZOrder::UI - 5 });

	SelectorPosBack.push_back(float4{ -200.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ -100.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ 0.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ 100.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ 190.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ -150.0f, 0.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ -51.0f, 0.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ 47.0f, 0.0f, (int)ZOrder::UI - 5 });
	SelectorPosBack.push_back(float4{ 147.0f, 0.0f , (int)ZOrder::UI - 5 });

	SlotItemName.push_back("PeaShooter");
	SlotItemName.push_back("UnKnown");
	SlotItemName.push_back("UnKnown");
	SlotItemName.push_back("UnKnown");
	SlotItemName.push_back("UnKnown");
	SlotItemName.push_back("BoomerangShooter");
	SlotItemName.push_back("UnKnown");
	SlotItemName.push_back("ConvergeShooter");
	SlotItemName.push_back("UnKnown");



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
	if (GetLevel()->GetNameCopy() != "WORLDMAP")
	{
		Off();
		return;
	}
	else
	{
		On();
	}

	if (GetPhase() == InventoryPhase::Front)
	{
		if (BeforePhase != GetPhase())
		{
			if (BeforePhase == InventoryPhase::ShotASlot)
			{

			}
			else if (BeforePhase == InventoryPhase::ShotBSlot)
			{

			}
			else if (BeforePhase == InventoryPhase::SuperSlot)
			{

			}
			else if (BeforePhase == InventoryPhase::CharmSlot)
			{

			}

			BeforePhase = Phase;
			if (FrontARenderer != nullptr)
			{
				FrontARenderer->On();
				FrontBRenderer->On();
				FrontCRenderer->On();
				FrontDRenderer->On();
				InventoryFront->SetTexture("ch_equip_front.png");
				InventoryFront->On();
				CurPos = 0;
				MaxPos = 4;
			}

			Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
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
						if (EquippedShotAName != "UnKnown")
						{
							EquippedShotAName = "UnKnown";
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
						if (EquippedShotBName != "UnKnown")
						{
							EquippedShotBName = "UnKnown";
							FrontBRenderer = CreateComponent<GameEngineTextureRenderer>();
							FrontBRenderer->CreateFrameAnimationFolder(EquippedShotBName, FrameAnimation_DESC(EquippedShotBName, 0.05f, true));
							FrontBRenderer->ChangeFrameAnimation(EquippedShotBName);
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
						if (EquippedSuperName != "UnKnown")
						{
							EquippedSuperName = "UnKnown";
							FrontCRenderer = CreateComponent<GameEngineTextureRenderer>();
							FrontCRenderer->CreateFrameAnimationFolder(EquippedSuperName, FrameAnimation_DESC(EquippedSuperName, 0.05f, true));
							FrontCRenderer->ChangeFrameAnimation(EquippedSuperName);
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
						if (EquippedCharmName != "UnKnown")
						{
							EquippedCharmName = "UnKnown";
							FrontDRenderer = CreateComponent<GameEngineTextureRenderer>();
							FrontDRenderer->CreateFrameAnimationFolder(EquippedCharmName, FrameAnimation_DESC(EquippedCharmName, 0.1f, false));
							FrontDRenderer->ChangeFrameAnimation(EquippedCharmName);
							FrontDRenderer->SetScaleModeImage();
							FrontDRenderer->GetTransform().SetLocalPosition({ 100.0f,-165.0f, (int)ZOrder::UI - 5 });
							FrontDRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
						}
					}
				}
			}
		}

		if (GameEngineInput::GetInst()->IsDown("Select"))
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
			if (BeforePhase == InventoryPhase::Front)
			{
				FrontARenderer->Off();
				FrontBRenderer->Off();
				FrontCRenderer->Off();
				FrontDRenderer->Off();

				BeforePhase = Phase;
				CurPos = 0;
				MaxPos = 8;
			}
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			if (ShotASlot == nullptr)
			{
				ShotASlot = CreateComponent<GameEngineTextureRenderer>();
				ShotASlot->SetTexture("generic_equip_back_9_icons.png");
				ShotASlot->ScaleToTexture();
				ShotASlot->GetTransform().SetLocalPosition({ 0.0f, -10.0f,(int)ZOrder::UI });
				ShotASlot->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
			else
			{
				ShotASlot->On();
			}

			std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
			for (GameEngineActor* Actor : Actors)
			{
				if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
				{
					for (ItemBase* Item : _State->Items[ItemType::Shoot])
					{
						for (int i = 0; i <= MaxPos; i++)
						{
							GameEngineTextureRenderer* ItemIconRenderer = CreateComponent<GameEngineTextureRenderer>();
							ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Equip", FrameAnimation_DESC(Item->ItemName + "Equip", 0.1f, false));
							ItemIconRenderer->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.1f, false));
							ItemIconRenderer->SetScaleModeImage();
							ItemIconRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);

							if (Item->ItemName == SlotItemName[i])
							{
								ItemIconRenderer->ChangeFrameAnimation(Item->ItemName + "Equip");
								ItemIconRenderer->GetTransform().SetLocalPosition(SelectorPosBack[i]);
							}
						}
					}
				}
			}
		}
	}

	{
		// Selector ÀÌµ¿
		if (GameEngineInput::GetInst()->IsDown("MoveRight"))
		{
			if (CurPos < MaxPos)
			{
				CurPos += 1;
			}
			else
			{
				CurPos = MaxPos;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("MoveLeft"))
		{
			if (CurPos > MinPos)
			{
				CurPos -= 1;
			}
			else
			{
				CurPos = MinPos;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("ESC"))
		{
			switch (Phase)
			{
			case InventoryPhase::Front:
			{
				Off();
			}
			break;
			case InventoryPhase::ShotASlot:
			{
				ShotASlot->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::ShotBSlot:
			{
				ShotBSlot->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::SuperSlot:
			{
				ShotCSlot->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::CharmSlot:
			{
				ShotDSlot->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("MoveDown"))
		{
			if (GetPhase() == InventoryPhase::ShotASlot ||
				GetPhase() == InventoryPhase::ShotBSlot ||
				GetPhase() == InventoryPhase::SuperSlot ||
				GetPhase() == InventoryPhase::CharmSlot)
			{
				CurPos += 5;
				if (CurPos > MaxPos)
				{
					CurPos = MaxPos;
				}
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("MoveUp"))
		{
			if (GetPhase() == InventoryPhase::ShotASlot ||
				GetPhase() == InventoryPhase::ShotBSlot ||
				GetPhase() == InventoryPhase::SuperSlot ||
				GetPhase() == InventoryPhase::CharmSlot)
			{
				CurPos -= 5;
				if (CurPos <= MinPos)
				{
					CurPos = MinPos;
				}
			}
		}
		if (GetPhase() == InventoryPhase::ShotASlot ||
			GetPhase() == InventoryPhase::ShotBSlot ||
			GetPhase() == InventoryPhase::SuperSlot ||
			GetPhase() == InventoryPhase::CharmSlot)
		{
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
		}
	}

}

void ItemInventory::End()
{
}