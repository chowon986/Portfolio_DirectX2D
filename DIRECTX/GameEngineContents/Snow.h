#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Snow : public GameEngineActor
{
public:
	// constrcuter destructer
	Snow();
	~Snow();

	// delete Function
	Snow(const Snow& _Other) = delete;
	Snow(Snow&& _Other) noexcept = delete;
	Snow& operator=(const Snow& _Other) = delete;
	Snow& operator=(Snow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

};

