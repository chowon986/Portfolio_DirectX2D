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
	: BlackScreenToAnimationIntervalTime(5.0f)
	, ElapsedTime(0.0f)
	, MDHRLogoRenderer(nullptr)
{
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}

void BeforeTitleLevel::OnEvent()
{

}

void BeforeTitleLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	Background* MDHRLogo = CreateActor<Background>(GameObjectGroup::UI);
	MDHRLogoRenderer = MDHRLogo->CreateComponent<GameEngineTextureRenderer>();
	MDHRLogoRenderer->GetTransform().SetLocalScale({ 1280,720,100 });
	MDHRLogoRenderer->CreateFrameAnimationFolder("BeforeTitle", FrameAnimation_DESC("10BeforeTitleLevel", 0.05f));
	MDHRLogoRenderer->SetTexture("Loading_background.png");
	MDHRLogoRenderer->AnimationBindEnd("BeforeTitle", std::bind(&BeforeTitleLevel::OnHDMRAnimationFrameEnd, this, std::placeholders::_1));

	OldFilm* PostEffect = CreateActor<OldFilm>(GameObjectGroup::UI);
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