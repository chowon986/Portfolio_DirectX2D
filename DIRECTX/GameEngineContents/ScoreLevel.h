#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

enum class ScorePhase
{
	Minute,
	Second,
	HP,
	Parry,
	UseCard,
	SkillLevel
};

class CharacterScore;
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
	void Start() override {}
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* BackgroundRenderer;
	GameEngineTextureRenderer* IrisRenderer;
	CharacterState* State;
	CharacterScore* Score;
	int PlayMinute;
	int PlaySecond;
	float ElapsedTime;
	float IntervalTime;
	int Num;
	std::map<int, GameEngineFontRenderer*> FontRenderers;
	ScorePhase Phase;
};

