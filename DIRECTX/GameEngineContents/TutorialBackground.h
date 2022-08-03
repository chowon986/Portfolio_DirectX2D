#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TutorialBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	TutorialBackground();
	~TutorialBackground();

	// delete Function
	TutorialBackground(const TutorialBackground& _Other) = delete;
	TutorialBackground(TutorialBackground&& _Other) noexcept = delete;
	TutorialBackground& operator=(const TutorialBackground& _Other) = delete;
	TutorialBackground& operator=(TutorialBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void EndTutorialStartAnimation(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* Renderer;
};

