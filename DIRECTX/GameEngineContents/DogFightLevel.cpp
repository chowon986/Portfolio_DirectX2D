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
			Renderer->AnimationBindEnd("CloudA1", &DogFightLevel::ResetPositionCloudLeftA, this);
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
			Renderer->AnimationBindEnd("CloudA1", &DogFightLevel::ResetPositionCloudLeftA2, this);
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
Renderer->AnimationBindEnd("CloudB2", &DogFightLevel::ResetPositionCloudLeftB, this);
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
		Renderer->AnimationBindEnd("CloudC1", &DogFightLevel::ResetPositionCloudLeftC, this);
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
			Renderer->AnimationBindEnd("CloudC2", &DogFightLevel::ResetPositionCloudLeftC2, this);
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
			Renderer->AnimationBindEnd("CloudD1", &DogFightLevel::ResetPositionCloudLeftD, this);
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
			Renderer->AnimationBindEnd("CloudD2", &DogFightLevel::ResetPositionCloudLeftD2, this);
			Renderer->ChangeFrameAnimation("CloudD2");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			CloudD2->GetTransform().SetLocalPosition({ 1130, -20, (int)ZOrder::Background - 1 });
			CloudD2->SetDirection((float4::LEFT * 1.5) + (float4::DOWN * 1.5));
			CloudD2->SetMoveSpeed(250.0f);
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
			Renderer->AnimationBindEnd("PatchLeftA", &DogFightLevel::ResetPositionPatchLeftA, this);
			Renderer->ChangeFrameAnimation("PatchLeftA");
			Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
			PatchLeftA->GetTransform().SetLocalPosition({ 100, -720, (int)ZOrder::Background - 3 });
			PatchLeftA->SetDirection(float4::RIGHT * 1.0 + (float4::UP * 0.5));
			PatchLeftA->SetMoveSpeed(280.0f);
		}
	}

	//{
	//	Bulldog* PH1BullDog = CreateActor<Bulldog>(GameObjectGroup::Monster);
	//	if (PH1BullDog == nullptr)
	//	{
	//		return;
	//	}
	//	PH1BullDog->GetTransform().SetLocalPosition({ 640, -300, (int)ZOrder::NPC });
	//}

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
		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		PH1BulldogPlane->GetTransform().SetLocalPosition({ 400, -250, (int)ZOrder::NPC + 3 });
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

void DogFightLevel::Update(float _DeltaTime)
{
	ColMapOnOffSwitch();
}

void DogFightLevel::End()
{
}
