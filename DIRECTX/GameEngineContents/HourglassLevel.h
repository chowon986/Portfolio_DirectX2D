#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class HourglassLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HourglassLevel();
	~HourglassLevel();

	// delete Function
	HourglassLevel(const HourglassLevel& _Other) = delete;
	HourglassLevel(HourglassLevel&& _Other) noexcept = delete;
	HourglassLevel& operator=(const HourglassLevel& _Other) = delete;
	HourglassLevel& operator=(HourglassLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	void EndAnimation(FrameAnimation_DESC _Info);
};

