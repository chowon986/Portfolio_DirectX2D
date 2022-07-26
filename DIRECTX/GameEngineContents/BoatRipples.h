#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BoatRipples : public GameEngineActor
{
public:
	// constrcuter destructer
	BoatRipples();
	~BoatRipples();

	// delete Function
	BoatRipples(const BoatRipples& _Other) = delete;
	BoatRipples(BoatRipples&& _Other) noexcept = delete;
	BoatRipples& operator=(const BoatRipples& _Other) = delete;
	BoatRipples& operator=(BoatRipples&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
};

