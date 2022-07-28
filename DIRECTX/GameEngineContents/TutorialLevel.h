#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class GameEngineTextureRenderer;
class TutorialLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

public:
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};

