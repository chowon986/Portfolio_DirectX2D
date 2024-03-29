#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "Background.h"
#include "WorldMapCuphead.h"
#include "Enums.h"
#include "Bakery.h"
#include "Omm.h"
#include "Boatman.h"
#include "NewsCat.h"
#include "Lantern.h"
#include "Pickaxe.h"
#include "Shovel.h"
#include "Shop.h"
#include "Catus.h"
#include "CharacterState.h"
#include "Ladder.h"
#include "Dogfight.h"
#include "Ghost.h"
#include "WaterLine.h"
#include "Boat.h"
#include "BoatRipples.h"
#include "Cart.h"
#include "Snow.h"
#include "Waterfall.h"
#include "WaterfallBase.h"
#include "Rumrunners.h"
#include "Cowgirl.h"
#include "WorldMapMugman.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "ItemInventory.h"
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineContents/TextureLoadUtils.h>
#include "CharacterScore.h"

WorldMapLevel::WorldMapLevel()
	: IrisRenderer(nullptr)
	, MainLandRenderer(nullptr)
	, MainLandColMapRenderer(nullptr)
	, UnderWaterLandRenderer(nullptr)
	, OutsideOfMainLandLeftRenderer(nullptr)
	, OutsideOfMainLandRightRenderer(nullptr)
	, State(nullptr)
	, CurCoin(0)
	, LoadCompleted(false)
	, Hourglass(nullptr)
	, FlagRenderer(nullptr)
	, TimeCountOn(false)
	, PineAppleElapsedTime(0.0f)
	, SoundOnceCheckA(false)
{
}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::ColMapOnOffSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		MainLandRenderer->OnOffSwitch();
		UnderWaterLandRenderer->OnOffSwitch();
		OutsideOfMainLandLeftRenderer->OnOffSwitch();
		OutsideOfMainLandRightRenderer->OnOffSwitch();
	}
}

void WorldMapLevel::GiveCoin()
{
	for (int i = 0; i < 5; i++)
	{
		EventCoinRenderers[i]->On();
	}
	GameEngineSound::SoundPlayOneShot("sfx_worldmap_coin_open.wav");
}

void WorldMapLevel::GivePineApple()
{
	for (int i = 0; i < 4; i++)
	{
		PineAppleRenderers[i]->On();
	}
	TimeCountOn = true;
}

void WorldMapLevel::Win()
{
	if (FlagRenderer == nullptr)
	{
		GameEngineActor* FlagActor = CreateActor<GameEngineActor>();
		FlagActor->GetTransform().SetLocalPosition({ 2700.0f, -1550.0f, (int)ZOrder::NPCB });
		FlagRenderer = FlagActor->CreateComponent<GameEngineTextureRenderer>();
		FlagRenderer->CreateFrameAnimationFolder("Flag", FrameAnimation_DESC("Flag", 0.07f, false));
		FlagRenderer->CreateFrameAnimationFolder("FlagLoop", FrameAnimation_DESC("FlagLoop", 0.07f, true));
		FlagRenderer->SetPivot(PIVOTMODE::LEFTBOT);
		FlagRenderer->ChangeFrameAnimation("Flag");
		FlagRenderer->SetScaleModeImage();
		FlagRenderer->AnimationBindFrame("Flag", std::bind(&WorldMapLevel::OnFlagAnimationFrameChanged, this, std::placeholders::_1));
	}
}


void WorldMapLevel::Start()
{
	//Start
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetBackgroundCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera2()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
}

