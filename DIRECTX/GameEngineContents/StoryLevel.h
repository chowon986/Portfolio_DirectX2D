#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

class Background;
class CharacterState;
class StoryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StoryLevel();
	~StoryLevel();

	// delete Function
	StoryLevel(const StoryLevel& _Other) = delete;
	StoryLevel(StoryLevel&& _Other) noexcept = delete;
	StoryLevel& operator=(const StoryLevel& _Other) = delete;
	StoryLevel& operator=(StoryLevel&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void IntroStoryAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void IntroStoryAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnLoadCompleted();

public:
	GameEngineSoundPlayer Controller;

private:
	Background* Hourglass;
	GameEngineTextureRenderer* BackgroundRenderer;
	GameEngineTextureRenderer* IrisRenderer;
	CharacterState* State;
	bool SoundOnceCheck;
	bool LoadCompleted;
	GameEngineTextureRenderer* StoryRenderer;
};

