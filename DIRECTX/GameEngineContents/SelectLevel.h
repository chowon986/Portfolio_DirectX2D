#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

// Ό³Έν :
class GameEngineTextureRenderer;
class SelectLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SelectLevel();
	~SelectLevel();

	// delete Function
	SelectLevel(const SelectLevel& _Other) = delete;
	SelectLevel(SelectLevel&& _Other) noexcept = delete;
	SelectLevel& operator=(const SelectLevel& _Other) = delete;
	SelectLevel& operator=(SelectLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* OptionRenderer;
	GameEngineTextureRenderer* SelectScreenRenderer;
	GameEngineTextureRenderer* RedSelectBoxRenderer;
	GameEngineTextureRenderer* SelectOutlineRenderer1;
	GameEngineTextureRenderer* SelectOutlineRenderer2;
	GameEngineTextureRenderer* SelectOutlineRenderer3;
	GameEngineTextureRenderer* LetterRenderer;
	GameEngineTextureRenderer* BlackLetterRenderer1;
	GameEngineTextureRenderer* BlackLetterRenderer2;
	GameEngineTextureRenderer* SelectPlayerRenderer;
	GameEngineTextureRenderer* PlayerARenderer;
	GameEngineTextureRenderer* PlayerBRenderer;
	std::string OptionNumber;
	int Num;
	int SelectBlockNum;
	bool SelectOptionOn;
	bool SelectDataOn;
	bool SelectCharacterOn;
	bool OnceCheck;
	bool CupheadOn;
	bool MugmanOn;
	float DeltaTime;

private:
	void EndAnimation(FrameAnimation_DESC _Info);
};

