#include "PreCompile.h"
#include "BeforeTitleLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

BeforeTitleLevel::BeforeTitleLevel()
{
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}

void BeforeTitleLevel::EndHDMRAnimation(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Title");
}

void BeforeTitleLevel::Start()
{
	{
		Background* MDHRLogo = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = MDHRLogo->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280,720,100 });
		Renderer->CreateFrameAnimationFolder("BeforeTitle", FrameAnimation_DESC("10BeforeTitleLevel", 0.05f));
		Renderer->AnimationBindEnd("BeforeTitle", std::bind(&BeforeTitleLevel::EndHDMRAnimation, this, std::placeholders::_1));
		Renderer->ChangeFrameAnimation("BeforeTitle");

	}
}

void BeforeTitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}


void BeforeTitleLevel::End()
{
	int a = 0;
}