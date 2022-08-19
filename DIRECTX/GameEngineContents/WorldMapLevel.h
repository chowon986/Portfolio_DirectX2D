#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CharacterState;
class GameEngineTextureRenderer;
class WorldMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WorldMapLevel();
	~WorldMapLevel();

	// delete Function
	WorldMapLevel(const WorldMapLevel& _Other) = delete;
	WorldMapLevel(WorldMapLevel&& _Other) noexcept = delete;
	WorldMapLevel& operator=(const WorldMapLevel& _Other) = delete;
	WorldMapLevel& operator=(WorldMapLevel&& _Other) noexcept = delete;

public:
	void ColMapOnOffSwitch();

protected:
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* MainLandRenderer;
	GameEngineTextureRenderer* MainLandColMapRenderer;
	GameEngineTextureRenderer* UnderWaterLandRenderer;
	GameEngineTextureRenderer* OutsideOfMainLandLeftRenderer;
	GameEngineTextureRenderer* OutsideOfMainLandRightRenderer;
	CharacterState* State;
};

