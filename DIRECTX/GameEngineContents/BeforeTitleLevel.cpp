#include "PreCompile.h"
#include "BeforeTitleLevel.h"
#include "Background.h"
#include "OldFilm.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

BeforeTitleLevel::BeforeTitleLevel()
	: BlackScreenToAnimationIntervalTime(3.0f)
	, ElapsedTime(0.0f)
	, MDHRLogoRenderer(nullptr)
{
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}

void BeforeTitleLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICameraActorTransform().SetLocalPosition({ 0, 0 });

	Background* MDHRLogo = CreateActor<Background>(GameObjectGroup::UI);
	MDHRLogoRenderer = MDHRLogo->CreateComponent<GameEngineTextureRenderer>();
	MDHRLogoRenderer->GetTransform().SetLocalScale({ 1280,720,100 });
	MDHRLogoRenderer->CreateFrameAnimationFolder("BeforeTitle", FrameAnimation_DESC("10BeforeTitleLevel", 0.05f));
	MDHRLogoRenderer->SetTexture("Loading_background.png");
	MDHRLogoRenderer->AnimationBindEnd("BeforeTitle", std::bind(&BeforeTitleLevel::OnHDMRAnimationFrameEnd, this, std::placeholders::_1));
	
	//{
	//	GameEngineActor* Shade = CreateActor< GameEngineActor>();
	//	GameEngineTextureRenderer* Renderer = Shade->CreateComponent<GameEngineTextureRenderer>();
	//	Renderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX",0,0, 0.05f));
	//	Renderer->ChangeFrameAnimation("03ScreenFX");
	//	Renderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
	//	Renderer->GetPipeLine()->SetOutputMergerBlend("OldFilm2");
	//	Renderer->Option.ColorInversion = 1;
	//}

	OldFilm* PostEffect = CreateActor<OldFilm>(GameObjectGroup::UI);
	PostEffect->SetLevelOverOn();
}

void BeforeTitleLevel::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;
	if (ElapsedTime > BlackScreenToAnimationIntervalTime)
	{
		MDHRLogoRenderer->ChangeFrameAnimation("BeforeTitle");
	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}

void BeforeTitleLevel::End()
{
}

void BeforeTitleLevel::OnHDMRAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Title");
}