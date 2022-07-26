#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "Background.h"
#include "WorldMapCuphead.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Boatman.h"
#include "Bakery.h"
#include "NewsCat.h"
#include "Lantern.h"
#include "Pickaxe.h"
#include "Shovel.h"
#include "Shop.h"
#include "Catus.h"
#include "Ladder.h"
#include "Dogfight.h"
#include "Ghost.h"
#include "WaterLine.h"
#include "Boat.h"
#include "BoatRipples.h"
#include "Cart.h"
#include "Omm.h"
#include "Waterfall.h"
#include "WaterfallBase.h"
#include "Rumrunners.h"
#include "Cowgirl.h"
#include "Snow.h"

WorldMapLevel::WorldMapLevel()
{
}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ 0.0, 0.0f, -500.0f });


	{
		// 바다 배경 왼쪽
		Background* OutsideOfMainLandLeft = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OutsideOfMainLandLeft->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_water_multiply.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ -2164, 0, (int)ZOrder::Background });
	}

	{
		// 바다 배경 오른쪽
		Background* OutsideOfMainLandRight = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OutsideOfMainLandRight->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_water_multiply.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2164, 0, (int)ZOrder::Background });
	}

	{
		// 바다 아래 세상
		Background* UnderWaterLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = UnderWaterLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_underwater_land.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1, -213, (int)ZOrder::Background-1 });
	}

	{
		// 바닷물
		WaterLine* MainLandWaterLine = CreateActor<WaterLine>(GameObjectGroup::UI);
		MainLandWaterLine->GetTransform().SetLocalPosition({ -1.0, -219.0f, (int)ZOrder::Background - 2 });
	}

	{
		// 땅
		Background* MainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = MainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0.0, 0.0, (int)ZOrder::Background - 3 });
	}

	{
		// 보트맨, 보트, 보트 물결
		Boatman* BoatMan = CreateActor<Boatman>(GameObjectGroup::UI);
		BoatMan->GetTransform().SetLocalPosition({ -1625.0f, -345.0f, (int)ZOrder::NPC});

		Boat* BoatManBoat = CreateActor<Boat>(GameObjectGroup::UI);
		BoatManBoat->GetTransform().SetLocalPosition({ -1626.0f, -562.0f,(int)ZOrder::NPC });

		BoatRipples* BoatmanRipples = CreateActor<BoatRipples>(GameObjectGroup::UI);
		BoatmanRipples->GetTransform().SetLocalPosition({ -1626.0f, -610.0f, (int)ZOrder::NPC + 1 });
	}


	{
		// 빵집
		Bakery* SaltBakerBakery = CreateActor<Bakery>(GameObjectGroup::UI);
		SaltBakerBakery->GetTransform().SetLocalPosition({ -840.0f, 575.0f, (int)ZOrder::NPC });
	}

	{
		// 빵집 옆
		Background* NextToBakery = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = NextToBakery->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -975.0f, 460.0f, (int)ZOrder::NPC-1 });
	}

	{
		// 튜토리얼 카트
		Cart* TutorialCart = CreateActor<Cart>(GameObjectGroup::UI);
		TutorialCart->GetTransform().SetLocalPosition({ -430.0f, 490.0f, (int)ZOrder::NPC });
	}

	{
		// 뉴스캣
		NewsCat* NewsieCat = CreateActor<NewsCat>(GameObjectGroup::UI);
		NewsieCat->GetTransform().SetLocalPosition({ -225.0f, 300.0f, (int)ZOrder::NPC });
	}

	{
		// 상점
		Shop* ItemShop = CreateActor<Shop>(GameObjectGroup::UI);
		ItemShop->GetTransform().SetLocalPosition({ -90.0f, 600.0f, (int)ZOrder::NPC });
	}

	{
		// 거인 입구
		Omm* OmmEntry = CreateActor<Omm>(GameObjectGroup::UI);
		OmmEntry->GetTransform().SetLocalPosition({ 653.0f, 704.0f, (int)ZOrder::NPC });
	}
	{
		// 거인 입구 옆 나무1
		Background* OmmTree = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 578.0f, 675.0f, (int)ZOrder::NPC - 1 });
	}
	{
		// 거인 입구 옆 나무2
		Background* OmmTree2 = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree2->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees_B.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 766.0f, 559.0f, (int)ZOrder::NPC-2 });
	}

	{
		// 폭포
		Waterfall* MainWaterfall = CreateActor<Waterfall>(GameObjectGroup::UI);
		MainWaterfall->GetTransform().SetLocalPosition({ 25.0f, 95.0f, (int)ZOrder::NPC });
	}

	{
		// 폭포 물
		WaterfallBase* MainWaterfallBase = CreateActor<WaterfallBase>(GameObjectGroup::UI);
		MainWaterfallBase->GetTransform().SetLocalPosition({ 38.0f, -55.0f, (int)ZOrder::NPC-1 });
	}

	{
		// 폭포 옆 나무
		Background* waterfall_trees = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_trees->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 135.0f, 52.0f, (int)ZOrder::NPC-2 });
	}

	{
		// 폭포 옆
		Background* waterfall_left_overlay = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_left_overlay->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_left_overlay.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -57.0f, 10.0f, (int)ZOrder::NPC-3 });
	}

	{
		// NPC 3명 중 가운데
		Lantern* NPCLantern = CreateActor<Lantern>(GameObjectGroup::UI);
		NPCLantern->GetTransform().SetLocalPosition({ 175.0f, 746.0f, (int)ZOrder::NPC });
	}

	{
		// NPC 3명 중 오른쪽
		Pickaxe* NPCPickaxe = CreateActor<Pickaxe>(GameObjectGroup::UI);
		NPCPickaxe->GetTransform().SetLocalPosition({ 265.0f, 725.0f,(int)ZOrder::NPC });
	}

	{
		// NPC 3명 중 왼쪽
		Shovel* NPCShovel = CreateActor<Shovel>(GameObjectGroup::UI);
		NPCShovel->GetTransform().SetLocalPosition({ 75.0f, 725.0f, (int)ZOrder::NPC });
	}

	{
		// Rumrunner 입구
		Rumrunners* RumrunnersEntry = CreateActor<Rumrunners>(GameObjectGroup::UI);
		RumrunnersEntry->GetTransform().SetLocalPosition({ -705.0, -268.0f, (int)ZOrder::NPC });
	}

	{
		// Cowgirl 입구
		Cowgirl* CowgirlEntry = CreateActor<Cowgirl>(GameObjectGroup::UI);
		CowgirlEntry->GetTransform().SetLocalPosition({ -475.0, -750.0f, (int)ZOrder::NPC });
	}

	{
		// NPC
		Catus* CatusGirl = CreateActor<Catus>(GameObjectGroup::UI);
		CatusGirl->GetTransform().SetLocalPosition({ -32.0, -692.0f, (int)ZOrder::NPC });
	}

	{
		// 사다리 입구
		Ladder* RopeLadder = CreateActor<Ladder>(GameObjectGroup::UI);
		RopeLadder->GetTransform().SetLocalPosition({ -32.0, -650.0f, 100.0f });
	}

	{
		// 연결 통로 그림자
		Background* BridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = BridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 322.0, -480.0f, (int)ZOrder::NPC+1 });
	}

	{
		// 연결통로
		Background* Bridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Bridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 322.0, -480.0f, (int)ZOrder::Foreground });
	}

	{
		// Dogfight 입구
		Dogfight* DogfightEntry = CreateActor<Dogfight>(GameObjectGroup::UI);
		DogfightEntry->GetTransform().SetLocalPosition({ 760.0, -390.0f, (int)ZOrder::NPC });
	}

	{
		// NPC
		Ghost* GhostDetective = CreateActor<Ghost>(GameObjectGroup::UI);
		GhostDetective->GetTransform().SetLocalPosition({ 835.0f, -40.0f, (int)ZOrder::NPC });
	}

	{
		// 연결 통로 그림자
		Background* StoneBridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_waterline_temp.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1185.0, -45.0f, (int)ZOrder::Foreground });
	}

	{
		// 연결 통로
		Background* StoneBridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_bottom.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1085.0, -10.0f, (int)ZOrder::Foreground });
	}

	{
		// Snow 맵 입구
		Snow* SnowEntry = CreateActor<Snow>(GameObjectGroup::UI);
		SnowEntry->GetTransform().SetLocalPosition({ 1400, 450.0f,  (int)ZOrder::NPC });
	}

	{
		// Snow 맵 옆 
		Background* snowbank_b = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_b->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_b.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1485, 331.0f, (int)ZOrder::NPC-1 });
	}

	{
		// Snow 맵 옆 
		Background* snowbank_c = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_c->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_c.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1222, 373.0f, (int)ZOrder::NPC-1 });
	}

	{
		// 연결 통로 그림자
		Background* dlc_ice_stairs_shadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_shadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 250.0f, (int)ZOrder::NPC+1 });
	}

	{
		// 연결 통로
		Background* dlc_ice_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 925, 335.0f, (int)ZOrder::NPC-1 });
	}
	
	{
		// 연결 통로 옆
		Background* dlc_ice_stairs_front = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_front->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_front.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 894, 300.0f, (int)ZOrder::NPC-2 });
	}

	{
		// 연결 통로
		Background* dlc_canyon_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -205.0, -455.0f, (int)ZOrder::NPC });
	}

	{
		// 연결 통로 그림자
		Background* dlc_canyon_stairs_back = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs_back->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs_back.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -230.0, -450.0f, (int)ZOrder::NPC-1 });
	}

	{
		// PC
		WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ -1473.0f, -296.0f, 100.0f, (int)ZOrder::Player});
	}

	{
		// 입구 계단
		Background* dlc_entrance_stairs_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_entrance_stairs_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_entrance_stairs_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1040.0f, -160.0f, 100.0f, (int)ZOrder::NPC-500 });
	}

	{
		// 생선 가게 천막
		Background* dlc_chips_shack_awning_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_chips_shack_awning_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_chips_shack_awning_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1367.0f, -117.0f,(int)ZOrder::NPC-2 });
	}

	{
		// MainTop
		Background* dlc_main_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_main_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 5, 20.0f, (int)ZOrder::NPC-1000 });
	}

}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		//GEngine::ChangeLevel("Title");
	}
}


void WorldMapLevel::End()
{
	int a = 0;
}