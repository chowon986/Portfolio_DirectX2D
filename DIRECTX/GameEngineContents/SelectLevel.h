#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

enum class SelectLevelPhase
{
	SelectOption,
	SelectRecord,
	SelectPlayer,
};

class Background;
class GameEngineTextureRenderer;
class SelectLevel : public GameEngineLevel
{
public:
	SelectLevel();
	~SelectLevel();

	SelectLevel(const SelectLevel& _Other) = delete;
	SelectLevel(SelectLevel&& _Other) noexcept = delete;
	SelectLevel& operator=(const SelectLevel& _Other) = delete;
	SelectLevel& operator=(SelectLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	SelectLevelPhase GetPhase();
	void SetPhase(SelectLevelPhase _Phase);
	void CreateSelectRecordPhaseRenderer();
	void CreateSelectPlayerPhaseRenderer();
	void EndAnimation(const FrameAnimation_DESC& _Info);

private:
	int RecordNum;
	int OptionImageNum;
	bool CanSelectCharacter;
	bool CupheadOnOffSwitch;
	float SelectCharacterElapsedTime;
	SelectLevelPhase Phase;
	std::string OptionNumber;
	GameEngineTextureRenderer* LetterRenderer;
	GameEngineTextureRenderer* OptionRenderer;
	GameEngineTextureRenderer* PlayerARenderer;
	GameEngineTextureRenderer* PlayerBRenderer;
	GameEngineTextureRenderer* SelectScreenRenderer;
	GameEngineTextureRenderer* RedSelectBoxRenderer;
	GameEngineTextureRenderer* BlackLetterRenderer1;
	GameEngineTextureRenderer* BlackLetterRenderer2;
	GameEngineTextureRenderer* SelectPlayerRenderer;
	GameEngineTextureRenderer* SelectOutlineRenderer1;
	GameEngineTextureRenderer* SelectOutlineRenderer2;
	GameEngineTextureRenderer* SelectOutlineRenderer3;
	GameEngineTextureRenderer* ScreenLightRenderer;
};

