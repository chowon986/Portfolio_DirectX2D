#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Dogfight : public GameEngineActor
{
public:
	// constrcuter destructer
	Dogfight();
	~Dogfight();

	// delete Function
	Dogfight(const Dogfight& _Other) = delete;
	Dogfight(Dogfight&& _Other) noexcept = delete;
	Dogfight& operator=(const Dogfight& _Other) = delete;
	Dogfight& operator=(Dogfight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
};

