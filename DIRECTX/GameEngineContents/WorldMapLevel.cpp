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
		Background* OutsideOfMainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OutsideOfMainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_water_multiply.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1, -213, (int)ZOrder::Background });
	}

	{
		Background* UnderWaterLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = UnderWaterLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_underwater_land.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1, -213, (int)ZOrder::Background-1 });
	}

	{
		Background* WaterLine = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = WaterLine->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 3710,1772,1 });
		Renderer->GetTransform().SetLocalPosition({ 0.0, -219.0f, (int)ZOrder::Background-2 });
		Renderer->CreateFrameAnimationFolder("WaterLine", FrameAnimation_DESC("WaterLine", 0, 0, 0.1f, true));
		Renderer->ChangeFrameAnimation("WaterLine");
	}

	{
		Background* MainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = MainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0.0, 0.0, (int)ZOrder::Background - 3 });
	}

	{
		Boatman* BoatMan = CreateActor<Boatman>(GameObjectGroup::UI);
		BoatMan->GetTransform().SetLocalPosition({ -1625.0f, -345.0f, (int)ZOrder::NPC});
	}

	{
		Background* BoatRipples = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = BoatRipples->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ -238,66,1 });
		Renderer->CreateFrameAnimationFolder("BoatmanRipples", FrameAnimation_DESC("BoatmanRipples", 0.1f, true));
		Renderer->ChangeFrameAnimation("BoatmanRipples");
		Renderer->GetTransform().SetLocalPosition({ -1626.0f, -610.0f, (int)ZOrder::NPC+1 });
	}

	{
		Background* Boat = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Boat->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ -233,148,1 });
		Renderer->CreateFrameAnimationFolder("Boat", FrameAnimation_DESC("Boat", 0.1f, true));
		Renderer->ChangeFrameAnimation("Boat");
		Renderer->GetTransform().SetLocalPosition({ -1626.0f, -562.0f,(int)ZOrder::NPC });
	}

	{
		Bakery* SaltBakerBakery = CreateActor<Bakery>(GameObjectGroup::UI);
		SaltBakerBakery->GetTransform().SetLocalPosition({ -840.0f, 575.0f, (int)ZOrder::NPC });
	}

	{
		Background* NextToBakery = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = NextToBakery->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -975.0f, 460.0f, (int)ZOrder::NPC-1 });
	}

	{
		Background* Cart = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Cart->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 176,179,1 });
		Renderer->CreateFrameAnimationFolder("Cart", FrameAnimation_DESC("Cart", 0.1f, true));
		Renderer->ChangeFrameAnimation("Cart");
		Renderer->GetTransform().SetLocalPosition({ -430.0f, 490.0f, (int)ZOrder::NPC });
	}

	{
		NewsCat* NewsieCat = CreateActor<NewsCat>(GameObjectGroup::UI);
		NewsieCat->GetTransform().SetLocalPosition({ -225.0f, 300.0f, (int)ZOrder::NPC });
	}

	{
		Shop* ItemShop = CreateActor<Shop>(GameObjectGroup::UI);
		ItemShop->GetTransform().SetLocalPosition({ -90.0f, 600.0f, (int)ZOrder::NPC });
	}

	{
		Background* Omm = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Omm->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 361,301,1 });
		Renderer->CreateFrameAnimationFolder("Omm", FrameAnimation_DESC("Omm", 0.1f, true));
		Renderer->ChangeFrameAnimation("Omm");
		Renderer->GetTransform().SetLocalPosition({ 653.0f, 704.0f, (int)ZOrder::NPC });
	}

	{
		Background* OmmTree = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 578.0f, 675.0f, (int)ZOrder::NPC-1 });
	}

	{
		Background* OmmTree2 = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree2->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees_B.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 766.0f, 559.0f, (int)ZOrder::NPC-2 });
	}

	{
		Background* Waterfall = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Waterfall->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 190,289,1 });
		Renderer->CreateFrameAnimationFolder("Waterfall", FrameAnimation_DESC("Waterfall", 0.1f, true));
		Renderer->ChangeFrameAnimation("Waterfall");
		Renderer->GetTransform().SetLocalPosition({ 25.0f, 95.0f, (int)ZOrder::NPC });
	}

	{
		Background* WaterfallBase = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = WaterfallBase->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 145,77,1 });
		Renderer->CreateFrameAnimationFolder("WaterfallBase", FrameAnimation_DESC("WaterfallBase", 0.1f, true));
		Renderer->ChangeFrameAnimation("WaterfallBase");
		Renderer->GetTransform().SetLocalPosition({ 38.0f, -55.0f, (int)ZOrder::NPC-1 });
	}

	{
		Background* waterfall_trees = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_trees->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 135.0f, 52.0f, (int)ZOrder::NPC-2 });
	}

	{
		Background* waterfall_left_overlay = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_left_overlay->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_left_overlay.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -57.0f, 10.0f, (int)ZOrder::NPC-3 });
	}

	{
		Lantern* NPCLantern = CreateActor<Lantern>(GameObjectGroup::UI);
		NPCLantern->GetTransform().SetLocalPosition({ 175.0f, 746.0f, (int)ZOrder::NPC });
	}

	{
		Pickaxe* NPCPickaxe = CreateActor<Pickaxe>(GameObjectGroup::UI);
		NPCPickaxe->GetTransform().SetLocalPosition({ 265.0f, 725.0f,(int)ZOrder::NPC });
	}

	{
		Shovel* NPCShovel = CreateActor<Shovel>(GameObjectGroup::UI);
		NPCShovel->GetTransform().SetLocalPosition({ 75.0f, 725.0f, (int)ZOrder::NPC });
	}

	{
		Background* Rumrunners = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Rumrunners->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 179,178,1 });
		Renderer->CreateFrameAnimationFolder("Rumrunners", FrameAnimation_DESC("Rumrunners", 0.1f, true));
		Renderer->ChangeFrameAnimation("Rumrunners");
		Renderer->GetTransform().SetLocalPosition({ -705.0, -268.0f, (int)ZOrder::NPC });
	}

	{
		Background* Cowgirl = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Cowgirl->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 169,224,1 });
		Renderer->CreateFrameAnimationFolder("Cowgirl", FrameAnimation_DESC("Cowgirl", 0.1f, true));
		Renderer->ChangeFrameAnimation("Cowgirl");
		Renderer->GetTransform().SetLocalPosition({ -475.0, -750.0f, (int)ZOrder::NPC });
	}

	{
		Catus* CatusGirl = CreateActor<Catus>(GameObjectGroup::UI);
		CatusGirl->GetTransform().SetLocalPosition({ -32.0, -692.0f, (int)ZOrder::NPC });
	}

	{
		// To do : 
		Ladder* RopeLadder = CreateActor<Ladder>(GameObjectGroup::UI);
		RopeLadder->GetTransform().SetLocalPosition({ -32.0, -650.0f, 100.0f });
	}

	{
		Background* BridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = BridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 322.0, -480.0f, (int)ZOrder::NPC+1 });
	}

	{
		Background* Bridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Bridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 322.0, -480.0f, (int)ZOrder::Foreground });
	}

	{
		Dogfight* DogfightEntry = CreateActor<Dogfight>(GameObjectGroup::UI);
		DogfightEntry->GetTransform().SetLocalPosition({ 760.0, -390.0f, (int)ZOrder::NPC });
	}

	{
		Ghost* GhostDetective = CreateActor<Ghost>(GameObjectGroup::UI);
		GhostDetective->GetTransform().SetLocalPosition({ 835.0f, -40.0f, (int)ZOrder::NPC });
	}

	{
		Background* StoneBridgeShadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridgeShadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_waterline_temp.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1185.0, -45.0f, (int)ZOrder::Foreground });
	}

	{
		Background* StoneBridge = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = StoneBridge->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_bottom.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1085.0, -10.0f, (int)ZOrder::Foreground });
	}

	{
		Background* Snow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Snow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 346,335,1 });
		Renderer->CreateFrameAnimationFolder("Snow", FrameAnimation_DESC("Snow", 0.1f, true));
		Renderer->ChangeFrameAnimation("Snow");
		Renderer->GetTransform().SetLocalPosition({ 1400, 450.0f,  (int)ZOrder::NPC });
	}

	{
		Background* snowbank_b = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_b->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_b.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1485, 331.0f, (int)ZOrder::NPC-1 });
	}

	{
		Background* snowbank_c = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = snowbank_c->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("snowbank_c.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1222, 373.0f, (int)ZOrder::NPC-1 });
	}

	{
		Background* dlc_ice_stairs_shadow = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_shadow->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 250.0f, (int)ZOrder::NPC+1 });
	}

	{
		Background* dlc_ice_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 925, 335.0f, (int)ZOrder::NPC-1 });
	}
	
	{
		Background* dlc_ice_stairs_front = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_ice_stairs_front->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_front.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 894, 300.0f, (int)ZOrder::NPC-2 });
	}

	{
		Background* dlc_canyon_stairs = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -205.0, -455.0f, (int)ZOrder::NPC });
	}

	{
		Background* dlc_canyon_stairs_back = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_canyon_stairs_back->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs_back.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -230.0, -450.0f, (int)ZOrder::NPC-1 });
	}

	{
		WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ -1473.0f, -296.0f, 100.0f, (int)ZOrder::Player});
	}

	{
		Background* dlc_entrance_stairs_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_entrance_stairs_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_entrance_stairs_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1040.0f, -160.0f, 100.0f, (int)ZOrder::NPC-500 });
	}

	{
		Background* dlc_chips_shack_awning_top = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = dlc_chips_shack_awning_top->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_chips_shack_awning_top.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1367.0f, -117.0f,(int)ZOrder::NPC-2 });
	}

	{
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