#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class GameEngineTextureRenderer;
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

private:
	void EndIrisAnimation(FrameAnimation_DESC _Info);
private:
	GameEngineTextureRenderer* IrisRenderer;
	GameEngineTextureRenderer* LeftDrawerRenderer;
	float Time;
};

