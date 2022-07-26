#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Waterfall : public GameEngineActor
{
public:
	// constrcuter destructer
	Waterfall();
	~Waterfall();

	// delete Function
	Waterfall(const Waterfall& _Other) = delete;
	Waterfall(Waterfall&& _Other) noexcept = delete;
	Waterfall& operator=(const Waterfall& _Other) = delete;
	Waterfall& operator=(Waterfall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

};

