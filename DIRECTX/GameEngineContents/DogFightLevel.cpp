#include "PreCompile.h"
#include "DogFightLevel.h"
#include "Background.h"
#include "InGameCuphead.h"
#include "BackgroundHills.h"
#include "BackgroundObject.h"

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

void DogFightLevel::ResetPositionCloudLeftA(const FrameAnimation_DESC& _Info)
{
	CloudLeftA->GetTransform().SetLocalPosition({ -70, -200, (int)ZOrder::Background - 1 });
}

void DogFightLevel::Start()
{

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		ColMapRenderer->GetTransform().SetLocalPosition({ ColMapRenderer->GetTransform().GetLocalPosition().x,ColMapRenderer->GetTransform().GetLocalPosition().y, (int)ZOrder::Background+1 });
	}

	{
		Background* BackgroundSky = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundSkyRenderer = BackgroundSky->CreateComponent<GameEngineTextureRenderer>();
		BackgroundSkyRenderer->SetTexture("background_sky_0001.png");
		BackgroundSkyRenderer->ScaleToTexture();
		BackgroundSkyRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		BackgroundSkyRenderer->GetTransform().SetLocalPosition({ ColMapRenderer->GetTransform().GetLocalPosition().x,ColMapRenderer->GetTransform().GetLocalPosition().y, (int)ZOrder::Background });
	}

	{
		Hills = CreateActor<BackgroundHills>(GameObjectGroup::UI);
		Hills->GetTransform().SetLocalPosition({ -50, -360, (int)ZOrder::Background - 1 });
	}

	{
		CloudLeftA = CreateActor<BackgroundObject>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = CloudLeftA->GetRenderer();
		Renderer->GetTransform().SetLocalPosition({ -70, -200, (int)ZOrder::Background - 1 });
		Renderer->CreateFrameAnimationFolder("CloudA1", FrameAnimation_DESC("CloudA1", 0.05f, true));
		Renderer->AnimationBindEnd("CloudA1", &DogFightLevel::ResetPositionCloudLeftA, this);
		Renderer->ChangeFrameAnimation("CloudA1");
		Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
		CloudLeftA->SetStartPosition({ -70, -200, (int)ZOrder::Background - 1 });
		CloudLeftA->SetDirection((float4::RIGHT*2) + (float4::DOWN * 0.5));
		CloudLeftA->SetMoveSpeed(200.0f);
	}

	InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
	Cuphead->SetColMapImage(ColMapRenderer);
	Cuphead->GetTransform().SetLocalPosition({ 100, -100, -100 });
}

void DogFightLevel::Update(float _DeltaTime)
{
	ColMapOnOffSwitch();
}

void DogFightLevel::End()
{
}
