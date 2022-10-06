#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineTextureRenderer;
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info);
	void OnHDMRAnimationFrameEnd(const FrameAnimation_DESC& _Info);

private:
	float BlackScreenToAnimationIntervalTime;
	float ElapsedTime;
	float FadeInElapsedTime;
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* MDHRLogoRenderer;
	GameEngineTextureRenderer* FadeInActorRenderer;
	int Phase;
	bool SoundOnceCheckA;
	bool SoundOnceCheckB;
	bool SoundOnceCheckC;
};

