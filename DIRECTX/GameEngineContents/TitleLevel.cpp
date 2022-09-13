#include <functional>
#include "PreCompile.h"
#include "TitleLevel.h"
#include "Background.h"
#include <GameEngineCore/GameEngineBlur.h>

TitleLevel::TitleLevel()
	: IrisRenderer(nullptr)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		Background* Title = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* TitleRenderer = Title->CreateComponent<GameEngineTextureRenderer>();
		TitleRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		TitleRenderer->SetTexture("TitleScreenBackground.png");
		TitleRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Background }); 

		Background* Bottom = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* BottomRenderer = Bottom->CreateComponent<GameEngineTextureRenderer>();
		BottomRenderer->GetTransform().SetLocalScale({ 1328.0f, 176.0f, 1.0f });
		BottomRenderer->GetTransform().SetLocalPosition({ 18.0f, -300.0f, (int)ZOrder::Player - 2 });
		BottomRenderer->SetTexture("TitleChipsLeft.png");

		Background* Button = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* ButtonRenderer = Button->CreateComponent<GameEngineTextureRenderer>();
		ButtonRenderer->CreateFrameAnimationFolder("Press", FrameAnimation_DESC("PressAnyKey", 0.5f));
		ButtonRenderer->ChangeFrameAnimation("Press");
		ButtonRenderer->GetTransform().SetLocalScale({ 363.0f, 49.0f, 1.0f });
		ButtonRenderer->GetTransform().SetLocalPosition({ 0.0f, -293.0f,  (int)ZOrder::Player - 3 });

		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		IrisRenderer->CreateFrameAnimationFolder("IrisBStart", FrameAnimation_DESC("IrisB", 0.07f, false));
		IrisRenderer->CreateFrameAnimationFolder("IrisB", FrameAnimation_DESC("IrisB", 0, 0, 0.07f, true));
		IrisRenderer->AnimationBindEnd("IrisBStart", std::bind(&TitleLevel::OnIrisAnimationFrameEnd, this, std::placeholders::_1));
		IrisRenderer->ChangeFrameAnimation("IrisB");
	}

	{
		Background* Chalice = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* ChaliceRenderer = Chalice->CreateComponent<GameEngineTextureRenderer>();
		ChaliceRenderer->CreateFrameAnimationFolder("Chalice", FrameAnimation_DESC("Chalice", 0.055f));
		ChaliceRenderer->ChangeFrameAnimation("Chalice");
		ChaliceRenderer->SetScaleModeImage();
		ChaliceRenderer->GetTransform().SetLocalPosition({ -25.0f, -50.0f, (int)ZOrder::Player });

		Background* Cuphead = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* CupheadRenderer = Cuphead->CreateComponent<GameEngineTextureRenderer>();
		CupheadRenderer->CreateFrameAnimationFolder("Cuphead", FrameAnimation_DESC("Cuphead", 0.055f));
		CupheadRenderer->ChangeFrameAnimation("Cuphead");
		CupheadRenderer->SetScaleModeImage();
		CupheadRenderer->GetTransform().SetLocalPosition({ -320.0f, -20.0f, (int)ZOrder::Player - 1 });

		Background* Mugman = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* MugmanRenderer = Mugman->CreateComponent<GameEngineTextureRenderer>();
		MugmanRenderer->CreateFrameAnimationFolder("MugmanA", FrameAnimation_DESC("Mugman", 0.055f));
		MugmanRenderer->ChangeFrameAnimation("MugmanA");
		MugmanRenderer->SetScaleModeImage();
		MugmanRenderer->GetTransform().SetLocalPosition({ 305.0f, -24.0f, (int)ZOrder::Player - 1 });
	}

	GameEngineSound::SoundPlayOneShot("MDHR.mp3");
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->GetIsAnyKeyPressed()) // 아무키가 눌리면
	{
		IrisRenderer->ChangeFrameAnimation("IrisBStart");
	}
}

void TitleLevel::End() 
{
}

void TitleLevel::OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Select");
}
