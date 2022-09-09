#include "PreCompile.h"
#include "ItemInventory.h"
#include "CharacterState.h"
#include "ItemBase.h"
#include "PeaShooterItem.h"
#include "PeaShooterItem.h"

ItemInventory::ItemInventory()
	:OnceCheck(false)
	, Phase(InventoryPhase::Front)
	, CurPos(0)
	, BeforePhase(InventoryPhase::None)
	, ShotABackRenderer(nullptr)
	, FrontARenderer(nullptr)
	, FrontBRenderer(nullptr)
	, FrontCRenderer(nullptr)
	, FrontDRenderer(nullptr)
	, FrontSlotC(nullptr)
	, FrontSlotD(nullptr)
	, MinPos(0)
	, SelectInvervalTime(0.2)
	, ItemName(8)
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
			ItemIconRenderers[i]->CreateFrameAnimationFolder("ConvergeShooterEquip", FrameAnimation_DESC("ConvergeShooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("PeashooterEquip", FrameAnimation_DESC("PeashooterEquip", 0.05f, true));
			ItemIconRenderers[i]->CreateFrameAnimationFolder("SpreadShooterEquip", FrameAnimation_DESC("SpreadShooterEquip", 0.05f, true));
			ItemIconRenderers[i]->ChangeFrameAnimation("UnKnown");
			ItemIconRenderers[i]->SetScaleModeImage();
			ItemIconRenderers[i]->GetTransform().SetLocalPosition(SelectorPosBack[i]);
			ItemIconRenderers[i]->ChangeCamera(CAMERAORDER::UICAMERA2);
			ItemIconRenderers[i]->Off();
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

	SelectedRenderer = CreateComponent<GameEngineTextureRenderer>();
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
		if (BeforePhase != GetPhase())
		{
			if (BeforePhase == InventoryPhase::ShotASlot)
			{
				for (int i = 0; i < ItemIconRenderers.size(); i++)
				{
					ItemIconRenderers[i]->Off();
				}
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
						EquippedShotAName = "UnKnown";
						FrontARenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontARenderer->CreateFrameAnimationFolder(EquippedShotAName, FrameAnimation_DESC(EquippedShotAName, 0.05f, true));
						FrontARenderer->ChangeFrameAnimation(EquippedShotAName);
						FrontARenderer->SetScaleModeImage();
						FrontARenderer->GetTransform().SetLocalPosition({ -198.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontARenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
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
						EquippedShotBName = "UnKnown";
						FrontBRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontBRenderer->CreateFrameAnimationFolder(EquippedShotBName, FrameAnimation_DESC(EquippedShotBName, 0.05f, true));
						FrontBRenderer->ChangeFrameAnimation(EquippedShotBName);
						FrontBRenderer->SetScaleModeImage();
						FrontBRenderer->GetTransform().SetLocalPosition({ -98.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontBRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
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
						EquippedSuperName = "UnKnown";
						FrontCRenderer = CreateComponent<GameEngineTextureRenderer>();
						FrontCRenderer->CreateFrameAnimationFolder(EquippedSuperName, FrameAnimation_DESC(EquippedSuperName, 0.05f, true));
						FrontCRenderer->ChangeFrameAnimation(EquippedSuperName);
						FrontCRenderer->SetScaleModeImage();
						FrontCRenderer->GetTransform().SetLocalPosition({ 0.0f,-165.0f, (int)ZOrder::UI - 5 });
						FrontCRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
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
			if (ShotABackRenderer == nullptr)
			{
				ShotABackRenderer = CreateComponent<GameEngineTextureRenderer>();
				ShotABackRenderer->SetTexture("generic_equip_back_9_icons.png");
				ShotABackRenderer->ScaleToTexture();
				ShotABackRenderer->GetTransform().SetLocalPosition({ 0.0f, -10.0f,(int)ZOrder::UI });
				ShotABackRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
			else
			{
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
					std::vector<ItemBase*> ShotAItems = _State->Items[ItemType::Shoot];

					int i = 0;
					for (ItemBase* Item : ShotAItems)
					{
						if (i < ShotAItems.size())
						{
							ItemIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
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
				// 아이템을 선택했다는 표시를 보여준다.
				//SelectedRenderer->ChangeFrameAnimation("");
				//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[0].x)
				{
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{
						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							_State->EquippedItems[InventoryType::ShotA] = ItemName[0];
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
	if (GetPhase() == InventoryPhase::ShotBSlot)
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
			if (ShotABackRenderer == nullptr)
			{
				ShotABackRenderer = CreateComponent<GameEngineTextureRenderer>();
				ShotABackRenderer->SetTexture("generic_equip_back_9_icons.png");
				ShotABackRenderer->ScaleToTexture();
				ShotABackRenderer->GetTransform().SetLocalPosition({ 0.0f, -10.0f,(int)ZOrder::UI });
				ShotABackRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
			else
			{
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
					std::vector<ItemBase*> ShotAItems = _State->Items[ItemType::Shoot];

					int i = 0;
					for (ItemBase* Item : ShotAItems)
					{
						if (i < ShotAItems.size())
						{
							ItemIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
							i++;
							//
						}
					}
				}
			}
		}
		// 상동 Selected Collision과 충돌했으면 Renderer의 애니메이션 바꾸기
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (ElapsedTime > SelectInvervalTime)
			{
				if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[0].x)
				{
					int a = 0;
					// 아이템을 선택했다는 표시를 보여준다.
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});

					// 이 아이템을 선택한 아이템으로 넣어야한다.
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{

						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotA]) &&
								nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotB])) // ShotA로 선택한 무기가 아니고 B로 선택한 무기가 아니면
							{
								_State->EquippedItems[InventoryType::ShotB] = new PeaShooterItem; // B로 넣어라
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
							if (nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotA]) &&
								nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotB])) // ShotA로 선택한 무기가 아니고 B로 선택한 무기가 아니면
							{
								_State->EquippedItems[InventoryType::ShotB] = new PeaShooterItem; // B로 넣어라
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[2].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[3].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[4].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[5].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[6].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[7].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[8].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
			}
		}
	}
	if (GetPhase() == InventoryPhase::SuperSlot)
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
				MaxPos = 3;
			}
			Selector->GetTransform().SetLocalPosition(SelectorPosBack[CurPos]);
			InventoryFront->SetTexture("ch_equip_back.png");
			if (ShotABackRenderer == nullptr)
			{
				ShotABackRenderer = CreateComponent<GameEngineTextureRenderer>();
				ShotABackRenderer->SetTexture("generic_equip_back_super_icons.png");
				ShotABackRenderer->ScaleToTexture();
				ShotABackRenderer->GetTransform().SetLocalPosition({ 0.0f, -10.0f,(int)ZOrder::UI });
				ShotABackRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
			}
			else
			{
				ShotABackRenderer->On();
			}

			for (int i = 0; i < SuperIconRenderers.size(); i++)
			{
				SuperIconRenderers[i]->On();
			}

			std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
			for (GameEngineActor* Actor : Actors)
			{
				if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
				{
					std::vector<ItemBase*> ShotAItems = _State->Items[ItemType::Super];

					int i = 0;
					for (ItemBase* Item : ShotAItems)
					{
						if (i < ShotAItems.size())
						{
							ItemIconRenderers[i]->ChangeFrameAnimation(Item->ItemName + "Equip");
							i++;
							//
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
					int a = 0;
					// 아이템을 선택했다는 표시를 보여준다.
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});

					// 이 아이템을 선택한 아이템으로 넣어야한다.
					std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
					for (GameEngineActor* Actor : Actors)
					{

						if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
						{
							if (nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotA]) &&
								nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotB])) // ShotA로 선택한 무기가 아니고 B로 선택한 무기가 아니면
							{
								_State->EquippedItems[InventoryType::ShotB] = new PeaShooterItem; // B로 넣어라
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
							if (nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotA]) &&
								nullptr == dynamic_cast<PeaShooterItem*>(_State->EquippedItems[InventoryType::ShotB])) // ShotA로 선택한 무기가 아니고 B로 선택한 무기가 아니면
							{
								_State->EquippedItems[InventoryType::ShotB] = new PeaShooterItem; // B로 넣어라
							}
						}
					}
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[2].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[3].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[4].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[5].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[6].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[7].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else if (Selector->GetTransform().GetLocalPosition().x == SelectorPosBack[8].x)
				{
					//SelectedRenderer->ChangeFrameAnimation("");
					//SelectedRenderer->GetTransform().SetLocalPosition(float4{});
				}
				else
				{
					return;
				}

				ElapsedTime = 0.0f;
			}
		}
	}
	if (GetPhase() == InventoryPhase::CharmSlot)
	{
		
	}
	{
		// Selector 이동
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
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::ShotBSlot:
			{
				FrontSlotB->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::SuperSlot:
			{
				FrontSlotC->Off();
				SetPhase(InventoryPhase::Front);
			}
			break;
			case InventoryPhase::CharmSlot:
			{
				FrontSlotD->Off();
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

		if (GetPhase() == InventoryPhase::Front)
		{
			MaxPos = 4;
			if (CurPos >= 4)
			{
				CurPos = 4;
			}
			Selector->GetTransform().SetLocalPosition(SelectorPosFront[CurPos]);
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