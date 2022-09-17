#include "PreCompile.h"
#include "ItemInventory.h"
#include "CharacterState.h"
#include "ItemBase.h"
#include "PeaShooterItem.h"
#include "PeaShooterItem.h"

ItemInventory::ItemInventory()
	: Phase(InventoryPhase::Front)
	, CurPos(0)
	, BeforePhase(InventoryPhase::None)
	, ShotABackRenderer(nullptr)
	, MinPos(0)
	, SelectInvervalTime(0.2)
	, ItemName(8)
	, AslotSelectedNum(-1)
	, BslotSelectedNum(-1)
	, Selector(nullptr)
	, EIcon(nullptr)
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

	SelectorPos3Slot.push_back(float4{ -100.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPos3Slot.push_back(float4{ 0.0f, 90.0f, (int)ZOrder::UI - 5 });
	SelectorPos3Slot.push_back(float4{ 100.0f, 90.0f, (int)ZOrder::UI - 5 });

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

	{
		GameEngineTextureRenderer* ItemIconRenderer0 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer1 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer3 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer4 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer5 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer6 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer7 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer8 = CreateComponent<GameEngineTextureRenderer>();

		ItemIconRenderers.insert(std::make_pair(0, ItemIconRenderer0));
		ItemIconRenderers.insert(std::make_pair(1, ItemIconRenderer1));
		ItemIconRenderers.insert(std::make_pair(2, ItemIconRenderer2));
		ItemIconRenderers.insert(std::make_pair(3, ItemIconRenderer3));
		ItemIconRenderers.insert(std::make_pair(4, ItemIconRenderer4));
		ItemIconRenderers.insert(std::make_pair(5, ItemIconRenderer5));
		ItemIconRenderers.insert(std::make_pair(6, ItemIconRenderer6));
		ItemIconRenderers.insert(std::make_pair(7, ItemIconRenderer7));
		ItemIconRenderers.insert(std::make_pair(8, ItemIconRenderer8));

		for (int i = 0; i < ItemIconRenderers.size(); i++)
		{
			ItemIconRenderers[i]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("BoomerangShooterEquip", FrameAnimation_DESC("BoomerangShooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("BoomerangShooterOk", FrameAnimation_DESC("BoomerangShooterOk", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterEquip", FrameAnimation_DESC("ConvergeShooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterOk", FrameAnimation_DESC("ConvergeShooterOk", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("PeaShooterEquip", FrameAnimation_DESC("PeashooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("PeaShooterOk", FrameAnimation_DESC("PeashooterOk", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("SpreadShooterEquip", FrameAnimation_DESC("SpreadShooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("SpreadShooterOk", FrameAnimation_DESC("SpreadShooterOk", 0.05f, true));
			ItemIconRenderers[i]->ChangeFrameAnimation("UnKnown");
			ItemIconRenderers[i]->SetScaleModeImage();
			ItemIconRenderers[i]->GetTransform().SetLocalPosition(SelectorPosBack[i]);
			ItemIconRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
			ItemIconRenderers[i]->Off();
		}
	}

	{
		GameEngineTextureRenderer* ItemIconRenderer0 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer1 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer3 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer4 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer5 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer6 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer7 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer8 = CreateComponent<GameEngineTextureRenderer>();

		ItemIconBRenderers.insert(std::make_pair(0, ItemIconRenderer0));
		ItemIconBRenderers.insert(std::make_pair(1, ItemIconRenderer1));
		ItemIconBRenderers.insert(std::make_pair(2, ItemIconRenderer2));
		ItemIconBRenderers.insert(std::make_pair(3, ItemIconRenderer3));
		ItemIconBRenderers.insert(std::make_pair(4, ItemIconRenderer4));
		ItemIconBRenderers.insert(std::make_pair(5, ItemIconRenderer5));
		ItemIconBRenderers.insert(std::make_pair(6, ItemIconRenderer6));
		ItemIconBRenderers.insert(std::make_pair(7, ItemIconRenderer7));
		ItemIconBRenderers.insert(std::make_pair(8, ItemIconRenderer8));

		for (int i = 0; i < ItemIconBRenderers.size(); i++)
		{
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("BoomerangShooterEquip", FrameAnimation_DESC("BoomerangShooterEquip", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("BoomerangShooterOk", FrameAnimation_DESC("BoomerangShooterOk", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterEquip", FrameAnimation_DESC("ConvergeShooterEquip", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterOk", FrameAnimation_DESC("ConvergeShooterOk", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("PeaShooterEquip", FrameAnimation_DESC("PeashooterEquip", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("PeaShooterOk", FrameAnimation_DESC("PeashooterOk", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("SpreadShooterEquip", FrameAnimation_DESC("SpreadShooterEquip", 0.05f, true));
			ItemIconBRenderers[i]->CreateFrameAnimationFolder("SpreadShooterOk", FrameAnimation_DESC("SpreadShooterOk", 0.05f, true));
			ItemIconBRenderers[i]->ChangeFrameAnimation("UnKnown");
			ItemIconBRenderers[i]->SetScaleModeImage();
			ItemIconBRenderers[i]->GetTransform().SetLocalPosition(SelectorPosBack[i]);
			ItemIconBRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
			ItemIconBRenderers[i]->Off();
		}
	}

	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);
	ItemName.push_back(nullptr);


	EIcon = CreateComponent<GameEngineTextureRenderer>();
	EIcon->CreateFrameAnimationFolder("EquipE", FrameAnimation_DESC("EquipE", 0.05, true));
	EIcon->ChangeFrameAnimation("EquipE");
	EIcon->SetScaleModeImage();
	EIcon->ChangeCamera(CAMERAORDER::UICAMERA2);
	EIcon->Off();

	GameEngineTextureRenderer* FrontARenderer = CreateComponent<GameEngineTextureRenderer>();
	FrontRenderers.insert(std::make_pair(0, FrontARenderer));

	GameEngineTextureRenderer* FrontBRenderer = CreateComponent<GameEngineTextureRenderer>();
	FrontRenderers.insert(std::make_pair(1, FrontBRenderer));

	GameEngineTextureRenderer* FrontCRenderer = CreateComponent<GameEngineTextureRenderer>();
	FrontRenderers.insert(std::make_pair(2, FrontCRenderer));

	GameEngineTextureRenderer* FrontDRenderer = CreateComponent<GameEngineTextureRenderer>();
	FrontRenderers.insert(std::make_pair(3, FrontDRenderer));

	for (int i = 0; i < 2; i++)
	{
		FrontRenderers[i]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
		FrontRenderers[i]->CreateFrameAnimationFolder("BoomerangShooterEquip", FrameAnimation_DESC("BoomerangShooterEquip", 0.05f, true));
		FrontRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterEquip", FrameAnimation_DESC("ConvergeShooterEquip", 0.05f, true));
		FrontRenderers[i]->CreateFrameAnimationFolder("PeaShooterEquip", FrameAnimation_DESC("PeashooterEquip", 0.05f, true));
		FrontRenderers[i]->CreateFrameAnimationFolder("SpreadShooterEquip", FrameAnimation_DESC("SpreadShooterEquip", 0.05f, true));
		FrontRenderers[i]->SetScaleModeImage();
		FrontRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
	}

	FrontRenderers[2]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
	FrontRenderers[2]->CreateFrameAnimationFolder("SuperBeamEquip", FrameAnimation_DESC("SuperBeamEquip", 0.05f, true));
	FrontRenderers[2]->CreateFrameAnimationFolder("SuperGhostEquip", FrameAnimation_DESC("SuperGhostEquip", 0.05f, true));
	FrontRenderers[2]->CreateFrameAnimationFolder("SuperInvincibleEquip", FrameAnimation_DESC("SuperInvincibleEquip", 0.05f, true));
	FrontRenderers[2]->SetScaleModeImage();
	FrontRenderers[2]->ChangeCamera(CAMERAORDER::UICAMERA2);

	FrontRenderers[3]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
	FrontRenderers[3]->CreateFrameAnimationFolder("AstalCookieEquip", FrameAnimation_DESC("AstalCookieEquip", 0.05f, true));
	FrontRenderers[3]->CreateFrameAnimationFolder("CursedRelicEquip", FrameAnimation_DESC("CursedRelicEquip", 0.05f, true));
	FrontRenderers[3]->CreateFrameAnimationFolder("TwinHeartEquip", FrameAnimation_DESC("TwinHeartEquip", 0.05f, true));
	FrontRenderers[3]->CreateFrameAnimationFolder("SmokeBombEquip", FrameAnimation_DESC("SmokeBombEquip", 0.05f, true));
	FrontRenderers[3]->SetScaleModeImage();
	FrontRenderers[3]->ChangeCamera(CAMERAORDER::UICAMERA2);

	ShotABackRenderer = CreateComponent<GameEngineTextureRenderer>();
	ShotABackRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	ShotABackRenderer->GetTransform().SetLocalPosition({ 0.0f, -10.0f,(int)ZOrder::UI });
	ShotABackRenderer->Off();

	{
		GameEngineTextureRenderer* ItemIconRenderer0 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer1 = CreateComponent<GameEngineTextureRenderer>();
		GameEngineTextureRenderer* ItemIconRenderer2 = CreateComponent<GameEngineTextureRenderer>();

		SuperIconRenderers.insert(std::make_pair(0, ItemIconRenderer0));
		SuperIconRenderers.insert(std::make_pair(1, ItemIconRenderer1));
		SuperIconRenderers.insert(std::make_pair(2, ItemIconRenderer2));

		for (int i = 0; i < SuperIconRenderers.size(); i++)
		{
			SuperIconRenderers[i]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
			SuperIconRenderers[i]->CreateFrameAnimationFolder("SuperBeamEquip", FrameAnimation_DESC("SuperBeamEquip", 0.05f, true));
			SuperIconRenderers[i]->CreateFrameAnimationFolder("SuperGhostEquip", FrameAnimation_DESC("SuperGhostEquip", 0.05f, true));
			SuperIconRenderers[i]->CreateFrameAnimationFolder("SuperInvincibleEquip", FrameAnimation_DESC("SuperInvincibleEquip", 0.05f, true));
			SuperIconRenderers[i]->ChangeFrameAnimation("UnKnown");
			SuperIconRenderers[i]->GetTransform().SetLocalPosition(SelectorPos3Slot[i]);
			SuperIconRenderers[i]->SetScaleModeImage();
			SuperIconRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
			SuperIconRenderers[i]->Off();
		}
	}

	{
		{
			GameEngineTextureRenderer* ItemIconRenderer0 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer1 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer2 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer3 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer4 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer5 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer6 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer7 = CreateComponent<GameEngineTextureRenderer>();
			GameEngineTextureRenderer* ItemIconRenderer8 = CreateComponent<GameEngineTextureRenderer>();

			CharmIconRenderers.insert(std::make_pair(0, ItemIconRenderer0));
			CharmIconRenderers.insert(std::make_pair(1, ItemIconRenderer1));
			CharmIconRenderers.insert(std::make_pair(2, ItemIconRenderer2));
			CharmIconRenderers.insert(std::make_pair(3, ItemIconRenderer3));
			CharmIconRenderers.insert(std::make_pair(4, ItemIconRenderer4));
			CharmIconRenderers.insert(std::make_pair(5, ItemIconRenderer5));
			CharmIconRenderers.insert(std::make_pair(6, ItemIconRenderer6));
			CharmIconRenderers.insert(std::make_pair(7, ItemIconRenderer7));
			CharmIconRenderers.insert(std::make_pair(8, ItemIconRenderer8));

			for (int i = 0; i < CharmIconRenderers.size(); i++)
			{
				CharmIconRenderers[i]->CreateFrameAnimationFolder("UnKnown", FrameAnimation_DESC("UnKnown", 0.05f, true));
				CharmIconRenderers[i]->CreateFrameAnimationFolder("AstalCookieEquip", FrameAnimation_DESC("AstalCookieEquip", 0.05f, true));
				CharmIconRenderers[i]->CreateFrameAnimationFolder("CursedRelicEquip", FrameAnimation_DESC("CursedRelicEquip", 0.05f, true));
				CharmIconRenderers[i]->CreateFrameAnimationFolder("SmokeBombEquip", FrameAnimation_DESC("SmokeBombEquip", 0.05f, true));
				CharmIconRenderers[i]->CreateFrameAnimationFolder("TwinHeartEquip", FrameAnimation_DESC("TwinHeartEquip", 0.05f, true));
				CharmIconRenderers[i]->ChangeFrameAnimation("UnKnown");
				CharmIconRenderers[i]->SetScaleModeImage();
				CharmIconRenderers[i]->GetTransform().SetLocalPosition(SelectorPosBack[i]);
				CharmIconRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
				CharmIconRenderers[i]->Off();
			}
		}
	}
}

void ItemInventory::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;

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
		ShotABackRenderer->Off();

		if (BeforePhase != GetPhase())
		{
			BeforePhase = Phase;

			for (int i = 0; i < FrontRenderers.size(); i++)
			{
				if (FrontRenderers[i] != nullptr)
				{
					FrontRenderers[i]->On();
				}
			}

			if (InventoryFront != nullptr)
			{
				InventoryFront->SetTexture("ch_equip_front.png");
				InventoryFront->On();
			}

			CurPos = 0;
			MaxPos = 4;

			std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
			for (GameEngineActor* Actor : Actors)
			{
				if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
				{
					std::shared_ptr<ItemBase> EquippedItemShotA = _State->EquippedItems[InventoryType::ShotA];
					std::shared_ptr<ItemBase> EquippedItemShotB = _State->EquippedItems[InventoryType::ShotB];
					std::shared_ptr<ItemBase> EquippedItemSuper = _State->EquippedItems[InventoryType::Super];
					std::shared_ptr<ItemBase> EquippedItemCharm = _State->EquippedItems[InventoryType::Charm];

					if (nullptr != EquippedItemShotA)
					{
						if (EquippedShotAName != EquippedItemShotA->ItemName + "Equip")
						{
							EquippedShotAName = EquippedItemShotA->ItemName + "Equip";
							FrontRenderers[0]->ChangeFrameAnimation(EquippedShotAName);
							FrontRenderers[0]->GetTransform().SetLocalPosition({ -198.0f,-165.0f, (int)ZOrder::UI - 5 });
						}
					}
					else
					{
						EquippedShotAName = "UnKnown";
						FrontRenderers[0]->ChangeFrameAnimation(EquippedShotAName);
						FrontRenderers[0]->GetTransform().SetLocalPosition({ -198.0f,-165.0f, (int)ZOrder::UI - 5 });
					}

					if (nullptr != EquippedItemShotB)
					{
						if (EquippedShotBName != EquippedItemShotB->ItemName + "Equip")
						{
							EquippedShotBName = EquippedItemShotB->ItemName + "Equip";
							FrontRenderers[1]->ChangeFrameAnimation(EquippedShotBName);
							FrontRenderers[1]->GetTransform().SetLocalPosition({ -98.0f,-165.0f, (int)ZOrder::UI - 5 });
						}
					}
					else
					{
						EquippedShotBName = "UnKnown";
						FrontRenderers[1]->ChangeFrameAnimation(EquippedShotBName);
						FrontRenderers[1]->GetTransform().SetLocalPosition({ -98.0f,-165.0f, (int)ZOrder::UI - 5 });
					}

					if (nullptr != EquippedItemSuper)
					{
						if (EquippedSuperName != EquippedItemSuper->ItemName + "Equip")
						{
							EquippedSuperName = EquippedItemSuper->ItemName + "Equip";
							FrontRenderers[2]->ChangeFrameAnimation(EquippedSuperName);
							FrontRenderers[2]->GetTransform().SetLocalPosition({ 0.0f,-165.0f, (int)ZOrder::UI - 5 });
						}
					}
					else
					{
						EquippedSuperName = "UnKnown";
						FrontRenderers[2]->ChangeFrameAnimation(EquippedSuperName);
						FrontRenderers[2]->GetTransform().SetLocalPosition({ 0.0f,-165.0f, (int)ZOrder::UI - 5 });
					}

					if (nullptr != EquippedItemCharm)
					{
						if (EquippedCharmName != EquippedItemCharm->ItemName + "Equip")
						{
							EquippedCharmName = EquippedItemCharm->ItemName + "Equip";
							FrontRenderers[3]->ChangeFrameAnimation(EquippedCharmName);
							FrontRenderers[3]->GetTransform().SetLocalPosition({ 100.0f,-165.0f, (int)ZOrder::UI - 5 });
						}
					}
					else
					{
						EquippedCharmName = "UnKnown";
						FrontRenderers[3]->ChangeFrameAnimation(EquippedCharmName);
						FrontRenderers[3]->GetTransform().SetLocalPosition({ 100.0f,-165.0f, (int)ZOrder::UI - 5 });
					}
				}
			}
		}

		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
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
				ElapsedTime = 0.0f;

			}
		}
	}
	if (GetPhase() == InventoryPhase::ShotASlot)
	{
		if (BeforePhase != GetPhase())
		{
			for (int i = 0; i < FrontRenderers.size(); i++)
			{
				if (FrontRenderers[i] != nullptr)
				{
					FrontRenderers[i]->Off();
				}
			}
			BeforePhase = Phase;
			CurPos = 0;
			MaxPos = 8;
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			ShotABackRenderer->SetTexture("generic_equip_back_9_icons.png");
			ShotABackRenderer->ScaleToTexture();
			ShotABackRenderer->On();
		}

		for (int i = 0; i < ItemIconRenderers.size(); i++)
		{
			ItemIconRenderers[i]->On();
		}

		std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
			{
				std::vector<std::shared_ptr<ItemBase>> ShotAItems = _State->Items[ItemType::Shoot];

				int i = 0;
				for (std::shared_ptr<ItemBase> Item : ShotAItems)
				{
					if (BslotSelectedNum != i)
					{
						ItemIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
						ItemIconRenderers[i]->GetTransform().SetLocalPosition( SelectorPosBack[i]);
						ItemName[i] = Item;
					}
					else if (BslotSelectedNum == i && BslotSelectedNum != -1)
					{
						ItemIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Ok");
						ItemIconRenderers[i]->GetTransform().SetLocalPosition(SelectorPosBack[i]);
					}
					if (AslotSelectedNum == i)
					{
						EIcon->GetTransform().SetLocalPosition(SelectorPosBack[i]);
						EIcon->SetPivot(PIVOTMODE::LEFTBOT);
						EIcon->On();
					}
					if (AslotSelectedNum == -1)
					{
						EIcon->GetTransform().SetLocalPosition(SelectorPosBack[0]);
						EIcon->SetPivot(PIVOTMODE::LEFTBOT);
						EIcon->On();
					}
					i++;
				}

			}
		}
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
			{
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[0].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[0];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[0]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 0;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[1].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[1];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[1]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 1;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[2].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[2];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[2]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 2;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[3].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[3];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[3]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 3;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[4].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[4];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[4]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 4;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[5].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[5];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[5]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 5;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[6].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[6];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[6]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 6;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[7].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[7];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[7]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 7;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[8].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[8];
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[8]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 8;
						}
					}
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
			}
		}
	}
	else if (GetPhase() == InventoryPhase::ShotBSlot)
	{
		if (BeforePhase != GetPhase())
		{
			for (int i = 0; i < FrontRenderers.size(); i++)
			{
				if (FrontRenderers[i] != nullptr)
				{
					FrontRenderers[i]->Off();
				}
			}
			BeforePhase = Phase;
			CurPos = 0;
			MaxPos = 8;

			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			ShotABackRenderer->SetTexture("generic_equip_back_9_icons.png");
			ShotABackRenderer->ScaleToTexture();
			ShotABackRenderer->On();

			for (int i = 0; i < ItemIconBRenderers.size(); i++)
			{
				ItemIconBRenderers[i]->On();
			}


			std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
			for (GameEngineActor* Actor : Actors)
			{
				if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
				{
					std::vector<std::shared_ptr<ItemBase>> ShotAItems = _State->Items[ItemType::Shoot];

					int i = 0;
					for (std::shared_ptr<ItemBase> Item : ShotAItems)
					{
						if (i < ShotAItems.size())
						{
							if (AslotSelectedNum != i)
							{
								ItemIconBRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
								ItemName[i] = Item;
							}
							else if (AslotSelectedNum == i && AslotSelectedNum != -1)
							{
								ItemIconBRenderers[AslotSelectedNum]->ChangeFrameAnimation(Item->ItemName + "Ok");
							}
							if (BslotSelectedNum == i)
							{
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[1]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
							}
							i++;
						}
						if (AslotSelectedNum == -1)
						{
							ItemIconBRenderers[0]->ChangeFrameAnimation(Item->ItemName + "Ok");
						}
					}

				}
			}
		}
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
			{
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[0].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[0])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[0];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[0]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 0;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[1].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[1])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[1];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[1]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 1;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[2].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[2])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[2];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[2]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 2;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[3].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[3])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[3];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[3]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 3;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[4].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[4])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[4];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[4]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 4;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[5].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[5])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[5];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[5]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 5;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[6].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[6])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[6];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[6]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 6;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[7].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[7])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[7];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[7]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 7;
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[8].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (_State->EquippedItems[InventoryType::ShotA] != ItemName[8])
							{
								_State->EquippedItems[InventoryType::ShotB] = ItemName[8];
								EIcon->GetTransform().SetLocalPosition(SelectorPosBack[8]);
								EIcon->SetPivot(PIVOTMODE::LEFTBOT);
								EIcon->On();
								BslotSelectedNum = 8;
							}
						}
					}
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
			}
		}
	}
	else if (GetPhase() == InventoryPhase::SuperSlot)
	{
		if (BeforePhase != GetPhase())
		{
			for (int i = 0; i < FrontRenderers.size(); i++)
			{
				if (FrontRenderers[i] != nullptr)
				{
					FrontRenderers[i]->Off();
				}
			}
			BeforePhase = Phase;
			CurPos = 0;
			MaxPos = 8;

			Selector->GetTransform().SetLocalPosition(SelectorPos3Slot[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");

			ShotABackRenderer->SetTexture("generic_equip_back_super_icons.png");
			ShotABackRenderer->ScaleToTexture();
			ShotABackRenderer->On();

			for (int i = 0; i < SuperIconRenderers.size(); i++)
			{
				SuperIconRenderers[i]->On();
			}

			std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
			for (GameEngineActor* Actor : Actors)
			{
				if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
				{
					std::vector<std::shared_ptr<ItemBase>> SuperItems = _State->Items[ItemType::Super];

					int i = 0;
					for (std::shared_ptr<ItemBase> Item : SuperItems)
					{
						if (i < SuperItems.size())
						{
							SuperIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
							ItemName[i] = Item;
							i++;
						}
					}

				}
			}
		}
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
			{
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPos3Slot[0].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::Super] = ItemName[0];
							EIcon->GetTransform().SetLocalPosition(SelectorPos3Slot[0]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 0;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPos3Slot[1].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::Super] = ItemName[1];
							EIcon->GetTransform().SetLocalPosition(SelectorPos3Slot[1]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 0;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPos3Slot[2].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::Super] = ItemName[2];
							EIcon->GetTransform().SetLocalPosition(SelectorPos3Slot[2]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 0;
						}
					}
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
			}
		}
	}
	else if (GetPhase() == InventoryPhase::CharmSlot)
	{
		if (BeforePhase != GetPhase())
		{
			for (int i = 0; i < FrontRenderers.size(); i++)
			{
				if (FrontRenderers[i] != nullptr)
				{
					FrontRenderers[i]->Off();
				}
			}
			BeforePhase = Phase;
			CurPos = 0;
			MaxPos = 8;
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			ShotABackRenderer->SetTexture("generic_equip_back_9_icons.png");
			ShotABackRenderer->ScaleToTexture();
			ShotABackRenderer->On();
		}

		for (int i = 0; i < CharmIconRenderers.size(); i++)
		{
			CharmIconRenderers[i]->On();
		}

		std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
			{
				std::vector<std::shared_ptr<ItemBase>> CharmItems = _State->Items[ItemType::Charm];

				int i = 0;
				for (std::shared_ptr<ItemBase> Item : CharmItems)
				{
					CharmIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
					ItemName[i] = Item;
					i++;
				}
			}
		}
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
			{
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[0].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[0]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[0]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[1].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[1]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[1]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 1;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[2].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[2]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[2]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 2;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[3].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[3]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[3]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 3;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[4].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[4]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[4]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 4;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[5].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[5]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[5]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 5;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[6].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[6]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[6]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 6;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[7].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[7]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[7]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 7;
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[8].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->SetEquippedItem(InventoryType::Charm, ItemName[8]);
							EIcon->GetTransform().SetLocalPosition(SelectorPosBack[8]);
							EIcon->SetPivot(PIVOTMODE::LEFTBOT);
							EIcon->On();
							AslotSelectedNum = 8;
						}
					}
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
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
				ShotABackRenderer->Off();
				for (int i = 0; i < ItemIconRenderers.size(); i++)
				{
					ItemIconRenderers[i]->Off();
				}
				EIcon->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::ShotBSlot:
			{
				ShotABackRenderer->Off();
				for (int i = 0; i < ItemIconBRenderers.size(); i++)
				{
					ItemIconBRenderers[i]->Off();
				}
				EIcon->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::SuperSlot:
			{
				ShotABackRenderer->Off();
				for (int i = 0; i < SuperIconRenderers.size(); i++)
				{
					SuperIconRenderers[i]->Off();
				}
				EIcon->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::CharmSlot:
			{
				ShotABackRenderer->Off();
				for (int i = 0; i < CharmIconRenderers.size(); i++)
				{
					CharmIconRenderers[i]->Off();
				}
				EIcon->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			}
		}
		else if (GameEngineInput::GetInst()->IsDown("MoveDown"))
		{
			if (GetPhase() == InventoryPhase::ShotASlot ||
				GetPhase() == InventoryPhase::ShotBSlot ||
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
				GetPhase() == InventoryPhase::CharmSlot)
			{
				CurPos -= 5;
				if (CurPos <= MinPos)
				{
					CurPos = MinPos;
				}
			}
		}

		if (GetPhase() == InventoryPhase::Front)
		{
			MaxPos = 4;
			if (CurPos >= 4)
			{
				CurPos = 4;
			}
			Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
		}

		else if (GetPhase() == InventoryPhase::SuperSlot)
		{
			MaxPos = 2;
			if (CurPos >= 2)
			{
				CurPos = 2;
			}
			Selector->GetTransform().SetLocalPosition(SelectorPos3Slot[CurPos]);
		}

		else if (GetPhase() == InventoryPhase::ShotASlot ||
			GetPhase() == InventoryPhase::ShotBSlot ||
			GetPhase() == InventoryPhase::CharmSlot)
		{
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
		}
	}
}


void ItemInventory::End()
{
}