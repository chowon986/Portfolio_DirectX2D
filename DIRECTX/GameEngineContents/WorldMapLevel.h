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
	void Win();
	void GivePineApple();

protected:
	void Start() override;
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void LevelEndEvent() override;
	void End() override;

	void OnLoadCompleted();
	void OnEventCoinDustAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnFlagAnimationFrameChanged(const FrameAnimation_DESC& _Info);

public:
	GameEngineSoundPlayer Controller;
	GameEngineTextureRenderer* DogFightEntryBubbleRenderer;
	GameEngineTextureRenderer* ShopEntryBubbleRenderer;
	GameEngineTextureRenderer* TutorialEntryBubbleRenderer;

private:
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* FlagRenderer;
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
	float PineAppleElapsedTime;
	bool SoundOnceCheck;
	bool TimeCountOn;

	std::vector<GameEngineTextureRenderer*> EventCoinRenderers;
	std::vector<GameEngineTextureRenderer*> PineAppleRenderers;
};

