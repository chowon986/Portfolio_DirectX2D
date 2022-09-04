#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineTextureRenderer;
class BeforeTitleLevel : public GameEngineLevel
{
public:
	BeforeTitleLevel();
	~BeforeTitleLevel();

	BeforeTitleLevel(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel(BeforeTitleLevel&& _Other) noexcept = delete;
	BeforeTitleLevel& operator=(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel& operator=(BeforeTitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnHDMRAnimationFrameEnd(const FrameAnimation_DESC& _Info);

private:
	float BlackScreenToAnimationIntervalTime;
	float ElapsedTime;
	GameEngineTextureRenderer* MDHRLogoRenderer;
};

