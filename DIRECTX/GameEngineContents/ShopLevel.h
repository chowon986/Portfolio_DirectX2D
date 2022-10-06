#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <string>

enum class ShopPhase
{
	None,
	Select,
	Buy,

};
// Ό³Έν :
enum class ShopPhase;
class ItemInventory;
class GameEngineTextureRenderer;
class Pig;
class ItemBase;
class CharacterState;
class ShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ShopLevel();
	~ShopLevel();

	// delete Function
	ShopLevel(const ShopLevel& _Other) = delete;
	ShopLevel(ShopLevel&& _Other) noexcept = delete;
	ShopLevel& operator=(const ShopLevel& _Other) = delete;
	ShopLevel& operator=(ShopLevel&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void LevelStartEvent() override;
	void LevelEndEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	void EndIrisAnimation(const FrameAnimation_DESC& _Info);
	void BuyItemEnd(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* LeftDrawerRenderer;
	float Time;
	bool IsLeftDrawerOpen;
	Pig* ShopPig;
	bool IsLeftDrawerOpened;
	float4 StartLerpValueX;
	float4 EndLerpValueX;
	float4 EndPosition;
	bool OnceCheck;
	float ElapsedTime;
	ShopPhase Phase;
	bool OddEvenSwitch() { IsOddNumber = !IsOddNumber; return IsOddNumber; }
	ItemInventory* Inventory;
	bool SoundOnceCheck;

public:
	std::vector<std::shared_ptr<ItemBase>> ItemNames;
	std::vector<GameEngineTextureRenderer*> ItemRenderers;
	std::vector<std::string> ItemName;
	float ItemPosX;
	float ItemPosY;
	bool IsOddNumber;
	int SelectItemNum;
	CharacterState* State;
	int CurCoin;
	GameEngineTextureRenderer* CoinCountRenderer;
	GameEngineTextureRenderer* FontRenderer;
	int BeforeSelectItemNum;
	GameEngineSoundPlayer Controller;
	bool SoundOnceCheckB;
};

