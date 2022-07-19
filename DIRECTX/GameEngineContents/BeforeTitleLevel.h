#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BeforeTitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BeforeTitleLevel();
	~BeforeTitleLevel();

	// delete Function
	BeforeTitleLevel(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel(BeforeTitleLevel&& _Other) noexcept = delete;
	BeforeTitleLevel& operator=(const BeforeTitleLevel& _Other) = delete;
	BeforeTitleLevel& operator=(BeforeTitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};

