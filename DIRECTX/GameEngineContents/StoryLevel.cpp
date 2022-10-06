#include "PreCompile.h"
#include "StoryLevel.h"
#include "Background.h"
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineContents/TextureLoadUtils.h>

StoryLevel::StoryLevel()
	:SoundOnceCheck(false)
	, Hourglass(nullptr)
	, BackgroundRenderer(nullptr)
	, IrisRenderer(nullptr)
	, LoadCompleted(false)
	, SoundOnceCheckA(false)
{
}

StoryLevel::~StoryLevel()
{
}

void StoryLevel::LevelStartEvent()
{
	if (Hourglass == nullptr)
	{
		Hourglass = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Hourglass->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("Loading", 0.05f));
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 550, -200,-100 });
	}
}

void StoryLevel::Update(float _DeltaTime)
{
	if (LoadCompleted == false)
	{
		LoadCompleted = TextureLoadUtils::LoadTexturesAsync("23IntroStory", 20);
		if (LoadCompleted == true)
		{
			OnLoadCompleted();
		}

		return;
	}

	if (false == SoundOnceCheck)
	{
		Controller = GameEngineSound::SoundPlayControl("mus_dlc_intro_start.wav");
		SoundOnceCheck = true;
	}
}

void StoryLevel::End()
{
}

void StoryLevel::IntroStoryAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Controller.Stop();
	GEngine::ChangeLevel("WorldMap");
}

void StoryLevel::IntroStoryAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	StoryRenderer->GetTransform().SetWorldScale({ 1280.0f, 720.0f });
	if (GameEngineInput::GetInst()->IsDown("AnimationFrameChangeSpeedUp"))
	{
		FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);
		Info->Inter = 0.0f;
	}

	if (_Info.CurFrame == 629)
	{
		Controller.Stop();
		Controller = GameEngineSound::SoundPlayControl("mus_dlc_intro.wav");
	}
}

void StoryLevel::OnLoadCompleted()
{
	{
		GameEngineActor* IntroStory = CreateActor<GameEngineActor>();
		StoryRenderer = IntroStory->CreateComponent<GameEngineTextureRenderer>();
		StoryRenderer->CreateFrameAnimationFolder("Story", FrameAnimation_DESC("Story", 0.05, false));
		StoryRenderer->ChangeFrameAnimation("Story");
		StoryRenderer->AnimationBindEnd("Story", std::bind(&StoryLevel::IntroStoryAnimationFrameFinished, this, std::placeholders::_1));
		StoryRenderer->AnimationBindFrame("Story", std::bind(&StoryLevel::IntroStoryAnimationFrameChanged, this, std::placeholders::_1));

		Hourglass->Off();
	}
}