void WorldMapLevel::LevelStartEvent()
{
	SoundOnceCheckA = false;

	if (Hourglass == nullptr)
	{
		Hourglass = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Hourglass->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("Loading", 0.05f));
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 545,-190,-100 });
	}
}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (TimeCountOn == true)
	{
		PineAppleElapsedTime += _DeltaTime;

		if (PineAppleElapsedTime > 2.0f)
		{
			for (int i = 0; i < 4; i++)
			{
				PineAppleRenderers[i]->Off();
			}

			TimeCountOn = false;
		}
	}

	if (LoadCompleted == false)
	{
		//Loading
		bool DogFightLevelLoadCompleted = TextureLoadUtils::LoadTexturesAsync("14WorldMapLevel");
		if (DogFightLevelLoadCompleted)
		{
			LoadCompleted = TextureLoadUtils::LoadTexturesAsync("05Item");
			if (LoadCompleted == true)
			{
				OnLoadCompleted();
			}
		}
		return;
	}

	if (SoundOnceCheckA == false)
	{
		Controller = GameEngineSound::SoundPlayControl("mus_dlc_map_b.wav");
		SoundOnceCheckA = true;
	}


	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("DogFight");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Inventory"))
	{
		if (Inventory != nullptr)
		{
			Inventory->OnOffSwitch();
		}
	}

	ColMapOnOffSwitch();


	if (State != nullptr)
	{
		if (CurCoin != State->Coin)
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
	}
}

void WorldMapLevel::LevelEndEvent()
{
	if (DogFightEntryBubbleRenderer->IsUpdate())
	{
		DogFightEntryBubbleRenderer->Off();
	}

	if (ShopEntryBubbleRenderer->IsUpdate())
	{
		ShopEntryBubbleRenderer->Off();
	}

	if (TutorialEntryBubbleRenderer->IsUpdate())
	{
		TutorialEntryBubbleRenderer->Off();
	}

	Controller.Stop();
}


void WorldMapLevel::End()
{
	Inventory->Off();
}

