#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class Background;
class CharacterState;
class ItemInventory;
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
	void Start() override {}
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnLoadCompleted();

private:
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* MainLandRenderer;
	GameEngineTextureRenderer* MainLandColMapRenderer;
	GameEngineTextureRenderer* UnderWaterLandRenderer;
	GameEngineTextureRenderer* OutsideOfMainLandLeftRenderer;
	GameEngineTextureRenderer* OutsideOfMainLandRightRenderer;
	GameEngineTextureRenderer* CoinCountRenderer;
	CharacterState* State;
	ItemInventory* Inventory;
	int CurCoin;
	Background* Hourglass;
	float LoadInterval;
	float LoadElapsedTime;
	float LoadCompleted;
};

