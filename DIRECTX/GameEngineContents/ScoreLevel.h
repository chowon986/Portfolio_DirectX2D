#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

class CharacterState;
class ScoreLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ScoreLevel();
	~ScoreLevel();

	// delete Function
	ScoreLevel(const ScoreLevel& _Other) = delete;
	ScoreLevel(ScoreLevel&& _Other) noexcept = delete;
	ScoreLevel& operator=(const ScoreLevel& _Other) = delete;
	ScoreLevel& operator=(ScoreLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	GameEngineTextureRenderer* BackgroundRenderer;
	CharacterState* State;
};

