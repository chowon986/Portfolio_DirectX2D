#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BackgroundHills;
class BackgroundObject;
class DogFightLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	DogFightLevel();
	~DogFightLevel();

	// delete Function
	DogFightLevel(const DogFightLevel& _Other) = delete;
	DogFightLevel(DogFightLevel&& _Other) noexcept = delete;
	DogFightLevel& operator=(const DogFightLevel& _Other) = delete;
	DogFightLevel& operator=(DogFightLevel&& _Other) noexcept = delete;

public:
	void ColMapOnOffSwitch();
	void ResetPositionCloudLeftA(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	BackgroundHills* Hills;
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* BackgroundSkyRenderer;
	BackgroundObject* CloudLeftA;
};

