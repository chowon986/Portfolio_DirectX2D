#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Boat : public GameEngineActor
{
public:
	// constrcuter destructer
	Boat();
	~Boat();

	// delete Function
	Boat(const Boat& _Other) = delete;
	Boat(Boat&& _Other) noexcept = delete;
	Boat& operator=(const Boat& _Other) = delete;
	Boat& operator=(Boat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* BoatRipplesRenderer;
};

