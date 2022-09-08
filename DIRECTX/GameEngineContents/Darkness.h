#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Darkness : public GameEngineActor
{
public:
	// constrcuter destructer
	Darkness();
	~Darkness();

	// delete Function
	Darkness(const Darkness& _Other) = delete;
	Darkness(Darkness&& _Other) noexcept = delete;
	Darkness& operator=(const Darkness& _Other) = delete;
	Darkness& operator=(Darkness&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

