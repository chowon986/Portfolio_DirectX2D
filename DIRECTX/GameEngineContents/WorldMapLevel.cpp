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
	}

	{
		Background* UnderWaterLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = UnderWaterLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_underwater_land.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -1, -213, -500.0f });
	}

	{
		Background* WaterLine = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = WaterLine->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 3710,1772,100 });
		Renderer->GetTransform().SetLocalPosition({ 0.0, -219.0f, -500.0f });
		Renderer->CreateFrameAnimationFolder("WaterLine", FrameAnimation_DESC("WaterLine", 0, 0, 0.1f, true));
		Renderer->ChangeFrameAnimation("WaterLine");
	}

	{
		Background* MainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = MainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land.png");
		Renderer->ScaleToTexture();
	}

	{
		Boatman* BoatMan = CreateActor<Boatman>(GameObjectGroup::UI);
		BoatMan->GetTransform().SetLocalPosition({ -1625.0f, -345.0f, 100.0f, 0.0f });
	}

	{
		Background* BoatRipples = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = BoatRipples->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ -238,66,100 });
		Renderer->CreateFrameAnimationFolder("BoatmanRipples", FrameAnimation_DESC("BoatmanRipples", 0.1f, true));
		Renderer->ChangeFrameAnimation("BoatmanRipples");
		Renderer->GetTransform().SetLocalPosition({ -1626.0f, -610.0f, 100.0f});
	}

	{
		Background* Boat = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Boat->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ -233,148,100 });
		Renderer->CreateFrameAnimationFolder("Boat", FrameAnimation_DESC("Boat", 0.1f, true));
		Renderer->ChangeFrameAnimation("Boat");
		Renderer->GetTransform().SetLocalPosition({ -1626.0f, -562.0f, 100.0f });
	}

	{
		Bakery* SaltBakerBakery = CreateActor<Bakery>(GameObjectGroup::UI);
		SaltBakerBakery->GetTransform().SetLocalPosition({ -840.0f, 575.0f, 100.0f });
	}

	{
		Background* NextToBakery = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = NextToBakery->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -975.0f, 460.0f, 100.0f });
	}

	{
		Background* Cart = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Cart->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 176,179,100 });
		Renderer->CreateFrameAnimationFolder("Cart", FrameAnimation_DESC("Cart", 0.1f, true));
		Renderer->ChangeFrameAnimation("Cart");
		Renderer->GetTransform().SetLocalPosition({ -430.0f, 490.0f, 100.0f });
	}

	{
		NewsCat* NewsieCat = CreateActor<NewsCat>(GameObjectGroup::UI);
		NewsieCat->GetTransform().SetLocalPosition({ -225.0f, 300.0f, 100.0f, 0.0f });
	}

	{
		Shop* ItemShop = CreateActor<Shop>(GameObjectGroup::UI);
		ItemShop->GetTransform().SetLocalPosition({ -100.0f, 490.0f, 100.0f, 0.0f });
	}

	{
		Background* Omm = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Omm->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 361,301,100 });
		Renderer->CreateFrameAnimationFolder("Omm", FrameAnimation_DESC("Omm", 0.1f, true));
		Renderer->ChangeFrameAnimation("Omm");
		Renderer->GetTransform().SetLocalPosition({ 653.0f, 704.0f, 100.0f });
	}

	{
		Background* OmmTree = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 578.0f, 675.0f, 100.0f });
	}

	{
		Background* OmmTree2 = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OmmTree2->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("omm_trees_B.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 766.0f, 558.0f, 100.0f });
	}

	{
		Background* Waterfall = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Waterfall->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 190,289,100 });
		Renderer->CreateFrameAnimationFolder("Waterfall", FrameAnimation_DESC("Waterfall", 0.1f, true));
		Renderer->ChangeFrameAnimation("Waterfall");
		Renderer->GetTransform().SetLocalPosition({ 25.0f, 95.0f, 100.0f });
	}

	{
		Background* WaterfallBase = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = WaterfallBase->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 145,77,100 });
		Renderer->CreateFrameAnimationFolder("WaterfallBase", FrameAnimation_DESC("WaterfallBase", 0.1f, true));
		Renderer->ChangeFrameAnimation("WaterfallBase");
		Renderer->GetTransform().SetLocalPosition({ 38.0f, -55.0f, 100.0f });
	}

	{
		Background* waterfall_trees = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_trees->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_trees.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 135.0f, 52.0f, 100.0f });
	}

	{
		Background* waterfall_left_overlay = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = waterfall_left_overlay->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("waterfall_left_overlay.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -57.0f, 10.0f, 100.0f });
	}

	{
		Lantern* NPCLantern = CreateActor<Lantern>(GameObjectGroup::UI);
		NPCLantern->GetTransform().SetLocalPosition({ 175.0f, 746.0f, 100.0f, 0.0f });
	}

	{
		Pickaxe* NPCPickaxe = CreateActor<Pickaxe>(GameObjectGroup::UI);
		NPCPickaxe->GetTransform().SetLocalPosition({ 265.0f, 725.0f, 100.0f, 0.0f });
	}

	{
		Shovel* NPCShovel = CreateActor<Shovel>(GameObjectGroup::UI);
		NPCShovel->GetTransform().SetLocalPosition({ 75.0f, 725.0f, 100.0f, 0.0f });
	}

	{
		WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
		//Cuphead->GetTransform().SetLocalPosition({ -1473.0f, -296.0f, 100.0f, 0.0f });
		Cuphead->GetTransform().SetLocalPosition({ -300.0f, 300.0f, 100.0f, 0.0f });
	}

	{
		Background* WaterfallBase = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = WaterfallBase->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 145,77,100 });
		Renderer->CreateFrameAnimationFolder("WaterfallBase", FrameAnimation_DESC("WaterfallBase", 0.1f, true));
		Renderer->ChangeFrameAnimation("WaterfallBase");
		Renderer->GetTransform().SetLocalPosition({ 38.0f, -55.0f, 100.0f });
	}

	{
		Background* Rumrunners = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Rumrunners->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 179,178,100 });
		Renderer->CreateFrameAnimationFolder("Rumrunners", FrameAnimation_DESC("Rumrunners", 0.1f, true));
		Renderer->ChangeFrameAnimation("Rumrunners");
		Renderer->GetTransform().SetLocalPosition({ -705.0, -268.0f, 100.0f });
	}

	{
		Background* Cowgirl = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Cowgirl->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 169,224,100 });
		Renderer->CreateFrameAnimationFolder("Cowgirl", FrameAnimation_DESC("Cowgirl", 0.1f, true));
		Renderer->ChangeFrameAnimation("Cowgirl");
		Renderer->GetTransform().SetLocalPosition({ -475.0, -750.0f, 100.0f });
	}

	{
		Catus* CatusGirl = CreateActor<Catus>(GameObjectGroup::UI);
		CatusGirl->GetTransform().SetLocalPosition({ -32.0, -692.0f, 100.0f });
	}

	{
		Ladder* RopeLadder = CreateActor<Ladder>(GameObjectGroup::UI);
		RopeLadder->GetTransform().SetLocalPosition({ -32.0, -692.0f, 100.0f });
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