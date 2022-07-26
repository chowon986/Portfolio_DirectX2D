#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class WaterfallBase : public GameEngineActor
{
public:
	// constrcuter destructer
	WaterfallBase();
	~WaterfallBase();

	// delete Function
	WaterfallBase(const WaterfallBase& _Other) = delete;
	WaterfallBase(WaterfallBase&& _Other) noexcept = delete;
	WaterfallBase& operator=(const WaterfallBase& _Other) = delete;
	WaterfallBase& operator=(WaterfallBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

};

