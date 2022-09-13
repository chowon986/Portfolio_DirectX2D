#include "PreCompile.h"
#include "ShopLevel.h"
#include "Background.h"
#include "Enums.h"
#include "Pig.h"
#include <functional>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "SpreadShooterItem.h"
#include "CursedRelicItem.h"
#include "SmokeBombItem.h"
#include "TwinHeartItem.h"
#include "BoomerangShooterItem.h"
#include "ConvergeShooterItem.h"
#include "CharacterState.h"
#include <GameEngineCore/GameEngineBlur.h>
#include "SpreadShooter.h"
#include "ConvergeShooter.h"
#include "BoomerangShooter.h"

ShopLevel::ShopLevel()
	: IrisRenderer(nullptr)
	, IsLeftDrawerOpen(false)
	, IsLeftDrawerOpened(false)
	, OnceCheck(false)
	, ItemPosX(-580)
	, ItemPosY(0)
	, IsOddNumber(false)
	, ElapsedTime(0.0f)
	, Inventory(nullptr)
	, LeftDrawerRenderer(nullptr)
	, Phase(ShopPhase::None)
	, SelectItemNum(0)
	, ShopPig(nullptr)
	, Time(0.0f)
{
}

ShopLevel::~ShopLevel()
{
	for (ItemBase* Item : ItemNames)
	{
		if (Item != nullptr)
		{
			delete Item;
			Item = nullptr;
		}
	}
}

void ShopLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	{
		Background* ShopBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = ShopBackground->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_shop_bg.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 200, (int)ZOrder::Background });
	}

	{
		Background* TableChalkboard = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = TableChalkboard->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("shop_table_chalkboard.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* LeftDrawer = CreateActor<Background>(GameObjectGroup::UI);
		LeftDrawerRenderer = LeftDrawer->CreateComponent<GameEngineTextureRenderer>();
		LeftDrawerRenderer->SetTexture("dlc_shop_drawer_left.png");
		LeftDrawerRenderer->ScaleToTexture();
		LeftDrawerRenderer->GetTransform().SetLocalPosition({ -320, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* RightDrawer = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = RightDrawer->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_shop_drawer_Right.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 320, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* ShopTable = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = ShopTable->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("shop_table.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -195, (int)ZOrder::Background - 5 });
	}

	{
		ShopPig = CreateActor<Pig>(GameObjectGroup::UI);
	}

	{
		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280,720,1 });
		IrisRenderer->GetTransform().SetLocalPosition({ 0,0,-1000 });
		IrisRenderer->CreateFrameAnimationFolder("IrisAStart", FrameAnimation_DESC("IrisA", 0.1f, false));
		IrisRenderer->AnimationBindEnd("IrisAStart", std::bind(&ShopLevel::EndIrisAnimation, this, std::placeholders::_1));
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
	}
	StartLerpValueX = { -320.0f, -850.0f };
	EndLerpValueX = { -850.0f, -780.0f };
	Phase = ShopPhase::None;


	{
		TwinHeartItem* TwinHeartIcon = new TwinHeartItem();
		CursedRelicItem* CursedRelicIcon = new CursedRelicItem();
		SmokeBombItem* SmokeBombIcon = new SmokeBombItem();
		SpreadShooterItem* SpreadShooterIcon = new SpreadShooterItem();
		BoomerangShooterItem* BoomerangShooterIcon = new BoomerangShooterItem();
		ConvergeShooterItem* ConvergeShooterIcon = new ConvergeShooterItem();
		ItemNames.push_back(SpreadShooterIcon);
		ItemNames.push_back(TwinHeartIcon);
		ItemNames.push_back(BoomerangShooterIcon);
		ItemNames.push_back(CursedRelicIcon);
		ItemNames.push_back(ConvergeShooterIcon);
		ItemNames.push_back(SmokeBombIcon);

		SpreadShooter* ShooterA = CreateActor<SpreadShooter>();
		SpreadShooterIcon->Weapon = ShooterA;
		SpreadShooterIcon->Weapon->SetLevelOverOn();

		BoomerangShooter* ShooterB = CreateActor<BoomerangShooter>();
		BoomerangShooterIcon->Weapon = ShooterB;
		BoomerangShooterIcon->Weapon->SetLevelOverOn();

		ConvergeShooter* ShooterC = CreateActor<ConvergeShooter>(); 
		ConvergeShooterIcon->Weapon = ShooterC;
		ConvergeShooterIcon->Weapon->SetLevelOverOn();
	}

	for (ItemBase* Item : ItemNames)
	{
		GameEngineActor* ItemIcon = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* ItemIconRenderer = ItemIcon->CreateComponent<GameEngineTextureRenderer>();
		ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName, FrameAnimation_DESC(Item->ItemName, 0.1f, false));
		ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Select", FrameAnimation_DESC(Item->ItemName + "Select", 0.1f, true));
		ItemIconRenderer->CreateFrameAnimationFolder("ItemSelectOK", FrameAnimation_DESC("ItemSelectOK", 0.05f, true));
		ItemIconRenderer->AnimationBindEnd("ItemSelectOK", std::bind(&ShopLevel::BuyItemEnd, this, std::placeholders::_1));
		ItemIconRenderer->ChangeFrameAnimation(Item->ItemName);
		ItemIconRenderer->SetPivot(PIVOTMODE::BOT);
		if (IsOddNumber == true) // È¦¼öÀÎ°¡
		{
			ItemPosY = -70.0f;
			ItemIconRenderer->SetScaleModeImage();
			ItemIconRenderer->GetTransform().SetWorldPosition({ ItemPosX, ItemPosY, (int)ZOrder::UI - 100 });
		}
		else // Â¦¼öÀÎ°¡
		{
			ItemPosY = -20.0f;
			ItemIconRenderer->SetScaleModeImage();
			ItemIconRenderer->GetTransform().SetWorldPosition({ ItemPosX, ItemPosY, (int)ZOrder::UI - 50 });
		}
		OddEvenSwitch();
		ItemPosX += 80.0f;
		ItemRenderers.push_back(ItemIconRenderer);
		ItemName.push_back(Item->ItemName);
	}

	
}

