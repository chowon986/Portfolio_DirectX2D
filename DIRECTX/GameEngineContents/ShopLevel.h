#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class ShopPhase
{
	None,
	Open,
	Select,

};
// ���� :
class GameEngineTextureRenderer;
class Pig;
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
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	void EndIrisAnimation(const FrameAnimation_DESC& _Info);

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
};

