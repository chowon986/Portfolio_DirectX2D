#include "PreCompile.h"
#include "Background.h"
#include "TutorialLevel.h"
#include "WorldMapCuphead.h"
#include "InGameCuphead.h"
#include <GameEngineCore/GameEngineBlur.h>

TutorialLevel::TutorialLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
	}

	{
		GameEngineActor* TutorialBackground = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* TutorialRenderer = TutorialBackground->CreateComponent<GameEngineTextureRenderer>();
		TutorialRenderer->CreateFrameAnimationFolder("TutorialStartBackground", FrameAnimation_DESC("TutorialStartBackground", 0.05f, false));
		TutorialRenderer->CreateFrameAnimationFolder("TutorialBackground", FrameAnimation_DESC("TutorialBackground", 0.05f, false));
		TutorialRenderer->GetTransform().SetLocalScale({ 1577.0f,1045.0f,1.0f });
		TutorialRenderer->ChangeFrameAnimation("TutorialStartBackground");
		TutorialRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
	}

	{
		InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::Player});
		Cuphead->SetColMapImage(ColMapRenderer);
		PushToRotateCamera(Cuphead);
	}

	{
		GameEngineActor* WheatA = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		WheatARenderer = WheatA->CreateComponent<GameEngineTextureRenderer>();
		WheatARenderer->CreateFrameAnimationFolder("ParryWheatA", FrameAnimation_DESC("ParryWheatA", 0.05f, true));
		WheatARenderer->ChangeFrameAnimation("ParryWheatA");
		WheatARenderer->GetTransform().SetLocalPosition({ 745.0f, -580.0f, (int)ZOrder::Foreground });
		WheatARenderer->SetScaleModeImage();
	}

	{
		GameEngineActor* RipOpen = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		RipRenderer = RipOpen->CreateComponent<GameEngineTextureRenderer>();
		RipRenderer->CreateFrameAnimationFolder("Rip", FrameAnimation_DESC("Rip", 0.05f, false));
		RipRenderer->ChangeFrameAnimation("Rip");
		RipRenderer->GetTransform().SetLocalPosition({ 300.0f, -0.0f, (int)ZOrder::Foreground });
		RipRenderer->SetScaleModeImage();
		RipRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
	}

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}

void TutorialLevel::Update(float _DeltaTime)
{
}


void TutorialLevel::End()
{
}