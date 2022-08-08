#include "PreCompile.h"
#include "DogFightLevel.h"
#include "Background.h"
#include "WorldMapCuphead.h"
#include "BackgroundHills.h"
#include "BackgroundObject.h"
#include "Bulldog.h"
#include "BulldogPlane.h"

DogFightLevel::DogFightLevel()
	: ColMapRenderer(nullptr)
{
}

DogFightLevel::~DogFightLevel()
{
}

void DogFightLevel::ColMapOnOffSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		BackgroundSkyRenderer->OnOffSwitch();
		Hills->OnOffSwitch();
	}
}

void DogFightLevel::Start()
{

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		if (ColMapImage == nullptr)
		{
			return;
		}
		ColMapRenderer->SetTexture("Test2.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		ColMapRenderer->GetTransform().SetLocalPosition({ ColMapRenderer->GetTransform().GetLocalPosition().x,ColMapRenderer->GetTransform().GetLocalPosition().y, (int)ZOrder::Background + 1 });
	}

	{
		Background* BackgroundSky = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundSkyRenderer = BackgroundSky->CreateComponent<GameEngineTextureRenderer>();
		if (BackgroundSky == nullptr)
		{
			return;
		}
		BackgroundSkyRenderer->SetTexture("background_sky_0001.png");
		BackgroundSkyRenderer->ScaleToTexture();
		BackgroundSkyRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		BackgroundSkyRenderer->GetTransform().SetLocalPosition({ BackgroundSkyRenderer->GetTransform().GetLocalPosition().x, BackgroundSkyRenderer->GetTransform().GetLocalPosition().y + 250, (int)ZOrder::Background });
	}

	{
		Hills = CreateActor<BackgroundHills>(GameObjectGroup::UI);
		if (Hills == nullptr)
		{
			return;
		}
		Hills->GetTransform().SetLocalPosition({ -50, -420, (int)ZOrder::Background - 2 });
	}

	//Cloud
	{
		{
			CloudA1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudA1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudA1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudA1", FrameAnimation_DESC("CloudA1", 0.06f, true));
			Renderer->AnimationBindEnd("CloudA1", std::bind(&DogFightLevel::ResetPositionCloudLeftA, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudA1");
			Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
			CloudA1->GetTransform().SetLocalPosition({ -150, -250, (int)ZOrder::Background - 1 });
			CloudA1->SetDirection((float4::RIGHT * 2) + (float4::DOWN * 0.5));
			CloudA1->SetMoveSpeed(250.0f);
		}

		{
			CloudA2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudA2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudA2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudA1", FrameAnimation_DESC("CloudA1", 0.06f, true));
			Renderer->AnimationBindEnd("CloudA1", std::bind(&DogFightLevel::ResetPositionCloudLeftA2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudA1");
			Renderer->SetPivot(PIVOTMODE::RIGHTCENTER);
			Renderer->GetTransform().PixLocalNegativeX();
			CloudA2->GetTransform().SetLocalPosition({ 1430, -250, (int)ZOrder::Background - 1 });
			CloudA2->SetDirection((float4::LEFT * 2) + (float4::DOWN * 0.5));
			CloudA2->SetMoveSpeed(250.0f);
		}

		{
			CloudB2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudB2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudB2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudB2", FrameAnimation_DESC("CloudB2", 0.06f, true));
			Renderer->AnimationBindEnd("CloudB2", std::bind(&DogFightLevel::ResetPositionCloudLeftB, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudB2");
			Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
			CloudB2->GetTransform().SetLocalPosition({ -150, -20, (int)ZOrder::Background - 1 });
			CloudB2->SetDirection((float4::RIGHT * 2) + float4::DOWN);
			CloudB2->SetMoveSpeed(250.0f);
		}

		{
			CloudC1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudC1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudC1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudC1", FrameAnimation_DESC("CloudC1", 0.05f, true));
			Renderer->AnimationBindEnd("CloudC1", std::bind(&DogFightLevel::ResetPositionCloudLeftC, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudC1");
			Renderer->GetTransform().PixLocalNegativeX();
			Renderer->SetPivot(PIVOTMODE::RIGHTCENTER);
			CloudC1->GetTransform().SetLocalPosition({ 1200, -20, (int)ZOrder::Background - 1 });
			CloudC1->SetDirection((float4::LEFT * 2) + (float4::DOWN * 1.5));
			CloudC1->SetMoveSpeed(250.0f);
		}

		{
			CloudC2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudC2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudC2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudC2", FrameAnimation_DESC("CloudC2", 0.05f, true));
			Renderer->AnimationBindEnd("CloudC2", std::bind(&DogFightLevel::ResetPositionCloudLeftC2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudC2");
			Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
			CloudC2->GetTransform().SetLocalPosition({ 150, -20, (int)ZOrder::Background - 1 });
			CloudC2->SetDirection((float4::RIGHT * 1.5) + (float4::DOWN * 1.5));
			CloudC2->SetMoveSpeed(250.0f);
		}

		{
			CloudD1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudD1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudD1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudD1", FrameAnimation_DESC("CloudD1", 0.05f, true));
			Renderer->AnimationBindEnd("CloudD1", std::bind(&DogFightLevel::ResetPositionCloudLeftD, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudD1");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			CloudD1->GetTransform().SetLocalPosition({ 640, -20, (int)ZOrder::Background - 1 });
			CloudD1->SetDirection(float4::DOWN * 1.8);
			CloudD1->SetMoveSpeed(250.0f);
		}

		{
			CloudD2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudD2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudD2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudD2", FrameAnimation_DESC("CloudD2", 0.05f, true));
			Renderer->AnimationBindEnd("CloudD2", std::bind(&DogFightLevel::ResetPositionCloudLeftD2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudD2");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			CloudD2->GetTransform().SetLocalPosition({ 1130, -20, (int)ZOrder::Background - 1 });
			CloudD2->SetDirection((float4::LEFT * 1.5) + (float4::DOWN * 1.5));
			CloudD2->SetMoveSpeed(250.0f);
		}

		{
			PlanePuffRight = CreateActor<BackgroundObject>(GameObjectGroup::Monster);
			if (PlanePuffRight == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PlanePuffRight->GetRenderer();
			Renderer->CreateFrameAnimationFolder("BulldogPlanePuffA", FrameAnimation_DESC("BulldogPlanePuffA", 0.03f, true));
			Renderer->AnimationBindEnd("BulldogPlanePuffA", std::bind(&DogFightLevel::ResetPositionPlanePuffRight, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("BulldogPlanePuffA");
			Renderer->ScaleToTexture();
			Renderer->SetPivot(PIVOTMODE::CENTER);
			PlanePuffRight->GetTransform().SetLocalPosition({ 900, -200, (int)ZOrder::NPC + 4 });
			PlanePuffRight->SetDirection((float4::LEFT * 1.5) + (float4::UP));
			PlanePuffRight->SetMoveSpeed(200.0f);
		}

		{
			PlanePuffLeft = CreateActor<BackgroundObject>(GameObjectGroup::Monster);
			if (PlanePuffLeft == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PlanePuffLeft->GetRenderer();
			Renderer->CreateFrameAnimationFolder("BulldogPlanePuffB", FrameAnimation_DESC("BulldogPlanePuffB", 0.03f, true));
			Renderer->AnimationBindEnd("BulldogPlanePuffB", std::bind(&DogFightLevel::ResetPositionPlanePuffLeft, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("BulldogPlanePuffB");
			Renderer->ScaleToTexture();
			Renderer->SetPivot(PIVOTMODE::CENTER);
			PlanePuffLeft->GetTransform().SetLocalPosition({ 380, -200, (int)ZOrder::NPC + 4 });
			PlanePuffLeft->SetDirection((float4::RIGHT * 1.5) + (float4::UP));
			PlanePuffLeft->SetMoveSpeed(200.0f);
		}
	}


	{
		{
			PatchLeftA = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (PatchLeftA == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PatchLeftA->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("PatchLeftA", FrameAnimation_DESC("PatchLeftA", 0.06f, true));
			Renderer->AnimationBindEnd("PatchLeftA", std::bind(&DogFightLevel::ResetPositionPatchLeftA, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("PatchLeftA");
			Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
			PatchLeftA->GetTransform().SetLocalPosition({ 100, -720, (int)ZOrder::Background - 3 });
			PatchLeftA->SetDirection(float4::RIGHT * 1.0 + (float4::UP * 0.5));
			PatchLeftA->SetMoveSpeed(280.0f);
		}
	}

	{
		Bulldog* PH1BullDog = CreateActor<Bulldog>(GameObjectGroup::Monster);
		if (PH1BullDog == nullptr)
		{
			return;
		}
		PH1BullDog->GetTransform().SetLocalPosition({ 640, -300, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFront", FrameAnimation_DESC("BulldogPlaneFront", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFront");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 640, -435, (int)ZOrder::NPC + 1 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingLeft", FrameAnimation_DESC("BulldogPlaneWingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 300, -400, (int)ZOrder::NPC + 3 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingRight", FrameAnimation_DESC("BulldogPlaneWingRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingRight");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 980, -400, (int)ZOrder::NPC + 3 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneBack", FrameAnimation_DESC("BulldogPlaneBack", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneBack");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 640, -262, (int)ZOrder::NPC + 2 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneTail", FrameAnimation_DESC("BulldogPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 640, -170, (int)ZOrder::NPC + 3 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorRingCenter", FrameAnimation_DESC("BulldogPropellorRingCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorRingCenter");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 640, -350, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipCenter", FrameAnimation_DESC("BulldogPropellorTipCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipCenter");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1});
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinCenter", FrameAnimation_DESC("BulldogPropellorSpinCenter", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinCenter");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 638, -350, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->GetTransform().PixLocalNegativeX();
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 1020, -340, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipRight", FrameAnimation_DESC("BulldogPropellorTipRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipRight");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 1020, -340, (int)ZOrder::NPC - 1 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinRight", FrameAnimation_DESC("BulldogPropellorSpinRight", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinRight");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 1025, -335, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 260, -340, (int)ZOrder::NPC });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipLeft", FrameAnimation_DESC("BulldogPropellorTipLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 260, -340, (int)ZOrder::NPC - 1 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftA", FrameAnimation_DESC("BulldogPlaneFlapLeftA", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftA");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 430, -260, (int)ZOrder::NPC + 4 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftB", FrameAnimation_DESC("BulldogPlaneFlapLeftB", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftB");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 150, -240, (int)ZOrder::NPC + 4 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightA", FrameAnimation_DESC("BulldogPlaneFlapRightA", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightA");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 850, -260, (int)ZOrder::NPC + 4 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightB", FrameAnimation_DESC("BulldogPlaneFlapRightB", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightB");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 1130, -240, (int)ZOrder::NPC + 4 });
	}

	{
		BulldogPlane* PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
		if (PH1BulldogPlane == nullptr)
		{
			return;
		}
		GameEngineTextureRenderer* Renderer = PH1BulldogPlane->GetRenderer();
		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinLeft", FrameAnimation_DESC("BulldogPropellorSpinLeft", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 260, -340, (int)ZOrder::NPC });
	}

	WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
	Cuphead->SetColMapImage(ColMapRenderer);
	Cuphead->GetTransform().SetLocalPosition({ 640, -360, -100 });
}

void DogFightLevel::ResetPositionCloudLeftA(const FrameAnimation_DESC& _Info)
{
	CloudA1->GetTransform().SetLocalPosition({ -150, -250, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftA2(const FrameAnimation_DESC& _Info)
{
	CloudA2->GetTransform().SetLocalPosition({ 1430, -250, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftB(const FrameAnimation_DESC& _Info)
{
	CloudB2->GetTransform().SetLocalPosition({ -150, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftC(const FrameAnimation_DESC& _Info)
{
	CloudC1->GetTransform().SetLocalPosition({ 1200, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftC2(const FrameAnimation_DESC& _Info)
{
	CloudC2->GetTransform().SetLocalPosition({ 150, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftD(const FrameAnimation_DESC& _Info)
{
	CloudD1->GetTransform().SetLocalPosition({ 640, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftD2(const FrameAnimation_DESC& _Info)
{
	CloudD2->GetTransform().SetLocalPosition({ 1130, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionPatchLeftA(const FrameAnimation_DESC& _Info)
{
	PatchLeftA->GetTransform().SetLocalPosition({ 100, -720, (int)ZOrder::Background - 3 });
}

void DogFightLevel::ResetPositionPlanePuffRight(const FrameAnimation_DESC& _Info)
{
	PlanePuffRight->GetTransform().SetLocalPosition({ 900, -200, (int)ZOrder::NPC + 4 });
}

void DogFightLevel::ResetPositionPlanePuffLeft(const FrameAnimation_DESC& _Info)
{
	PlanePuffLeft->GetTransform().SetLocalPosition({ 380, -200, (int)ZOrder::NPC + 4 });
}

void DogFightLevel::Update(float _DeltaTime)
{
	ColMapOnOffSwitch();
}

void DogFightLevel::End()
{
}