void WorldMapLevel::OnLoadCompleted()
{
	Inventory = CreateActor<ItemInventory>(GameObjectGroup::INVENTORY);
	Inventory->SetLevelOverOn();
	Inventory->Off();

	{
		GameEngineActor* EntryActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		DogFightEntryBubbleRenderer = EntryActor->CreateComponent<GameEngineTextureRenderer>();
		DogFightEntryBubbleRenderer->SetTexture("DogFightEntryBubble.png");
		DogFightEntryBubbleRenderer->ScaleToTexture();
		DogFightEntryBubbleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 300 });
		DogFightEntryBubbleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		DogFightEntryBubbleRenderer->Off();
	}

	{
		GameEngineActor* EntryActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		ShopEntryBubbleRenderer = EntryActor->CreateComponent<GameEngineTextureRenderer>();
		ShopEntryBubbleRenderer->SetTexture("ShopEntryBubble.png");
		ShopEntryBubbleRenderer->ScaleToTexture();
		ShopEntryBubbleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 300 });
		ShopEntryBubbleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		ShopEntryBubbleRenderer->Off();
	}

	{
		GameEngineActor* EntryActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		TutorialEntryBubbleRenderer = EntryActor->CreateComponent<GameEngineTextureRenderer>();
		TutorialEntryBubbleRenderer->SetTexture("TutorialEntryBubble.png");
		TutorialEntryBubbleRenderer->ScaleToTexture();
		TutorialEntryBubbleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 300 });
		TutorialEntryBubbleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		TutorialEntryBubbleRenderer->Off();
	}

	// 파인애플
	{
		GameEngineActor* PineAppleActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PineAppleRenderer = PineAppleActor->CreateComponent<GameEngineTextureRenderer>();
		PineAppleRenderer->SetTexture("GetPineApple.png");
		PineAppleRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		PineAppleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 150 });
		PineAppleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		PineAppleRenderer->Off();

		PineAppleRenderers.push_back(PineAppleRenderer);
	}

	{
		GameEngineActor* PineAppleActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PineAppleRenderer = PineAppleActor->CreateComponent<GameEngineTextureRenderer>();
		PineAppleRenderer->CreateFrameAnimationFolder("PineAppleShineBack", FrameAnimation_DESC("PineAppleShineBack", 0.05f));
		PineAppleRenderer->ChangeFrameAnimation("PineAppleShineBack");
		PineAppleRenderer->SetScaleModeImage();
		PineAppleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 200 });
		PineAppleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		PineAppleRenderer->Off();

		PineAppleRenderers.push_back(PineAppleRenderer);
	}

	{
		GameEngineActor* PineAppleActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PineAppleRenderer = PineAppleActor->CreateComponent<GameEngineTextureRenderer>();
		PineAppleRenderer->CreateFrameAnimationFolder("PineAppleShineForeBack", FrameAnimation_DESC("PineAppleShineForeBack", 0.05f));
		PineAppleRenderer->ChangeFrameAnimation("PineAppleShineForeBack");
		PineAppleRenderer->SetScaleModeImage();
		PineAppleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 250 });
		PineAppleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		PineAppleRenderer->Off();

		PineAppleRenderers.push_back(PineAppleRenderer);
	}

	{
		GameEngineActor* PineAppleActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PineAppleRenderer = PineAppleActor->CreateComponent<GameEngineTextureRenderer>();
		PineAppleRenderer->CreateFrameAnimationFolder("PineApple", FrameAnimation_DESC("PineApple", 0.07f));
		PineAppleRenderer->ChangeFrameAnimation("PineApple");
		PineAppleRenderer->SetScaleModeImage();
		PineAppleRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 300 });
		PineAppleRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		PineAppleRenderer->Off();

		PineAppleRenderers.push_back(PineAppleRenderer);
	}

	//이벤트 코인

	{
		GameEngineActor* EventCoinActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* BackgroundRenderer = EventCoinActor->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("GetCoin.png");
		BackgroundRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		BackgroundRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 300 });
		BackgroundRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		BackgroundRenderer->Off();

		EventCoinRenderers.push_back(BackgroundRenderer);
	}

	{
		GameEngineActor* EventCoinActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* CoinRenderer = EventCoinActor->CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.05f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 150 });
		CoinRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		CoinRenderer->Off();

		EventCoinRenderers.push_back(CoinRenderer);
	}

	{
		GameEngineActor* EventCoinActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* CoinRenderer = EventCoinActor->CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.05f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetWorldPosition({ -200.0f, 0.0f,(int)ZOrder::UI - 100 });
		CoinRenderer->Off();
		CoinRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		EventCoinRenderers.push_back(CoinRenderer);
	}

	{
		GameEngineActor* EventCoinActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* CoinRenderer = EventCoinActor->CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.05f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetWorldPosition({ 200.0f, 0.0f,(int)ZOrder::UI - 100 });
		CoinRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		CoinRenderer->Off();

		EventCoinRenderers.push_back(CoinRenderer);
	}

	{
		GameEngineActor* EventCoinActor = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* CoinDustRenderer = EventCoinActor->CreateComponent<GameEngineTextureRenderer>();
		CoinDustRenderer->CreateFrameAnimationFolder("CoinDust", FrameAnimation_DESC("CoinDust", 0.1f));
		CoinDustRenderer->ChangeFrameAnimation("CoinDust");
		CoinDustRenderer->SetScaleModeImage();
		CoinDustRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f,(int)ZOrder::UI - 50 });
		CoinDustRenderer->ChangeCamera(CAMERAORDER::UICAMERA2);
		CoinDustRenderer->Off();
		CoinDustRenderer->AnimationBindFrame("CoinDust", std::bind(&WorldMapLevel::OnEventCoinDustAnimationFrameChanged, this, std::placeholders::_1));

		EventCoinRenderers.push_back(CoinDustRenderer);
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

	{
		// 바다 배경 왼쪽
		Background* OutsideOfMainLandLeft = CreateActor<Background>(GameObjectGroup::UI);
		OutsideOfMainLandLeftRenderer = OutsideOfMainLandLeft->CreateComponent<GameEngineTextureRenderer>();
		OutsideOfMainLandLeftRenderer->SetTexture("dlc_water_multiply.png");
		OutsideOfMainLandLeftRenderer->ScaleToTexture();
		OutsideOfMainLandLeftRenderer->GetTransform().SetLocalPosition({ -2164, -1500, (int)ZOrder::Background });
	}

	{
		// 바다 배경 오른쪽
		Background* OutsideOfMainLandRight = CreateActor<Background>(GameObjectGroup::UI);
		OutsideOfMainLandRightRenderer = OutsideOfMainLandRight->CreateComponent<GameEngineTextureRenderer>();
		OutsideOfMainLandRightRenderer->SetTexture("dlc_water_multiply.png");
		OutsideOfMainLandRightRenderer->ScaleToTexture();
		OutsideOfMainLandRightRenderer->GetTransform().SetLocalPosition({ 2164, -1500, (int)ZOrder::Background });
	}

	{
		// 바다 아래 세상
		Background* UnderWaterLand = CreateActor<Background>(GameObjectGroup::UI);
		UnderWaterLandRenderer = UnderWaterLand->CreateComponent<GameEngineTextureRenderer>();
		UnderWaterLandRenderer->SetTexture("dlc_underwater_land.png");
		UnderWaterLandRenderer->ScaleToTexture();
		UnderWaterLandRenderer->GetTransform().SetLocalPosition({ 1853, -1318, (int)ZOrder::Background - 1 });
		//UnderWaterLandRenderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	{
		// 바닷물
		WaterLine* MainLandWaterLine = CreateActor<WaterLine>(GameObjectGroup::UI);
		MainLandWaterLine->GetTransform().SetLocalPosition({ 0, -437, (int)ZOrder::Background - 2 });
	}

	{
		// 땅
		Background* MainLand = CreateActor<Background>(GameObjectGroup::UI);
		MainLandRenderer = MainLand->CreateComponent<GameEngineTextureRenderer>();
		MainLandRenderer->SetTexture("dlc_main_land.png");
		MainLandRenderer->ScaleToTexture();
		MainLandRenderer->GetTransform().SetLocalPosition({ 1855, -1105, (int)ZOrder::Background - 3 });
	}

	{
		// 보트맨, 보트, 보트 물결
		Boatman* BoatMan = CreateActor<Boatman>(GameObjectGroup::UI);
		BoatMan->GetTransform().SetLocalPosition({ 240, -1450.0f, (int)ZOrder::NPCB });
	}
	{
		Boat* BoatManBoat = CreateActor<Boat>(GameObjectGroup::UI);
		BoatManBoat->GetTransform().SetLocalPosition({ 240, -1667.0f,(int)ZOrder::NPC });
	}
	{
		BoatRipples* BoatmanRipples = CreateActor<BoatRipples>(GameObjectGroup::UI);
		BoatmanRipples->GetTransform().SetLocalPosition({ 240, -1715, (int)ZOrder::NPC + 1 });
	}


	{
		// 빵집
		Bakery* SaltBakerBakery = CreateActor<Bakery>(GameObjectGroup::UI);
		SaltBakerBakery->GetTransform().SetLocalPosition({ 1020, -530, (int)ZOrder::NPC });
	}

	{
		// 빵집 옆
		Background* NextToBakery = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = NextToBakery->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 880, -645.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// 튜토리얼 카트
		Cart* TutorialCart = CreateActor<Cart>(GameObjectGroup::UI);
		TutorialCart->GetTransform().SetLocalPosition({ 1425, -615.0f, (int)ZOrder::NPC });
	}

	{
		// 뉴스캣
		NewsCat* NewsieCat = CreateActor<NewsCat>(GameObjectGroup::UI);
		NewsieCat->GetTransform().SetLocalPosition({ 1630.0, -805.0, (int)ZOrder::NPC });
	}

	{
		// 상점
		Shop* ItemShop = CreateActor<Shop>(GameObjectGroup::UI);
		ItemShop->GetTransform().SetLocalPosition({ 1765.0, -505.0f, (int)ZOrder::NPC });
	}

	{
		// 거인 입구
		Omm* OmmEntry = CreateActor<Omm>(GameObjectGroup::UI);
		OmmEntry->GetTransform().SetLocalPosition({ 2508.0, -401.0f, (int)ZOrder::NPC });
	}
	{
		// 거인 입구 옆 나무1
		Background* OmmTree = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2433.0f, -430.0f, (int)ZOrder::NPC - 1 });
	}
	{
		// 거인 입구 옆 나무2
		Background* OmmTree2 = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree2->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees_B.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2621.0f, -546.0f, (int)ZOrder::NPC - 2 });
	}

	{
		// 폭포
		Waterfall* MainWaterfall = CreateActor<Waterfall>(GameObjectGroup::UI);
		MainWaterfall->GetTransform().SetLocalPosition({ 1880.0f, -1010.0f, (int)ZOrder::NPC });
	}

	{
		// 폭포 물
		WaterfallBase* MainWaterfallBase = CreateActor<WaterfallBase>(GameObjectGroup::UI);
		MainWaterfallBase->GetTransform().SetLocalPosition({ 1900.0f, -1150.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// 폭포 옆 나무
		Background* waterfall_trees = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_trees->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1990.0f, -1053.0f, (int)ZOrder::NPCB });
	}

	{
		// 폭포 옆
		Background* waterfall_left_overlay = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_left_overlay->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_left_overlay.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1799.0, -1094.0f, (int)ZOrder::NPCB });
	}

	{
		// NPC 3명 중 가운데
		Lantern* NPCLantern = CreateActor<Lantern>(GameObjectGroup::UI);
		NPCLantern->GetTransform().SetLocalPosition({ 2025, -359.0, (int)ZOrder::NPC });
	}

	{
		// NPC 3명 중 오른쪽
		Pickaxe* NPCPickaxe = CreateActor<Pickaxe>(GameObjectGroup::UI);
		NPCPickaxe->GetTransform().SetLocalPosition({ 2120.0f, -380.0f,(int)ZOrder::NPC });
	}

	{
		// NPC 3명 중 왼쪽
		Shovel* NPCShovel = CreateActor<Shovel>(GameObjectGroup::UI);
		NPCShovel->GetTransform().SetLocalPosition({ 1930.0f, -380.0f, (int)ZOrder::NPC });
	}

	{
		// Rumrunner 입구
		Rumrunners* RumrunnersEntry = CreateActor<Rumrunners>(GameObjectGroup::UI);
		RumrunnersEntry->GetTransform().SetLocalPosition({ 1150.0, -1373.0f, (int)ZOrder::NPC });
	}

	{
		// Cowgirl 입구
		Cowgirl* CowgirlEntry = CreateActor<Cowgirl>(GameObjectGroup::UI);
		CowgirlEntry->GetTransform().SetLocalPosition({ 1380.0f, -1855.0f, (int)ZOrder::NPCB });
	}

	{
		// NPC
		Catus* CatusGirl = CreateActor<Catus>(GameObjectGroup::UI);
		CatusGirl->GetTransform().SetLocalPosition({ 1823.0f, -1797.0f, (int)ZOrder::NPCB });
	}

	{
		// 사다리 입구
		//Ladder* RopeLadder = CreateActor<Ladder>(GameObjectGroup::UI);
		//RopeLadder->GetTransform().SetLocalPosition({ 1823.0, -1755.0f, 100.0f });
	}

	{
		// 연결 통로 그림자
		Background* BridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = BridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2177.0f, -1585.0f, (int)ZOrder::NPC + 1 });
	}

	{
		// 연결통로
		Background* Bridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Bridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2177.0f, -1585.0f, (int)ZOrder::Foreground });
	}

	{
		// Dogfight 입구
		Dogfight* DogfightEntry = CreateActor<Dogfight>(GameObjectGroup::UI);
		DogfightEntry->GetTransform().SetLocalPosition({ 2615.0f, -1495.0f, (int)ZOrder::NPCB });
	}

	{
		// NPC
		Ghost* GhostDetective = CreateActor<Ghost>(GameObjectGroup::UI);
		GhostDetective->GetTransform().SetLocalPosition({ 2691.0f, -1143.0f, (int)ZOrder::NPC });

		Background* GhostHand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* HandRenderer = GhostHand->CreateComponent<GameEngineTextureRenderer>();
		HandRenderer->CreateFrameAnimationFolder("GhostHand", FrameAnimation_DESC("GhostHand", 0.1f));
		HandRenderer->ChangeFrameAnimation("GhostHand");
		HandRenderer->ScaleToTexture();
		HandRenderer->GetTransform().SetLocalPosition({ 2660, -1123,  (int)ZOrder::NPC });
	}

	{
		Background* Hanger = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Hanger->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("hangar_18.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3010, -1435.0f, (int)ZOrder::NPC });
	}

	{
		Background* LightHouse = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = LightHouse->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("LightHouse.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3119, -1300.0f, (int)ZOrder::NPC });
	}

	{
		// 연결 통로 그림자
		Background* StoneBridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_waterline_temp.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3040.0f, -1150.0f, (int)ZOrder::Foreground });
	}

	{
		// 연결 통로
		Background* StoneBridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_bottom.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2940.0f, -1115.0f, (int)ZOrder::Foreground });
	}

	{
		// Snow 맵 입구
		Snow* SnowEntry = CreateActor<Snow>(GameObjectGroup::UI);
		SnowEntry->GetTransform().SetLocalPosition({ 3255.0f, -650.0f,  (int)ZOrder::NPC });
	}

	{
		// Snow 맵 옆 
		Background* snowbank_b = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_b->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_b.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3340.0f, -780.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// Snow 맵 옆 
		Background* snowbank_c = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_c->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_c.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3077.0f, -731.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// 연결 통로 그림자
		Background* dlc_ice_stairs_shadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_shadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2715.0f, -850.0f, (int)ZOrder::NPC + 1 });
	}

	{
		// 연결 통로
		Background* dlc_ice_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2780.0f, -770.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// 연결 통로 옆
		Background* dlc_ice_stairs_front = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_front->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_front.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2749.0f, -805.0f, (int)ZOrder::NPCB });
	}

	{
		// 연결 통로
		Background* dlc_canyon_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1650.0f, -1565.0f, (int)ZOrder::NPC });
	}

	{
		// 연결 통로 그림자
		Background* dlc_canyon_stairs_back = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs_back->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs_back.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1625.0f, -1560.0f, (int)ZOrder::NPC - 1 });
	}

	{
		//ColMap
		Background* ColMap = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* MainLandColMapRenderer = ColMap->CreateComponent<GameEngineTextureRenderer>();
		MainLandColMapRenderer->SetTexture("dlc_main_land_ColMap.png");
		MainLandColMapRenderer->ScaleToTexture();
		MainLandColMapRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		MainLandColMapRenderer->GetTransform().SetLocalPosition({ 1855.0f, -1105.0f, (int)ZOrder::Background + 1 });

		// PC
		if (State != nullptr)
		{
			if (State->Type == CharacterType::Cuphead)
			{
				WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
				Cuphead->GetTransform().SetLocalPosition({ 1057.0f, -790.0f, (int)ZOrder::Player });
				Cuphead->SetColMapImage(MainLandColMapRenderer);
				Cuphead->SetInventory(Inventory);
			}
			else
			{
				WorldMapMugman* Mugman = CreateActor<WorldMapMugman>(GameObjectGroup::Player);
				Mugman->GetTransform().SetLocalPosition({ 1057.0f, -790.0f, (int)ZOrder::Player });
				Mugman->SetColMapImage(MainLandColMapRenderer);
			}
		}
		else
		{
			WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
			Cuphead->GetTransform().SetLocalPosition({ 1057.0f, -790.0f, (int)ZOrder::Player });
			Cuphead->SetColMapImage(MainLandColMapRenderer);
			Cuphead->SetInventory(Inventory);

		}

	}

	{
		// 입구 계단
		Background* dlc_entrance_stairs_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_entrance_stairs_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_entrance_stairs_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 815.0f, -1265.0f, (int)ZOrder::NPCB });
	}

	{
		// 생선 가게 천막
		Background* dlc_chips_shack_awning_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_chips_shack_awning_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_chips_shack_awning_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 488.0f, -1220.0f,(int)ZOrder::NPCB });
	}

	{
		// 가로등 아래
		Background* lower_flower_light = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = lower_flower_light->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lower_flower_light.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1235.0f, -1340.0f, (int)ZOrder::NPC - 1 });
	}

	{
		// 가로등 위
		Background* top_flower_light = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = top_flower_light->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("top_flower_light.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1235.0f, -1340.0f, (int)ZOrder::NPC - 2 });
	}

	{
		// MainTop
		Background* dlc_main_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_main_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1860.0f, -1085.0f, (int)ZOrder::NPCB });
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

void WorldMapLevel::OnEventCoinDustAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 12)
	{
		for (GameEngineTextureRenderer* Renderer : EventCoinRenderers)
		{
			Renderer->Off();
		}
		if (State != nullptr)
		{
			State->Coin = (State->Coin + 3);
		}
	}
}

void WorldMapLevel::OnFlagAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 17)
	{
		FlagRenderer->ChangeFrameAnimation("FlagLoop");
	}
}
