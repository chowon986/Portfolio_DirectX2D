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
	, BeforeSelectItemNum(-1)
{
}

ShopLevel::~ShopLevel()
{
}

void ShopLevel::LevelStartEvent()
{
	//Loading
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");
	Dir.Move("01ShopLevel");
	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();
	for (GameEngineDirectory Dir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	std::vector<GameEngineFile> Textures = Dir.GetAllFile();
	for (size_t i = 0; i < Textures.size(); i++)
	{
		GameEngineTexture::Load(Textures[i].GetFullPath());
	}

	// Start
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
		LeftDrawerRenderer->GetTransform().SetLocalPosition({ -320, -210, (int)ZOrder::Background - 3 });
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
		IrisRenderer->CreateFrameAnimationFolder("IrisAStart", FrameAnimation_DESC("IrisA", 0.07f, false));
		IrisRenderer->AnimationBindEnd("IrisAStart", std::bind(&ShopLevel::EndIrisAnimation, this, std::placeholders::_1));
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
		IrisRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	}

	{
		GameEngineActor* CurCoin = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* CoinRenderer = CurCoin->CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->SetTexture("WorldMapCoin.png");
		CoinRenderer->ScaleToTexture();
		CoinRenderer->GetTransform().PixLocalNegativeX();
		CoinRenderer->GetTransform().SetWorldPosition({ -580.0f, 330.0f,(int)ZOrder::UI - 100 });
		CoinRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	}
	{
		GameEngineActor* CoinCount = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		CoinCountRenderer = CoinCount->CreateComponent<GameEngineTextureRenderer>();
		CoinCountRenderer->SetTexture("CoinCount0.png");
		CoinCountRenderer->ScaleToTexture();
		CoinCountRenderer->GetTransform().SetWorldPosition({ -535.0f, 330.0f,(int)ZOrder::UI - 100 });
		CoinCountRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
	}

	StartLerpValueX = { -320.0f, -850.0f };
	EndLerpValueX = { -850.0f, -780.0f };
	Phase = ShopPhase::None;


	{
		std::shared_ptr<TwinHeartItem> TwinHeartIcon = std::make_shared<TwinHeartItem>();
		std::shared_ptr<CursedRelicItem> CursedRelicIcon = std::make_shared<CursedRelicItem>();
		std::shared_ptr<SmokeBombItem> SmokeBombIcon = std::make_shared<SmokeBombItem>();
		std::shared_ptr<SpreadShooterItem> SpreadShooterIcon = std::make_shared<SpreadShooterItem>();
		std::shared_ptr<BoomerangShooterItem> BoomerangShooterIcon = std::make_shared<BoomerangShooterItem>();
		std::shared_ptr<ConvergeShooterItem> ConvergeShooterIcon = std::make_shared<ConvergeShooterItem>();
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

	for (std::shared_ptr<ItemBase> Item : ItemNames)
	{
		GameEngineActor* ItemIcon = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* ItemIconRenderer = ItemIcon->CreateComponent<GameEngineTextureRenderer>();
		ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName, FrameAnimation_DESC(Item->ItemName, 0.1f, false));
		ItemIconRenderer->CreateFrameAnimationFolder(Item->ItemName + "Select", FrameAnimation_DESC(Item->ItemName + "Select", 0.1f, true));
		ItemIconRenderer->CreateFrameAnimationFolder("ItemSelectOK", FrameAnimation_DESC("ItemSelectOK", 0.05f, true));
		ItemIconRenderer->AnimationBindEnd("ItemSelectOK", std::bind(&ShopLevel::BuyItemEnd, this, std::placeholders::_1));
		ItemIconRenderer->ChangeFrameAnimation(Item->ItemName);
		ItemIconRenderer->SetPivot(PIVOTMODE::BOT);
		if (IsOddNumber == true) // 홀수인가
		{
			ItemPosY = -70.0f;
			ItemIconRenderer->SetScaleModeImage();
			ItemIconRenderer->GetTransform().SetWorldPosition({ ItemPosX, ItemPosY, (int)ZOrder::UI - 100 });
		}
		else // 짝수인가
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

	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		FontRenderer = Font->CreateComponent<GameEngineTextureRenderer>();
		FontRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		FontRenderer->GetTransform().SetWorldPosition({ -300.0f, -205.0f,(int)ZOrder::Background - 2 });
	}

	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			State = _State;
			CurCoin = State->Coin;
		}
	}
}
void ShopLevel::Update(float _DeltaTime)
{
	if (State != nullptr)
	{
		CurCoin = State->Coin;
		if (CurCoin < 0)
		{
			CurCoin = 0;
		}
		else if (CurCoin > 25)
		{
			CurCoin = 25;
		}
		CoinCountRenderer->SetTexture("CoinCount" + std::to_string(CurCoin) + ".png");
	}

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
		}

		else if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
		{
			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum]);
			--SelectItemNum;

			if (SelectItemNum < 0)
			{
				SelectItemNum = 0;
			}
		}

		else if (true == GameEngineInput::GetInst()->IsDown("ESC"))
		{
			if (nullptr != State)
			{
				if (State->Coin != CurCoin)
				{
					State->Coin = CurCoin;
				}
			}
			ShopPig->GetRenderer()->ChangeFrameAnimation("Welcome"); // bye로 바꾸기, 닫히기, 바이 인사하기, iris
		}

		if (SelectItemNum != BeforeSelectItemNum)
		{
			BeforeSelectItemNum = SelectItemNum;
			FontRenderer->SetTexture("Font" + std::to_string(SelectItemNum) + ".png");
			FontRenderer->ScaleToTexture();
			ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum] + "Select");
		}
	}

	if (Phase == ShopPhase::Buy)
	{
		if (GameEngineInput::GetInst()->IsDown("ESC") /*|| nullptr == State*/)
		{
			Phase = ShopPhase::Select;
		}


		if (nullptr != State)
		{
			switch (SelectItemNum)
			{
			case 0:
				if (State->Coin >= 4)
				{
					State->Coin -= 4;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			case 1:
				if (State->Coin >= 3)
				{
					State->Coin -= 3;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			case 2:
				if (State->Coin >= 4)
				{
					State->Coin -= 4;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			case 3:
				if (State->Coin >= 1)
				{
					State->Coin -= 1;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			case 4:
				if (State->Coin >= 4)
				{
					State->Coin -= 4;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			case 5:
				if (State->Coin >= 3)
				{
					State->Coin -= 3;
					ItemRenderers[SelectItemNum]->ChangeFrameAnimation("ItemSelectOK");
					FontRenderer->SetTexture("Font6.png");
					Phase = ShopPhase::Select;
					return;
				}
				else
				{
					Phase = ShopPhase::Select;
					return;
				}
				break;
			default:
				break;
			}
		}
	}
}

void ShopLevel::End()
{
}

void ShopLevel::EndIrisAnimation(const FrameAnimation_DESC& _Info)
{
	ShopPig->GetRenderer()->ChangeFrameAnimation("Welcome");
	ItemRenderers[SelectItemNum]->ChangeFrameAnimation(ItemName[SelectItemNum] + "Select");
	FontRenderer->SetTexture("Font" + std::to_string(SelectItemNum) + ".png");
	FontRenderer->ScaleToTexture();
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
			std::shared_ptr<ItemBase> Item = ItemNames[SelectItemNum];
			State->Items[Type].push_back(Item);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (true == ItemRenderers[i]->IsUpdate())
		{
			SelectItemNum = i;
			Phase = ShopPhase::Select;
			return;
		}
	}

	Phase = ShopPhase::Select;
}
