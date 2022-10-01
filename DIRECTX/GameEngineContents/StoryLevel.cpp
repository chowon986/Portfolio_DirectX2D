#include "PreCompile.h"
#include "StoryLevel.h"

StoryLevel::StoryLevel()
{
}

StoryLevel::~StoryLevel()
{
}

void StoryLevel::LevelStartEvent()
{
	//GameEngineActor* IntroStory = CreateActor<GameEngineActor>();
	//GameEngineTextureRenderer* Renderer = IntroStory->CreateComponent<GameEngineTextureRenderer>();
	//Renderer->CreateFrameAnimationFolder("23IntroStory", FrameAnimation_DESC("23IntroStory", 0.05, false));
	//Renderer->ChangeFrameAnimation("23IntroStory");
	//Renderer->SetScaleModeImage();
	//Renderer->AnimationBindEnd("23IntroStory", std::bind(&StoryLevel::IntroStoryAnimationFrameFinished, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("23IntroStory", std::bind(&StoryLevel::IntroStoryAnimationFrameChanged, this, std::placeholders::_1));

	//GameEngineInput::GetInst()->CreateKey("AnimationFrameChangeSpeedUp", VK_DELETE);
}

void StoryLevel::Update(float _DeltaTime)
{
}

void StoryLevel::End()
{
}

void StoryLevel::IntroStoryAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("WorldMap");
}

void StoryLevel::IntroStoryAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (GameEngineInput::GetInst()->IsDown("AnimationFrameChangeSpeedUp"))
	{
		FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);
		Info->Inter -= 0.01;
	}
}

