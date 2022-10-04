#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
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
	void GiveCoin();

protected:
	void Start() override;
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnLoadCompleted();
	void OnEventCoinDustAnimationFrameChanged(const FrameAnimation_DESC& _Info);

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
	float LoadCompleted;

	std::vector<GameEngineTextureRenderer*> EventCoinRenderers;
};