void ShopLevel::Update(float _DeltaTime)
{
		if (OnceCheck == true)
		{
			ElapsedTime += _DeltaTime;
			ElapsedTime = ElapsedTime / 1.0f;
			float LeftDrawerPosX = LeftDrawerRenderer->GetTransform().GetLocalPosition().x;

			if (IsLeftDrawerOpened == false)
			{
				if (StartLerpValueX.y == LeftDrawerPosX)
				{
					IsLeftDrawerOpened = true;
					ElapsedTime = 0.0f;
				}

				EndPosition = float4::LerpLimit(StartLerpValueX.x, StartLerpValueX.y, ElapsedTime);
			}
			else
			{
				if (EndLerpValueX.y == LeftDrawerPosX)
				{
					OnceCheck = false;
					Phase = ShopPhase::Select;
				}
				EndPosition = float4::LerpLimit(EndLerpValueX.x, EndLerpValueX.y, ElapsedTime);
			}

			LeftDrawerRenderer->GetTransform().SetLocalPosition({ EndPosition.x, -210, (int)ZOrder::Background - 2 });
		}

	if (Phase == ShopPhase::Select)
	{
		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			Phase = ShopPhase::Buy;
		}

		if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
		{
			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum]);
			++SelectItemNum;

			if (SelectItemNum >= 6)
			{
				SelectItemNum = 5;
			}

			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum] + "Select");
		}

		else if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
		{
			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum]);
			--SelectItemNum;

			if (SelectItemNum < 0)
			{
				SelectItemNum = 0;
			}

			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum] + "Select");
		}
	}

	if (Phase == ShopPhase::Buy)
	{
		ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
	}
}

void ShopLevel::End()
{
}

void ShopLevel::EndIrisAnimation(const FrameAnimation_DESC& _Info)
{
	ShopPig->GetRenderer()->ChangeFrameAnimation("Welcome");
	ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum] + "Select");
	OnceCheck = true;
}

void ShopLevel::BuyItemEnd(const FrameAnimation_DESC& _Info)
{
	ItemRenderers[SelectItemNum]->GetActor()->Off();
	
	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* State = dynamic_cast<CharacterState*>(Actor))
		{
			ItemType Type = ItemNames[SelectItemNum]->Type;
			ItemBase* Item = ItemNames[SelectItemNum];
			State->Items[Type].push_back(Item);
		}
	}

	Phase = ShopPhase::Select;
}
